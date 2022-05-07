//
// Created by Aaron Ishibashi on 5/6/22.
//
#pragma once
#include <exception>
#include <typeindex>
#include <string>

namespace SDG
{
    class NullReferenceException : std::exception {
    public:
        NullReferenceException(const std::type_index &type);
        const char *what() const noexcept override;
    private:
        std::string message;
    };
}
