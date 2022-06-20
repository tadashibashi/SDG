/* ====================================================================================================================
 * @file Sprite.h - SDG_Engine
 * @author Aaron Ishibashi
 * 
 * @class Sprite
 * Contains data for rendering an animation
 * ==================================================================================================================*/
#pragma once
#include "Frame.h"
#include <Engine/Lib/Array.h>
#include <Engine/Lib/String.h>

namespace SDG
{
    /// A series of Frames that forms an animation
    class Sprite
    {
    public:
        /// Creates an empty Sprite
        Sprite();
        Sprite(const String &name, const Array<Frame> &frames, 
            const Array<unsigned> &reel);

        auto LoadFromStrip(const String &name, Ref<class Texture> texture, size_t frameCount, Vector2 anchor = { 0.5f, 0.5f }) -> bool;

        /// Only const indexers are available, fixed
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