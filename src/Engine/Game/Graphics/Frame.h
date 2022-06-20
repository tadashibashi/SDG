/* ====================================================================================================================
 * @file Frame.h - SDG_Engine
 * @author Aaron Ishibashi
 * 
 * @class Frame
 * Information for rendering a rectangle frame from a larger atlas
 * ==================================================================================================================*/
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
        Frame(const Rect_<uint16_t> &frame, const Rect_<uint16_t> &origRect, bool rotated,
            const Vec2_<uint16_t> &anchor, const Texture *texture) :
                      frameRect(frame), origRect(origRect), rotated(rotated),
                      anchor(anchor), texture(texture) { }

        /// Gets the source Rect
        [[nodiscard]] auto &FrameRect() const noexcept { return frameRect;  }
        /// Gets the full original size of the image
        [[nodiscard]] auto &ImageRect() const noexcept { return origRect;  }

        /// Add this to the FrameRect X and Y positions to get the original image projection coordinates.
        /// @param withAnchor - true: includes anchor offset from the {0, 0} of original image.
        /// false: calculates from the {0, 0} position of the original image
        [[nodiscard]] auto OffsetPos(bool withAnchor) const noexcept -> Point
        {
            /// todo: may need to swap x's and y's, if rotated... check with crunch algorithm
            return withAnchor ? 
                Point {
                    (int)origRect.X() - (int)frameRect.X() - (int)anchor.X(),
                    (int)origRect.Y() - (int)frameRect.Y() - (int)anchor.Y()
                } : Point {
                    (int)origRect.X() - (int)frameRect.X(),
                    (int)origRect.Y() - (int)frameRect.Y(),
                };
        }

        /// Gets the angle; either 0 or -90 degrees if rotated
        [[nodiscard]] auto Angle() const noexcept -> float { return rotated ? -90.f : 0;  }

        [[nodiscard]] auto Anchor() const noexcept { return anchor; }

        /// Gets the texture from which this frame originates
        [[nodiscard]] auto Texture() const noexcept -> const Texture * { return texture; }
        
    private:
        Vec2_<uint16_t> anchor;
        Rect_<uint16_t> frameRect;
        Rect_<uint16_t> origRect;
        bool      rotated;
        const class Texture *texture;
    };
}
