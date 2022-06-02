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

#include <SDG/Math/Rectangle.h>
#include <SDG/Math/Vector2.h>
#include <SDG/Lib/Ref.h>
#include <SDG/Math/Circle.h>

// forward declaration
struct GPU_Target;
typedef struct GPU_Target GPU_Target;

namespace SDG
{
    class RenderTarget
    {
    public:
        RenderTarget();

        /// Receive a render target from another source.
        /// RenderTarget becomes the owner of this target.
        explicit RenderTarget(Ref<GPU_Target> ref);
        ~RenderTarget();

        /*!
         * Sets the internal target. Frees any pre-existing target.
         * This object is now the owner of the GPU_Target object
         * @param pTarget the target to set
         * @return this object reference for chaining
         */
        RenderTarget &EmplaceTarget(Ref<GPU_Target> pTarget);


        void MakeActiveTarget();

        /*!
         * Gets the target's viewport rectangle
         * @return the viewport rectangle
         */
        [[nodiscard]] Rectangle Viewport() const;

        /// Sets the target's viewport rectangle
        /// @param viewport rectangle to set
        /// @return this object reference for chaining
        RenderTarget &Viewport(Rectangle viewport);


        /*!
         * Gets the virtual dimensions of the target
         * @return Point containing width and height of the target
         */
        [[nodiscard]] Point Size() const;

        /// Gets the true underlying dimensions of the target
        /// @return Point containing width and height of the target
        [[nodiscard]] Point BaseSize() const;

        /// Gets the current rendering color
        Color DrawColor() const;

        /// Sets the rendering color. Cumulative effect with image color.
        RenderTarget &DrawColor(Color color);

        void DrawTexture(Ref<class Texture> texture, Rectangle src,
            FRectangle dest, float rotation, Vector2 anchor, Flip flip);
        void DrawRectangle(FRectangle rect);
        void DrawCircle(Circle circle);
        /*!
         * Gets the internal GPU_Target. Please include SDL_gpu.h in
         * order to access the internals and functions.
         * @return the raw SDL_gpu GPU_Target reference
         */
        [[nodiscard]] Ref<GPU_Target> Target() const;

        bool IsOpen();

        /*!
         * Frees the internal GPU_Target.
         * This function is safe to call even
         * if the target has already been freed, and is automatically called
         * during ~RenderTarget()
         */
        void Close();

        void Clear(Color color = Color::CornflowerBlue());
        void SwapBuffers();

        /// Will evaluate to true or false if the internal target is null or not.
        operator bool() const;

    private:
        GPU_Target *target;
    };
}
