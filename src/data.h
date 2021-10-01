//
// Created by user on 9/28/21.
//

#include <iostream>
#include <random>

#include "helper.h"
#include "const.h"

#ifndef CLMIXER_DATA_H
#define CLMIXER_DATA_H

class Data
{
private:
    std::mt19937 m_mt;

    std::string m_generator;
    std::string m_unit;
    unsigned long m_length;
    unsigned long m_size;

    double* m_double{nullptr};
    int* m_int{nullptr};
    long* m_long{nullptr};

    void generate_data();

public:
    const void* c_data{nullptr};
    const unsigned long* c_length{nullptr};
    const unsigned long* c_size{nullptr};

    Data(std::string generator, std::string unit, unsigned long size, unsigned long seed=defaults::DEFAULT_RANDOM_SEED)
    {
        m_generator = generator;
        m_unit = unit;
        m_size = size;
        c_size = &m_size;
        m_mt.seed(seed);

        generate_data();
    }

    ~Data()
    {
        m_double ? delete[] m_double : void();
        m_int ? delete[] m_int : void();
        m_long ? delete[] m_long : void();

        spdlog::info("data: cleanup");
    }
};

#endif //CLMIXER_DATA_H
