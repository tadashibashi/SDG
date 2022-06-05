#pragma once
#include "RuntimeException.h"

namespace SDG
{
    class DivisionByZeroException : public RuntimeException
    {
    public:
        DivisionByZeroException(const String &str = String()) : RuntimeException(
            String("Division by zero error") + (str.Empty() ? "" : ": " + str)) { }
    };
}
