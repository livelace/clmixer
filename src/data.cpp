//
// Created by user on 9/28/21.
//

#include <random>

#include <spdlog/spdlog.h>

#include "const.h"
#include "data.h"
#include "helper.h"

void Data::generate_data() {
    spdlog::info("generate {} data: started", m_generator);

    if (m_unit == "double")
    {
        m_length = m_size / sizeof(double);

        if (m_generator == "increment")
        {
            m_double = new double[m_length];
            for (unsigned long i=0; i < m_length; ++i) { m_double[i] = i; }
        }

        if (m_generator == "random")
        {
            m_double = new double[m_length];
            std::uniform_real_distribution<double> dist(defaults::RANDOM_DOUBLE_BEGIN, defaults::RANDOM_DOUBLE_END);
            for (unsigned long i=0; i < m_length; ++i) { m_double[i] = dist(m_mt); }
        }

        if (m_generator == "zero")
        {
            m_double = new double[m_length]{0};
        }

        c_data = m_double;
    }

    if (m_unit == "int")
    {
        m_length = m_size / sizeof(int);

        if (m_generator == "increment")
        {
            m_int = new int[m_length];
            for (unsigned long i=0; i < m_length; ++i) { m_int[i] = i; }
        }

        if (m_generator == "random")
        {
            m_int = new int[m_length];
            std::uniform_int_distribution<int> dist(defaults::RANDOM_INT_BEGIN, defaults::RANDOM_INT_END);
            for (unsigned long i=0; i < m_length; ++i) { m_int[i] = dist(m_mt); }
        }

        if (m_generator == "zero")
        {
            m_int = new int[m_length]{0};
        }

        c_data = m_int;
    }

    if (m_unit == "long")
    {
        m_length = m_size / sizeof(long);

        if (m_generator == "increment")
        {
            m_long = new long[m_length];
            for (unsigned long i=0; i < m_length; ++i) { m_long[i] = i; }
        }

        if (m_generator == "random")
        {
            m_long = new long[m_length];
            std::uniform_int_distribution<long> dist(defaults::RANDOM_LONG_BEGIN, defaults::RANDOM_LONG_END);
            for (unsigned long i=0; i < m_length; ++i) { m_long[i] = dist(m_mt); }
        }

        if (m_generator == "zero")
        {
            m_long = new long[m_length]{0};
        }

        c_data = m_long;
    }

    c_length = &m_length;

    spdlog::info("generate {} data: finished ({}, {}, {})",
            m_generator, m_unit, m_length, human_readable(m_size));
}