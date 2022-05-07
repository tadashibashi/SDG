//
// Created by Aaron Ishibashi on 5/7/22.
//

#pragma once
#include <stdexcept>
#include <string>
namespace SDG
{
    class InvalidArgumentException : std::exception
    {
    public:
        InvalidArgumentException(const char *func, const char *arg,
                                 const char *info = nullptr);
        const char *what() const noexcept override;
    private:
        std::string message;
    };
}
