/*!
 * @file Frame.h
 * @namespace SDG
 * @class Frame
 * Information for rendering a rectangle frame from a larger atlas
 * 
 */
#pragma once
#include <SDG/Lib/Ref.h>
#include <SDG/Lib/String.h>
#include <SDG/Math/Rectangle.h>
#include <SDG/Math/Vector2.h>

namespace SDG
{
    class Frame
    {
    public:
        Frame(const Rectangle &frame, const Rectangle &origRect, bool rotated,
              const Point &anchor, const String &name,
              CRef<class Texture2D> texture) :
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
        CRef<class Texture2D> Texture() const noexcept { return texture; }

        /// Gets the frame name
        const String &Name() const noexcept { return name; }

    private:
        Point anchor;
        Rectangle frameRect;
        Rectangle origRect;
        bool rotated;
        CRef<class Texture2D> texture;
        String name;
    };
}
