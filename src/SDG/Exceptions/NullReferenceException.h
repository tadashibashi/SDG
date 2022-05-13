//
// Created by Aaron Ishibashi on 5/6/22.
//
#pragma once
#include "Exception.h"
#include <string>

namespace SDG
{
    class NullReferenceException : public Exception
    {
    public:
        NullReferenceException() : typeName() { }
        explicit NullReferenceException(const std::string &typeName)
            : typeName(typeName) { }
    private:
        void What(std::ostream &stream) const override;
        std::string typeName;
    };
}
