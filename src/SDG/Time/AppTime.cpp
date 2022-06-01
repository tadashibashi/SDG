#include "AppTime.h"
#include <SDG/Exceptions/InvalidArgumentException.h>

#include <SDL_timer.h>

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

    Duration AppTime::Now() const
    {
        return Duration(SDL_GetTicks64());
    }

    uint64_t AppTime::Ticks() const
    {
        return ticks_;
    }

    double AppTime::As(TimeUnit unit) const
    {
        return TimeAs(ticks_, unit);
    }

    uint64_t AppTime::DeltaTicks(unsigned cap) const
    {
        return cap ? SDL_min(deltaTicks_, cap) : deltaTicks_;
    }
}
