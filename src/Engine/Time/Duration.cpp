#include "Duration.h"
#include <Engine/Exceptions.h>

SDG::Duration::Duration(uint64_t sdlticks) : ticks(sdlticks) { }

SDG::Duration::Duration(long double time, TimeUnit units) : ticks()
{
    switch (units)
    {
    case TimeUnit::Days:
        ticks = (uint64_t)time * 86400000ull;
        break;
    case TimeUnit::Hours:
        ticks = (uint64_t)time * 3600000ull;
        break;
    case TimeUnit::Minutes:
        ticks = (uint64_t)time * 60000ull;
        break;
    case TimeUnit::Seconds:
        ticks = (uint64_t)time * 1000ull;
        break;
    case TimeUnit::Milliseconds:
        ticks = (uint64_t)time;
    default: // in case user passes a bad casted TimeUnit
        throw SDG::InvalidArgumentException("Duration::Duration(long double time, "
            "TimeUnit units)", "units", "TimeUnit value was invalid");
        break;
    }
}

SDG::Duration::Duration(uint64_t ms, uint64_t secs, uint64_t mins, 
    uint64_t hours, uint64_t days)
    : ticks(ms + secs * 1000ull + mins * 60000ull + hours * 3600000ull +
        days * 86400000ull)
{ }

double SDG::Duration::As(TimeUnit units) const
{
    return TimeAs(ticks, units);
}

uint16_t SDG::Duration::Days() const
{
    return (uint16_t)(ticks / 86400000.0);
}

uint16_t SDG::Duration::Hours() const
{
    return (uint16_t)(ticks / 3600000.0) % 24ull;
}

uint16_t SDG::Duration::Minutes() const
{
    return (uint64_t)(ticks / 60000.0) % 60ull;
}

uint16_t SDG::Duration::Seconds() const
{
    return (uint64_t)(ticks * 0.001) % 60ull;
}

uint16_t SDG::Duration::Milliseconds() const
{
    return ticks % 1000;
}

SDG::Duration &SDG::Duration::operator += (const SDG::Duration &other)
{
    ticks += other.ticks;
    return *this;
}

SDG::Duration &SDG::Duration::operator -= (const SDG::Duration &other)
{
    ticks -= other.ticks;
    return *this;
}

SDG::Duration &SDG::Duration::operator *= (float scalar)
{
    ticks *= scalar;
    return *this;
}

SDG::Duration &SDG::Duration::operator /= (float scalar)
{
    ticks /= scalar;
    return *this;
}

SDG::Duration operator + (const SDG::Duration &a, const SDG::Duration &b)
{
    return SDG::Duration(a) += b;
}

SDG::Duration operator - (const SDG::Duration &a, const SDG::Duration &b)
{
    return SDG::Duration(a) -= b;
}

SDG::Duration operator * (const SDG::Duration &a, float scalar)
{
    return SDG::Duration(a) *= scalar;
}

SDG::Duration operator / (const SDG::Duration &a, float scalar)
{
    if (scalar == 0)
        throw SDG::DivisionByZeroException();

    return SDG::Duration(a) /= scalar;
}
