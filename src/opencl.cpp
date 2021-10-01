//
// Created by user on 9/25/21.
//

#define CL_MINIMUM_OPENCL_VERSION 110
#define CL_HPP_MINIMUM_OPENCL_VERSION 110
#define CL_HPP_TARGET_OPENCL_VERSION 300

#include <iostream>
#include <vector>

#include <spdlog/spdlog.h>
#include <CL/opencl.hpp>

#include "opencl.h"

std::vector<std::shared_ptr<Device>> get_devices()
{
    auto platforms = get_platforms();

    std::vector<std::shared_ptr<Device>> all_devices;
    std::vector<std::shared_ptr<Device>> cpu_devices;
    std::vector<std::shared_ptr<Device>> gpu_devices;

    for (auto const& platform : platforms)
    {
        std::vector<cl::Device> platform_devices;
        platform.getDevices(CL_DEVICE_TYPE_ALL, &platform_devices);

        for (auto const& d : platform_devices)
        {
            auto device = std::make_shared<Device>();

            device->clock_speed = d.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>();
            device->image_support = d.getInfo<CL_DEVICE_IMAGE_SUPPORT>();
            device->memory_global_size = d.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
            device->memory_max_allocate = d.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>();
            device->name = d.getInfo<CL_DEVICE_NAME>();
            device->platform_name = platform.getInfo<CL_PLATFORM_NAME>();
            device->svm_coarse_grained_buffer =
                    d.getInfo<CL_DEVICE_SVM_CAPABILITIES>() == CL_DEVICE_SVM_COARSE_GRAIN_BUFFER;
            device->svm_fine_grained_buffer =
                    d.getInfo<CL_DEVICE_SVM_CAPABILITIES>() == CL_DEVICE_SVM_FINE_GRAIN_BUFFER;
            device->svm_fine_grained_system =
                    d.getInfo<CL_DEVICE_SVM_CAPABILITIES>() == CL_DEVICE_SVM_FINE_GRAIN_SYSTEM;
            device->work_group_dimension = d.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>();
            device->work_group_size = d.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();

            device->cl_device = d;

            switch (d.getInfo<CL_DEVICE_TYPE>())
            {
                case CL_DEVICE_TYPE_CPU:
                    device->type = "cpu";
                    cpu_devices.push_back(std::move(device));
                    break;
                case CL_DEVICE_TYPE_GPU:
                    device->type = "gpu";
                    gpu_devices.push_back(std::move(device));
                    break;
                default:
                    device->type = "unsupported"; // apu.
                    break;
            }
        }
    }

    // cpu devices first.
    // gpu devices second.
    // assign ids.
    std::move(cpu_devices.begin(), cpu_devices.end(), std::back_inserter(all_devices));
    std::move(gpu_devices.begin(), gpu_devices.end(), std::back_inserter(all_devices));

    for (int i=0; i < all_devices.size(); i++)
    {
        all_devices[i]->id = i;
    }

    return all_devices;
}

std::vector<cl::Platform> get_platforms()
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    return platforms;
}

void list_devices()
{
    auto devices = get_devices();

    if (! devices.empty())
    {
        std::string cpu = "cpu:\n";
        std::string gpu = "gpu:\n";

        for (auto const& d : devices)
        {
            if (d->type == "cpu")
            {
                cpu += d->get_info();
            }
            else if (d->type == "gpu")
            {
                gpu += d->get_info();
            }
        }

        spdlog::info("available devices:");
        std::cout << std::endl;

        if (cpu != "cpu:\n")
        {
            std::cout << cpu << std::endl;
        }

        if (gpu != "gpu:\n")
        {
            std::cout << gpu << std::endl;
        }

    } else
    {
        spdlog::info("available devices: 0");
    }

    exit(0);
}