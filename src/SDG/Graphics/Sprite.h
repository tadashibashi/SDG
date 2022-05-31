/*!
 * @file Sprite.h
 * @namespace SDG
 * @class Sprite
 * Contains data and functions for sprite rendering
 * 
 */
#pragma once
#include "Frame.h"
#include <SDG/Templates/Array.h>

namespace SDG
{
    class Sprite
    {
    public:
        Sprite(const Array<Frame> &frames, 
            const Array<unsigned> &reel);
        const Frame &operator [] (unsigned index) const;
        const Frame &At(unsigned index) const;

        size_t Size() const;
        bool Empty() const;
    private:
        Array<Frame> frames;
        Array<unsigned> reel;
    };
}