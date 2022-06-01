#include "TimeUnit.h"
#include <SDG/Exceptions/InvalidArgumentException.h>

double SDG::TimeAs(uint64_t ms, SDG::TimeUnit unit)
{
    switch (unit)
    {
    case TimeUnit::Milliseconds: return ms;
    case TimeUnit::Seconds: return ms * 0.001;
    case TimeUnit::Minutes: return ms * 0.001 / 60.0;
    case TimeUnit::Hours: return ms * 0.001 / 3600.0;
    default:
        throw InvalidArgumentException("AppTime::As", "unit",
            "Unit enum value not recognized");
    }
}