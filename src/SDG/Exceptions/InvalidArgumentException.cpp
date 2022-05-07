//
// Created by Aaron Ishibashi on 5/7/22.
//

#include "InvalidArgumentException.h"

namespace SDG
{
    InvalidArgumentException::InvalidArgumentException(
            const char *func, const char *arg, const char *info) : message()
    {
        message = std::string("Invalid argument passed to ") + func +
                std::string(". Argument name: ") + arg;
        if (info)
            message += std::string(": ") + info;
    }

    const char *
    InvalidArgumentException::what() const noexcept
    {
        return message.c_str();
    }
}