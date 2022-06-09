#include "Chronogram.h"
#include <SDL_timer.h>

void SDG::Chronogram::Start()
{
    marker = SDL_GetTicks64();
}

double SDG::Chronogram::Check(TimeUnit units) const
{
    return TimeAs(SDL_GetTicks64() - marker, units);
}

double SDG::Chronogram::GetStartTime(TimeUnit units) const
{
    return TimeAs(marker, units);
}
