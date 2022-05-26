/*!
 * @file Frame.h
 * @namespace SDG
 * @class Frame
 * Information for rendering a rectangle frame from a larger atlas
 * 
 */
#pragma once
#include <SDG/Math/Vector2.h>
#include <SDG/Math/Rectangle.h>
#include <SDG/Ref.h>
#include <SDG/String.h>

namespace SDG
{
    class Frame
    {
    public:
        /// Gets the source Rect
        const Rectangle &FrameRect() const { return frameRect;  }
        /// Gets the full original size of the image
        const Rectangle &ImageRect() const { return origRect;  }
        Rectangle OffsetRect() const 
        { 
            return Rectangle(
                frameRect.X() - origRect.X(),
                frameRect.Y() - origRect.Y(),
                frameRect.Width() - origRect.Width(),
                frameRect.Height() - origRect.Height()); 
        }

        /// Gets whether the rectangle is rotated 90 degrees
        bool Rotated() const { return rotated;  }

        /// Gets the texture from which this frame originates
        CRef<class Texture2D> Texture() const { return texture; }

        /// Gets the frame name
        const String &Name() const { return name; }
    private:
        Point anchor;
        Rectangle frameRect;
        Rectangle origRect;
        bool rotated;
        CRef<class Texture2D> texture;
        String name;
    };
}