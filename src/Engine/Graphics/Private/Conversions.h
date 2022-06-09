/* =============================================================================
 * Conversions
 * 
 * 
 * ===========================================================================*/
#pragma once
#include <SDL.h>
#include "../Color.h"

namespace SDG::Conv
{
    inline SDL_Color ToSDLColor(const Color &color)
    {
        return {color.R(), color.G(), color.B(), color.A()};
    }

    inline SDG::Color ToSDGColor(const SDL_Color &color)
    {
        return {color.r, color.g, color.b, color.a};
    }
}
