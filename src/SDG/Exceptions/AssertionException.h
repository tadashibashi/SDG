//
// Created by Aaron Ishibashi on 4/21/22.
//
#pragma once
#include <stdexcept>
#include <string>

namespace SDG
{
    class AssertionException : public std::exception
    {
    public:
        AssertionException(const std::string &statement, const char *file, int line, const char *func);

        const char *what() const noexcept override
        {
            return message.c_str();
        }


    private:
        std::string message;

    };
}