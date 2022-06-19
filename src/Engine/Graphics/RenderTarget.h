/*!
 * @file RenderTarget.h
 * @namespace SDG
 * @class RenderTarget
 * Specifies a RenderTarget used to blit graphics to and display.
 * 
 */
#pragma once
#include "Color.h"
#include "Flip.h"

#include <Engine/Math/Rectangle.h>
#include <Engine/Math/Vector2.h>
#include <Engine/Lib/Ref.h>
#include <Engine/Math/Circle.h>

#include "Private/GPU_Target_Fwd.h"

namespace SDG
{
    class RenderTarget
    {
    public:
        RenderTarget();

        /// Receive a render target from another source.
        /// RenderTarget becomes the owner of this target.
        explicit RenderTarget(GPU_Target *ref);
        ~RenderTarget();

        /*!
         * Sets the internal target. Frees any pre-existing target.
         * This object is now the owner of the GPU_Target object
         * @param pTarget the target to set
         * @return this object reference for chaining
         */
        RenderTarget &EmplaceTarget(GPU_Target *pTarget);

        auto MakeActiveTarget()->void;

        /*!
         * Gets the target's viewport rectangle
         * @return the viewport rectangle
         */
        [[nodiscard]] auto Viewport() const->Rectangle;

        /// Sets the target's viewport rectangle
        auto Viewport(Rectangle viewport)->RenderTarget &;


        /*!
         * Gets the virtual dimensions of the target
         * @return Point containing width and height of the target
         */
        [[nodiscard]] auto Size() const->Point;

        /// Gets the true underlying dimensions of the target
        /// @return Point containing width and height of the target
        [[nodiscard]] auto BaseSize() const->Point;

        /// Gets the current rendering color
        [[nodiscard]] auto DrawColor() const->Color;

        /// Sets the rendering color. Cumulative effect with image color.
        auto DrawColor(Color color)->RenderTarget &;

        auto DrawTexture(Ref<class Texture> texture, Rectangle src,
            FRectangle dest, float rotation, Vector2 anchor, Flip flip)->void;
        auto DrawRectangle(FRectangle rect)->void;
        auto DrawCircle(Circle circle)->void;

        [[nodiscard]] auto Target()->Ref<GPU_Target>;
        [[nodiscard]] auto Target() const->Ref<const GPU_Target>;

        [[ nodiscard]] auto IsOpen() const -> bool;

        /// Frees the internal GPU_Target.
        /// Safe to call even if the target has already been freed, and is automatically called during ~RenderTarget()
        auto Close()->void;

        auto Clear(Color color = Color::CornflowerBlue())->void;
        auto SwapBuffers()->void;

        /// Will evaluate to true or false if the internal target is null or not.
        operator bool() const;
    private:
        GPU_Target *target;
    };
}
