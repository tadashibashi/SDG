#include "Time.h"
#include "SDL.h"
#include <SDG/Exceptions/InvalidArgumentException.h>

static const int8_t MAX_DELTA_TICKS = 64;

namespace SDG
{
    Time::Time():
            deltaTicks_(0), ticks_(0) { }

    void Time::Update()
    {
        Uint64 currentTicks = SDL_GetTicks64();
        deltaTicks_ = SDL_min(currentTicks - ticks_, MAX_DELTA_TICKS);
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
            case Unit::Ms: return ticks_;
            case Unit::Sec: return ticks_ * 0.001;
            case Unit::Min: return ticks_ * 0.001 / 60.0;
            case Unit::Hr: return ticks_ * 0.001 / 3600.0;
            default:
                throw InvalidArgumentException("Time::As", "unit",
                                               "Unit enum value not recognized");
        }
    }
}