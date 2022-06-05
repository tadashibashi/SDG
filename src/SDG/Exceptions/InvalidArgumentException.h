#pragma once
#include "Exception.h"

namespace SDG
{
    class InvalidArgumentException : public Exception
    {
    public:
        InvalidArgumentException(const String &func, const String &arg);
        InvalidArgumentException(const String &func, const String &arg,
            const String &info);
    };
}
