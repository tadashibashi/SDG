#pragma once
#include "LogicException.h"

namespace SDG
{
    class InvalidArgumentException : public LogicException
    {
    public:
        InvalidArgumentException(const String &func, const String &arg);
        InvalidArgumentException(const String &func, const String &arg,
            const String &info);
        const char *Name() const noexcept override { return "InvalidArgumentException"; }
    };
}
