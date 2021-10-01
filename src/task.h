//
// Created by user on 9/27/21.
//

#include <iostream>
#include <memory>

#include "device.h"
#include "helper.h"
#include "result.h"

#ifndef CLMIXER_TASK_H
#define CLMIXER_TASK_H

class Task
{
protected:
    unsigned int m_id;
    unsigned int m_current_repeat{1};
    unsigned int m_maximum_repeat{1};

    explicit Task(unsigned int id, unsigned int maximum_iteration)
            : m_id(id), m_maximum_repeat(maximum_iteration) {}

public:
    virtual void run(void* output) = 0;
};

class OpenclBufferTask : public Task
{
private:
    std::shared_ptr<Device> m_device;

    unsigned long m_buffer_length;
    unsigned long m_buffer_size;
    const void* m_buffer_data;

    std::string m_kernel_source;
    std::string m_kernel_source_file;

    cl::Context m_opencl_context;
    cl::CommandQueue m_opencl_command_queue;
    cl::Buffer m_opencl_input_buffer;
    cl::Kernel m_opencl_kernel;
    cl::Buffer m_opencl_output_buffer;
    cl::Program m_opencl_program;
    cl::Program::Sources m_opencl_program_source;

    unsigned int m_work_group_size;

    void opencl_init();

public:
    void run(void* output);

    OpenclBufferTask(unsigned int id, unsigned int maximum_repeat, std::shared_ptr<Device> device,
                     std::string kernel_source_file,
                     unsigned int work_group_size,
                     const unsigned long *buffer_length, const unsigned long *buffer_size, const void *buffer_data)
            : Task(id, maximum_repeat)
    {
        spdlog::info("task [{}][{}]: creation ...", m_id, m_current_repeat);

        m_device = device;

        m_buffer_length = *buffer_length;
        m_buffer_size = *buffer_size;
        m_buffer_data = buffer_data;

        m_kernel_source_file = std::move(kernel_source_file);
        m_kernel_source = read_file(m_kernel_source_file);

        m_work_group_size = work_group_size == 0 ? m_device->work_group_size : work_group_size;

        opencl_init();

        spdlog::info("task [{}][{}]: creation: finished", m_id, m_current_repeat);
    }

    ~OpenclBufferTask()
    {
        spdlog::info("task [{}]: cleanup", m_id);
    }
};

void parallel_task(unsigned int limit,
        std::vector<std::shared_ptr<Task>> tasks, std::vector<std::shared_ptr<Result>> results);

#endif //CLMIXER_TASK_H
