/*!
 * @file Sprite.h
 * @namespace SDG
 * @class Sprite
 * Contains data and functions for sprite rendering
 * 
 */
#pragma once
#include "Frame.h"
#include <SDG/Lib/Array.h>
#include <SDG/Lib/String.h>

namespace SDG
{
    class Sprite
    {
    public:
        Sprite();
        Sprite(const String &name, const Array<Frame> &frames, 
            const Array<unsigned> &reel);
        const Frame &operator [] (unsigned index) const;
        const Frame &At(unsigned index) const;

        size_t Length() const;
        bool Empty() const;
        const String &Name() const { return name; }
    private:
        Array<Frame> frames;
        Array<unsigned> reel;
        String name;
    };
}