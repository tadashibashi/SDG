#pragma once
#include "Exception.h"

namespace SDG
{
    class RuntimeException : public Exception
    {
    public:
        RuntimeException(const String &message) : Exception(message)
        { }

        const char *Name() const noexcept override { return "RuntimeException"; }
    };
}
