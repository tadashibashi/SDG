//
// Created by Aaron Ishibashi on 5/6/22.
//
#pragma once
#include "Exception.h"

namespace SDG
{
    class NullReferenceException : public Exception
    {
    public:
        NullReferenceException() :
            Exception("NullReferenceException") { }

        NullReferenceException(const String &message) : 
            Exception("NullReferenceException: " + message) { }

        const char *Name() const noexcept override { return "NullReferenceException"; }
    };
}
