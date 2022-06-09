#pragma once
#include <cstdint>

namespace SDG
{
    enum class TimeUnit
    {
        Milliseconds,
        Seconds,
        Minutes,
        Hours,
        Days
    };

    /// Convert millisecond "ticks" to another time unit
    double TimeAs(uint64_t ms, TimeUnit unit);
}
