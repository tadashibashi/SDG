#pragma once
#include "LogicException.h"

namespace SDG
{
    /// Exception intended for indexers that have exceeded a container's bounds.
    class OutOfRangeException : public LogicException
    {
    public:
        OutOfRangeException(int64_t value, const class String &info);

        const char *Name() const noexcept override { return "OutOfRangeException"; }
    };
}
