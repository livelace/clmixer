//
// Created by user on 9/25/21.
//

#define CL_MINIMUM_OPENCL_VERSION 110
#define CL_HPP_MINIMUM_OPENCL_VERSION 110

#include <memory>

#include <CL/opencl.hpp>

#include "device.h"

#ifndef CLMIXER_OPENCL_H
#define CLMIXER_OPENCL_H

std::vector<std::shared_ptr<Device>> get_devices();
std::vector<cl::Platform> get_platforms();
void list_devices();


#endif //CLMIXER_OPENCL_H
