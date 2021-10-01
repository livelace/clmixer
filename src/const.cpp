//
// Created by user on 9/25/21.
//

#include <cmath>

#include "const.h"

namespace defaults
{
    extern const std::string APP_NAME = "clmixer";
    extern const std::string APP_VERSION = "v1.0.0";
    extern const std::string DEFAULT_OPENCL_KERNEL_NAME = "clmixer";
    extern const unsigned long DEFAULT_OPENCL_BUFFER_SIZE = 1 * 1024 * 1024 * 1024; // 1g
    extern const unsigned long DEFAULT_RANDOM_SEED = 42; // 42!
    extern const double RANDOM_DOUBLE_BEGIN = std::pow(2, sizeof(double) * 8) / -2;
    extern const double RANDOM_DOUBLE_END = std::pow(2, sizeof(double) * 8) / 2;
    extern const int RANDOM_INT_BEGIN = std::pow(2, sizeof(int) * 8) / -2;
    extern const int RANDOM_INT_END = std::pow(2, sizeof(int) * 8) / 2;
    extern const long RANDOM_LONG_BEGIN = std::pow(2, sizeof(long) * 8) / -2;
    extern const long RANDOM_LONG_END = std::pow(2, sizeof(long) * 8) / 2;
}