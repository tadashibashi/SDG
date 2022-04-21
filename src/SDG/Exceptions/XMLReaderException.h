//
// Created by Aaron Ishibashi on 4/21/22.
//
#pragma once
#include <stdexcept>
#include <string>

namespace SDG
{
    class XMLReaderException : public std::exception
    {
    public:
        XMLReaderException(const std::string &doing, int error);

        const char *what() const noexcept override
        {
            return message.c_str();
        }


    private:
        std::string message;

    };
}

