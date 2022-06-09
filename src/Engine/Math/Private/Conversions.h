/* =============================================================================
 * Conversions
 * 
 * 
 * ===========================================================================*/
#pragma once
#include <SDL_gpu.h>
#include "../Rectangle.h"

namespace SDG::Conv
{
    inline GPU_Rect ToGPURect(const SDG::FRectangle &rect)
    {
        return {rect.X(), rect.Y(), rect.Width(), rect.Height()};
    }

    inline SDG::FRectangle ToSDGFRect(const GPU_Rect &rect)
    {
        return {rect.x, rect.y, rect.w, rect.h};
    }

    inline GPU_Rect ToGPURect(const SDG::Rectangle &rect)
    {
        return {(float)rect.X(), (float)rect.Y(),
                (float)rect.Width(), (float)rect.Height()};
    }

    inline SDG::Rectangle ToSDGRect(const GPU_Rect &rect)
    {
        return {(int)rect.x, (int)rect.y,
                (int)rect.w, (int)rect.h};
    }
}
