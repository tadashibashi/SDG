#include "TimeUnit.h"
#include <Engine/Exceptions.h>

double SDG::TimeAs(uint64_t ms, SDG::TimeUnit unit)
{
    switch (unit)
    {
    case TimeUnit::Milliseconds: return ms;
    case TimeUnit::Seconds: return ms * 0.001;
    case TimeUnit::Minutes: return ms / 60000.0;
    case TimeUnit::Hours: return ms / 3600000.0;
    case TimeUnit::Days: return ms / 86400000.0;
    default:
        throw InvalidArgumentException("AppTime::As", "unit",
            "Unit enum value not recognized");
    }
}
