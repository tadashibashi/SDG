#pragma once
#include "RuntimeException.h"

namespace SDG
{
    /// Exception intended for indexers that have exceeded a container's bounds.
    class OutOfRangeException : public RuntimeException
    {
    public:
        OutOfRangeException(int64_t value, const String &info);
    };
}
