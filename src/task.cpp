//
// Created by user on 9/27/21.
//

#include <chrono>
#include <future>
#include <thread>
#include <spdlog/spdlog.h>

#include "const.h"
#include "task.h"

void OpenclBufferTask::run(void* output)
{
    while (m_current_repeat == m_maximum_repeat || m_current_repeat < m_maximum_repeat)
    {
        spdlog::info("task [{}][{}]: execution ...", m_id, m_current_repeat);

        // create output buffer.
        m_opencl_output_buffer = cl::Buffer(m_opencl_context, CL_MEM_WRITE_ONLY, m_buffer_size);

        // set kernel parameters.
        m_opencl_kernel.setArg(0, m_opencl_input_buffer);
        m_opencl_kernel.setArg(1, m_opencl_output_buffer);

        // start computation (synchronous).
        cl::NDRange global(m_buffer_length);
        auto compute_code = m_opencl_command_queue.enqueueNDRangeKernel(m_opencl_kernel, cl::NullRange,
                                                                        global, m_work_group_size);
        m_opencl_command_queue.finish();
        if (compute_code != 0)
        {
            spdlog::error("task [{}][{}]: execution: compute failed: {}",
                    m_id, m_current_repeat, compute_code);
            exit(1);
        }
        spdlog::info("task [{}][{}]: execution: compute fulfilled", m_id, m_current_repeat);

        // read results.
        auto read_code = m_opencl_command_queue.enqueueReadBuffer(m_opencl_output_buffer, CL_TRUE, 0,
                                                                  m_buffer_size, output);
        if (read_code != 0)
        {
            spdlog::error("task [{}][{}]: execution: cannot read output buffer: {}",
                          m_id, m_current_repeat, read_code);
            exit(1);
        }
        spdlog::info("task [{}][{}]: execution: output buffer read", m_id, m_current_repeat);

        spdlog::info("task [{}][{}]: execution: finished", m_id, m_current_repeat);

        m_current_repeat += 1;
    }
}

void OpenclBufferTask::opencl_init()
{
    // prepare opencl stuff.
    m_opencl_context = cl::Context(m_device->cl_device);
    m_opencl_command_queue = cl::CommandQueue(m_opencl_context, m_device->cl_device);
    m_opencl_program_source.push_back({m_kernel_source.c_str(), m_kernel_source.length()});
    m_opencl_program = cl::Program(m_opencl_context, m_opencl_program_source);

    // try to compile kernel source.
    auto compile_code = m_opencl_program.build(m_device->cl_device);
    if (compile_code != 0)
    {
        spdlog::error("task [{}][{}]: creation: cannot compile kernel: \n{}", m_id, m_current_repeat,
                      m_opencl_program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(m_device->cl_device));
        exit(1);
    }
    spdlog::debug("task [{}][{}]: creation: kernel build log: \n{}", m_id, m_current_repeat,
                  m_opencl_program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(m_device->cl_device));
    spdlog::info("task [{}][{}]: creation: kernel compiled", m_id, m_current_repeat);

    // create kernel.
    m_opencl_kernel = cl::Kernel(m_opencl_program, defaults::DEFAULT_OPENCL_KERNEL_NAME.c_str());

    // fill input buffer.
    m_opencl_input_buffer = cl::Buffer(m_opencl_context, CL_MEM_READ_ONLY, m_buffer_size);

    auto write_code = m_opencl_command_queue.enqueueWriteBuffer(m_opencl_input_buffer, CL_TRUE, 0,
                                                                m_buffer_size, m_buffer_data);
    if (write_code != 0)
    {
        spdlog::error("task [{}][{}]: creation: cannot write input buffer: {}",
                      m_id, m_current_repeat, write_code);
        exit(1);
    }

    spdlog::info("task [{}][{}]: creation: input buffer written", m_id, m_current_repeat);
}

void parallel_task(unsigned int limit,
        std::vector<std::shared_ptr<Task>> tasks, std::vector<std::shared_ptr<Result>> results)
{
    std::vector<std::future<void>> pool;

    while (true)
    {
        // end work if there are no tasks (wait, run).
        if (tasks.empty() && pool.empty()) break;

        // process awaiting tasks.
        if (!tasks.empty())
        {
            // respect pool limits.
            if (pool.size() < limit)
            {
                auto index = tasks.size() - 1;
                auto task = tasks[index];
                auto result = results[index];

                pool.push_back(std::async(std::launch::async, [task, result] {task->run(result->data);}));
                tasks.pop_back();
            } else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        // remove completed tasks from the pool.
        pool.erase(std::remove_if(pool.begin(), pool.end(), [](std::future<void> &task) {
            return task.wait_for((std::chrono::seconds(0))) == std::future_status::ready;
        }), pool.end());
    }
}
