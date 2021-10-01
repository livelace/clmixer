//
// Created by user on 9/27/21.
//

#include <fstream>
#include <string>

#include <spdlog/spdlog.h>

#include "helper.h"

std::string human_readable(std::uintmax_t size)
{
    int i{};
    double mantissa = size;

    for (; mantissa >= 1024.; mantissa /= 1024., ++i) { }

    mantissa = std::ceil(mantissa * 10.) / 10.;

    return fmt::format("{}{}", mantissa, "BKMGTPE"[i]);
}

std::string read_file(const std::string &file) {
    std::string output;
    std::ifstream input_file(file);

    if (!input_file)
    {
        spdlog::error("cannot read file: {}", file);
        exit(1);
    }

    while (input_file)
    {
        std::string line;
        std::getline(input_file, line);
        output += line + "\n";
    }

    input_file.close();

    return output;
}
