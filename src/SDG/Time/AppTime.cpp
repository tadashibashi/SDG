#include "AppTime.h"
#include "SDL.h"
#include <SDG/Exceptions/InvalidArgumentException.h>

namespace SDG
{
    AppTime::AppTime():
            deltaTicks_(0), ticks_(0) { }

    void AppTime::Update()
    {
        Uint64 currentTicks = SDL_GetTicks64();
        deltaTicks_ = currentTicks - ticks_;
        ticks_ = currentTicks;
    }

    uint64_t AppTime::Now() const
    {
        return SDL_GetTicks64();
    }

    uint64_t AppTime::Ticks() const
    {
        return ticks_;
    }

    double AppTime::As(TimeUnit unit) const
    {
        switch(unit)
        {
            case TimeUnit::Milliseconds: return ticks_;
            case TimeUnit::Seconds: return ticks_ * 0.001;
            case TimeUnit::Minutes: return ticks_ * 0.001 / 60.0;
            case TimeUnit::Hours: return ticks_ * 0.001 / 3600.0;
            default:
                throw InvalidArgumentException("AppTime::As", "unit",
                                               "Unit enum value not recognized");
        }
    }

    uint64_t AppTime::DeltaTicks(unsigned cap) const
    {
        return cap ? SDL_min(deltaTicks_, cap) : deltaTicks_;
    }
}