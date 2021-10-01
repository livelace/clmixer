//
// Created by user on 9/28/21.
//

#include <spdlog/spdlog.h>

#include "result.h"

void OpenclBufferResult::allocate_data() {
    if (m_unit == "double")
    {
        m_length = m_size / sizeof(double);
        m_double =  new double[m_length];
        data = m_double;
    }

    if (m_unit == "int")
    {
        m_length = m_size / sizeof(int);
        m_int =  new int[m_length];
        data = m_int;
    }

    if (m_unit == "long")
    {
        m_length = m_size / sizeof(long);
        m_long =  new long[m_length];
        data = m_long;
    }
}

void OpenclBufferResult::compare(const std::shared_ptr<Result>& result)
{
    auto r = std::static_pointer_cast<OpenclBufferResult>(result);

    if (m_unit != r->m_unit)
    {
        spdlog::warn("result check [{}][{}]: differ unit ({} <> {})",
                m_id, r->m_id, m_unit, r->m_unit);
        return;
    }

    if (m_length != r->m_length)
    {
        spdlog::warn("result check [{}][{}]: differ length ({} <> {})",
                     m_id, r->m_id, m_length, r->m_length);
        return;
    }

    if (m_size != r->m_size)
    {
        spdlog::warn("result check [{}][{}]: differ size ({} <> {})",
                     m_id, r->m_id, m_size, r->m_size);
        return;
    }

    if (m_unit == "double")
    {
        auto src_result = m_double;
        auto dst_result = r->m_double;
        for (unsigned long i=0; i < m_length; i++)
        {
            if (src_result[i] != dst_result[i])
            {
                spdlog::warn("result check [{}][{}]: differ data at offset: {} ({} <> {})",
                             m_id, r->m_id, i, src_result[i], dst_result[i]);
                return;
            }
        }
    }

    if (m_unit == "int")
    {
        auto src_result = m_int;
        auto dst_result = r->m_int;
        for (unsigned long i=0; i < m_length; i++)
        {
            if (src_result[i] != dst_result[i])
            {
                spdlog::warn("result check [{}][{}]: differ data at offset: {} ({} <> {})",
                             m_id, r->m_id, i, src_result[i], dst_result[i]);
                return;
            }
        }
    }

    if (m_unit == "long")
    {
        auto src_result = m_long;
        auto dst_result = r->m_long;
        for (unsigned long i=0; i < m_length; i++)
        {
            if (src_result[i] != dst_result[i])
            {
                spdlog::warn("result check [{}][{}]: differ data at offset: {} ({} <> {})",
                             m_id, r->m_id, i, src_result[i], dst_result[i]);
                return;
            }
        }
    }

    spdlog::info("result check [{}][{}]: same", m_id, r->m_id);
}

void OpenclBufferResult::show()
{
    if (m_unit == "double")
        spdlog::info("result show [{}]: [{} ... {}]", m_id, m_double[0], m_double[m_length - 1]);

    if (m_unit == "int")
        spdlog::info("result show [{}]: [{} ... {}]", m_id, m_int[0], m_int[m_length - 1]);

    if (m_unit == "long")
        spdlog::info("result show [{}]: [{} ... {}]", m_id, m_long[0], m_long[m_length - 1]);
}
