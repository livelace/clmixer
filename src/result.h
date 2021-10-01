//
// Created by user on 9/28/21.
//

#include <filesystem>
#include <iostream>

#ifndef CLMIXER_RESULT_H
#define CLMIXER_RESULT_H

class Result
{
protected:
    unsigned int m_id;

    explicit Result(unsigned int id) : m_id(id) {}

public:
    void* data{nullptr};
    virtual void compare(const std::shared_ptr<Result>& result) = 0;
    virtual void show() = 0;
};

class OpenclBufferResult : public Result
{
private:
    std::string m_unit;
    unsigned long m_length;
    unsigned long m_size;

    double* m_double{nullptr};
    int* m_int{nullptr};
    long* m_long{nullptr};

    void allocate_data();

public:
    void compare(const std::shared_ptr<Result>& result) override;
    void show() override;

    OpenclBufferResult(unsigned int id, const std::string &unit,
                       const unsigned long &size)
            : Result(id)
    {
        m_unit = unit;
        m_size = size;

        allocate_data();
    }

    ~OpenclBufferResult()
    {
        m_double ? delete[] m_double : void();
        m_int ? delete[] m_int : void();
        m_long ? delete[] m_long : void();
    }
};

#endif //CLMIXER_RESULT_H
