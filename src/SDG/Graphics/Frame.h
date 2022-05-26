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

        /// Gets whether the rectangle is rotated 90 degrees
        bool Rotated() const noexcept { return rotated;  }

        /// Gets the texture from which this frame originates
        CRef<class Texture2D> Texture() const noexcept { return texture; }

        /// Gets the relative position from the top-left corner from
        /// which rotation and the zero point will be located
        const Point &Anchor() const noexcept { return anchor; }

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