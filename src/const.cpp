//
// Created by user on 9/25/21.
//

#include <cmath>

#include "const.h"

namespace defaults
{
    extern const std::string APP_NAME = "clmixer";
    extern const std::string APP_VERSION = "v1.1.0";
    extern const std::string DEFAULT_OPENCL_KERNEL_NAME = "clmixer";
    extern const unsigned long DEFAULT_OPENCL_BUFFER_SIZE = 1 * 1024 * 1024 * 1024; // 1g
    extern const unsigned long DEFAULT_RANDOM_SEED = 42; // 42!
}
