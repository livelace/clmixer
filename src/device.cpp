//
// Created by user on 9/24/21.
//

#include <iostream>

#include <fmt/format.h>

#include "device.h"
#include "helper.h"

std::string Device::get_info() {

    std::string tpl = R"DEL(  device: #{}
    name:                      {}
    platform:                  {}
    clock speed:               {}MHz
    memory global size:        {}
    memory max allocate:       {}
    svm coarse-grained buffer: {}
    svm fine-grained buffer:   {}
    svm fine-grained system:   {}
    work group dimension:      {}
    work group size:           {}

)DEL";

    return fmt::format(tpl,
                       id,
                       name,
                       platform_name,
                       clock_speed,
                       human_readable(memory_global_size),
                       human_readable(memory_max_allocate),
                       svm_coarse_grained_buffer,
                       svm_fine_grained_buffer,
                       svm_fine_grained_system,
                       work_group_dimension,
                       work_group_size);
}
