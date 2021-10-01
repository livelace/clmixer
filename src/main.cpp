//
// Created by user on 9/24/21.
//

#include <chrono>
#include <thread>

#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "const.h"
#include "data.h"
#include "main.h"
#include "opencl.h"
#include "result.h"
#include "task.h"

int main(int argc, char *argv[]) {
    // ------------------------------------------------------------------------
    // Parse arguments.

    CLI::App app(defaults::APP_NAME);
    app.set_version_flag("-v,--version", defaults::APP_VERSION);

    // device.
    unsigned int device_number{0};

    // task.
    std::string task_mode{"opencl"};
    unsigned int task_limit{1};
    unsigned int task_repeat{1};

    // opencl.
    std::string opencl_mode{"buffer"};
    std::vector<std::string> opencl_kernel_file;

    // opencl buffer.
    bool opencl_check_result{false};
    std::string opencl_buffer_generator{"increment"};
    unsigned int opencl_buffer_generator_seed{42};
    unsigned int opencl_buffer_work_group_size{0};
    //std::string opencl_buffer_memory{"device"};
    unsigned long opencl_buffer_size{defaults::DEFAULT_OPENCL_BUFFER_SIZE};
    std::string opencl_buffer_unit{"long"};

    // device.
    app.add_option(
            "--device,-d",
            device_number,
            "device number: [0]"
    )->group("Device options");

    app.add_flag_callback(
            "--show-devices,--sd",
            list_devices,
            "show available devices"
    )->group("Device options");

    // task.
    app.add_option(
            "--task-mode,--tm",
            task_mode,
            "supported task modes: [opencl]"
    )->group("Task options");

    app.add_option(
            "--task-limit,--tl",
            task_limit,
            "how many tasks are allowed to work in parallel: [1]"
    )->group("Task options");

    app.add_option(
            "--task-repeat,--tr",
            task_repeat,
            "how many times task should be repeated: [1]"
    )->group("Task options");

    // opencl.
    app.add_option(
            "--opencl-mode,--om",
            task_repeat,
            "opencl mode: [buffer]"
    )->group("OpenCL options");

    app.add_option(
            "--opencl-kernel-file,--okf",
            opencl_kernel_file,
            "opencl kernel files (tasks): /path/to/first /path/to/second"
    )->required()->check(CLI::ExistingFile)->group("OpenCL options");

    // opencl buffer.
    app.add_flag(
            "--opencl-buffer-check-result,--obcr",
            opencl_check_result,
            "check result between different tasks: [false], true"
    )->group("OpenCL buffer options");

    app.add_option(
            "--opencl-buffer-generator,--obg",
            opencl_buffer_generator,
            "opencl buffer generator: [increment], random, zero"
    )->group("OpenCL buffer options");

    app.add_option(
            "--opencl-buffer-generator-seed,--obgs",
            opencl_buffer_generator_seed,
            "opencl buffer generator seed: [42]"
    )->group("OpenCL buffer options");

    app.add_option(
            "--opencl-buffer-work-group-size,--obwgs",
            opencl_buffer_work_group_size,
            "opencl buffer work group size: [auto], 256"
    )->group("OpenCL buffer options");

/*    app.add_option(
            "--opencl-buffer-memory,--obm",
            opencl_buffer_memory,
            "opencl buffer memory: [device]"
    )->group("OpenCL buffer options");*/

    app.add_option(
            "--opencl-buffer-size,--obs",
            opencl_buffer_size,
            "opencl buffer size: [1g]"
    )->transform(CLI::AsSizeValue(false))->group("OpenCL buffer options");

    app.add_option(
            "--opencl-buffer-unit,--obu",
            opencl_buffer_unit,
            "opencl buffer unit: double, int, [long]"
    )->check(CLI::IsMember({"double", "int", "long"}))->group("OpenCL buffer options");

    // parse args.
    try {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    spdlog::info("{} {}", defaults::APP_NAME, defaults::APP_VERSION);

    // ------------------------------------------------------------------------
    // Check device availability/compatibility.

    auto devices = get_devices();

    if (devices.size()-1 < device_number)
    {
        spdlog::error("device doesn't exist: {}", device_number);
        exit (1);
    }

    auto device = devices[device_number];

    spdlog::info("device: #{} ({}, {}MHz, {}, {})",
                 device->id, device->name, device->clock_speed,
                 human_readable(device->memory_global_size), human_readable(device->memory_max_allocate));

    spdlog::info("task mode: {}", task_mode);

    // ------------------------------------------------------------------------
    // OpenCL buffer task.
    if (task_mode == "opencl" && opencl_mode == "buffer")
    {
        spdlog::info("opencl mode: {}", opencl_mode);

        std::vector<std::shared_ptr<Result>> results;

        {
            // generate data.
            auto opencl_buffer_data = std::make_shared<Data>(opencl_buffer_generator, opencl_buffer_unit,
                                                             opencl_buffer_size, opencl_buffer_generator_seed);

            // create tasks, fill data.
            std::vector<std::shared_ptr<Task>> tasks;

            for (int index=0; index < opencl_kernel_file.size(); index++)
            {
                auto id = index + 1;
                auto kernel_file = opencl_kernel_file[index];
                auto task = std::make_shared<OpenclBufferTask>(id, task_repeat, device, kernel_file,
                                                               opencl_buffer_work_group_size,
                                                               opencl_buffer_data->c_length,
                                                               opencl_buffer_data->c_size,
                                                               opencl_buffer_data->c_data);

                auto result = std::make_shared<OpenclBufferResult>(id, opencl_buffer_unit, opencl_buffer_size);

                tasks.push_back(task);
                results.push_back(result);
            }

            // execute tasks.
            parallel_task(task_limit, tasks, results);
        }

        // show results.
        for (const auto& result : results) result->show();

        // compare results.
        if (opencl_check_result && results.size() > 1)
        {
            auto r0 = results[0];
            for (int i=1; i < results.size(); i++) r0->compare(results[i]);

        } else if (opencl_check_result && results.size() == 1)
        {
            spdlog::warn("result check [0]: nothing to compare");
        }
    }

    // ------------------------------------------------------------------------
    // OpenCL image task.

    // ------------------------------------------------------------------------
    // OpenCL pipe task.

    // ------------------------------------------------------------------------

    spdlog::info("exiting");
}