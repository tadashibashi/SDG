#include "Time.h"
#include "SDL.h"
#include <SDG/Exceptions/InvalidArgumentException.h>

namespace SDG
{
    Time::Time():
            deltaTicks_(0), ticks_(0) { }

    void Time::Update()
    {
        Uint64 currentTicks = SDL_GetTicks64();
        deltaTicks_ = currentTicks - ticks_;
        ticks_ = currentTicks;
    }

    uint64_t Time::Now() const
    {
        return SDL_GetTicks64();
    }

    uint64_t Time::Ticks() const
    {
        return ticks_;
    }

    double Time::As(Time::Unit unit)
    {
        switch(unit)
        {
            case Unit::Milliseconds: return ticks_;
            case Unit::Seconds: return ticks_ * 0.001;
            case Unit::Minutes: return ticks_ * 0.001 / 60.0;
            case Unit::Hours: return ticks_ * 0.001 / 3600.0;
            default:
                throw InvalidArgumentException("Time::As", "unit",
                                               "Unit enum value not recognized");
        }
    }

    uint64_t Time::DeltaTicks(unsigned cap) const
    {
        return cap ? SDL_min(deltaTicks_, cap) : deltaTicks_;
    }
}