//
// Created by user on 9/24/21.
//

#define CL_MINIMUM_OPENCL_VERSION 110
#define CL_HPP_MINIMUM_OPENCL_VERSION 110

#include <string>
#include <CL/opencl.hpp>

#ifndef CLMIXER_DEVICE_H
#define CLMIXER_DEVICE_H

class Device {
public:
    unsigned int id;

    uint clock_speed{0};
    bool image_support{false};
    ulong memory_global_size{0};
    ulong memory_max_allocate{0};
    std::string name{"unknown"};
    std::string platform_name{"unknown"};
    std::string type{"unknown"};
    bool svm_coarse_grained_buffer{false};
    bool svm_fine_grained_buffer{false};
    bool svm_fine_grained_system{false};
    uint work_group_dimension{0};
    size_t work_group_size{0};

    cl::Device cl_device;

    std::string get_info();
};

#endif //CLMIXER_DEVICE_H
