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
#include <Engine/Graphics/Texture.h>

namespace SDG
{
    /// Contains the necessary information to display a source rectangle of a 
    /// Texture image
    class Frame
    {
    public:
        Frame() : frameRect(), origRect(), rotated(), anchor(), 
            texture() { }
        Frame(const Rectangle &frame, const Rectangle &origRect, bool rotated,
            const Point &anchor, const Texture *texture) :
                      frameRect(frame), origRect(origRect), rotated(rotated),
                      anchor(anchor), texture(texture) { }

        /// Gets the source Rect
        [[nodiscard]] auto FrameRect() const noexcept -> const Rectangle & { return frameRect;  }
        /// Gets the full original size of the image
        [[nodiscard]] auto ImageRect() const noexcept -> const Rectangle & { return origRect;  }

        /// The difference between the original image rect and the frame
        [[nodiscard]] auto OffsetRect() const noexcept -> Rectangle
        { 
            return Rectangle(
                    origRect.X() - frameRect.X(),
                    origRect.Y() - frameRect.Y(),
                    origRect.Width() - frameRect.Width(),
                    origRect.Height() - frameRect.Height());
        }

        /// Gets the angle; either 0 or 90 degrees
        [[nodiscard]] auto Angle() const noexcept -> float { return rotated ? 90.f : 0;  }

        [[nodiscard]] auto Anchor() const noexcept -> Point { return anchor; }

        /// Gets the texture from which this frame originates
        [[nodiscard]] auto Texture() const noexcept -> const Texture * { return texture; }
        
    private:
        Point anchor;
        Rectangle frameRect;
        Rectangle origRect;
        bool rotated;
        const class Texture *texture;
    };
}
