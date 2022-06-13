#pragma once
#include "Exception.h"

namespace SDG
{
    class LogicException : public Exception
    {
    public:
        LogicException(const String &message) : Exception(message)
        { }

        const char *Name() const noexcept override { return "LogicException"; }
    };
}
