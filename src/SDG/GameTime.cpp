#include "GameTime.h"
#include <SDL.h>

static const int8_t MAX_DELTA_TICKS = 64;

namespace SDG
{
    GameTime::GameTime():
            deltaTicks_(0), ticks_(0) { }

    void GameTime::Update()
    {
        Uint64 currentTicks = SDL_GetTicks64();
        deltaTicks_ = SDL_min(currentTicks - ticks_, MAX_DELTA_TICKS);
        ticks_ = currentTicks;
    }

    uint64_t GameTime::Now() const
    {
        return SDL_GetTicks64();
    }
}