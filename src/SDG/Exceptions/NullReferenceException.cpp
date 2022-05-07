//
// Created by Aaron Ishibashi on 5/6/22.
//
#include "NullReferenceException.h"

SDG::NullReferenceException::NullReferenceException(const std::type_index &type)
        : std::exception(), message()
{
    message = "Null reference of type " + std::string(type.name());
}

const char *
SDG::NullReferenceException::what() const noexcept
{
    return message.c_str();
}
