#pragma once
#include "RuntimeException.h"

namespace SDG
{
    class DivisionByZeroException : public RuntimeException
    {
    public:
        DivisionByZeroException(const String &str = String()) : RuntimeException(
            String::Format("DivisionByZeroException{}", str.Empty() ? "" : ": " + str)) { }
        const char *Name() const noexcept override { return "DivisionByZeroException"; }
    };
}
