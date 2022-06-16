/*!
 * @file Frame.h
 * @namespace SDG
 * @class Frame
 * Information for rendering a rectangle frame from a larger atlas
 * 
 */
#pragma once

#include <Engine/Lib/String.h>
#include <Engine/Math/Rectangle.h>
#include <Engine/Math/Vector2.h>
#include "Texture.h"

namespace SDG
{
    /// Contains the necessary information to display a source rectangle of a 
    /// Texture image
    class Frame
    {
    public:
        Frame() : frameRect(), origRect(), rotated(), anchor(), name(), 
            texture() { }
        Frame(const Rectangle &frame, const Rectangle &origRect, bool rotated,
            const Point &anchor, const String &name, const Texture *texture) :
                      frameRect(frame), origRect(origRect), rotated(rotated),
                      anchor(anchor), name(name), texture(texture) { }

        /// Gets the source Rect
        const Rectangle &FrameRect() const noexcept { return frameRect;  }
        /// Gets the full original size of the image
        const Rectangle &ImageRect() const noexcept { return origRect;  }

        /// The difference between the original image rect and the frame
        Rectangle OffsetRect() const noexcept
        { 
            return Rectangle(
                    origRect.X() - frameRect.X(),
                    origRect.Y() - frameRect.Y(),
                    origRect.Width() - frameRect.Width(),
                    origRect.Height() - frameRect.Height());
        }

        /// Gets the angle; either 0 or 90 degrees
        float Angle() const noexcept { return rotated ? 90.f : 0;  }

        Point Anchor() const noexcept { return anchor; }

        /// Gets the texture from which this frame originates
        const Texture *Texture() const noexcept { return texture; }

        /// Gets the frame name
        const String &Name() const noexcept { return name; }

    private:
        Point anchor;
        Rectangle frameRect;
        Rectangle origRect;
        bool rotated;
        const class Texture *texture;
        String name;
    };
}
