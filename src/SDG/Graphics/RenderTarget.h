//
// Wrapper for SDL_gpu's GPU_Target
//
#pragma once
#include <SDG/Ref.h>
#include <SDG/Math/Rectangle.h>
#include <SDG/Math/Vector2.h>
#include "Color.h"

struct GPU_Target;

namespace SDG
{
    class RenderTarget
    {
    public:
        RenderTarget();

        /// Receive a render target from another source.
        /// RenderTarget becomes the owner of this target.
        explicit RenderTarget(Ref<GPU_Target> ref);
        virtual ~RenderTarget();

        /*!
         * Sets the internal target. Frees any pre-existing target.
         * @param pTarget the target to set
         * @return this object reference for chaining
         */
        RenderTarget &EmplaceTarget(Ref<GPU_Target> pTarget);


        /*!
         * Gets the target's viewport rectangle
         * @return the viewport rectangle
         */
        Rectangle Viewport() const;


        /*!
         * Sets the target's viewport rectangle
         * @param viewport rectangle to set
         * @return this object reference for chaining
         */
        RenderTarget &Viewport(Rectangle viewport);


        /*!
         * Gets the true underlying dimensions of the target
         * @return Point containing width and height of the target
         */
        virtual Point Size() const;

        Color Color() const;

        /*!
         * Gets the internal GPU_Target. Please include SDL_gpu.h in
         * order to access the internals and functions.
         * @return the raw SDL_gpu GPU_Target reference
         */
        Ref<GPU_Target> Target() const;

        /*!
         * Frees the internal GPU_Target.
         * This function is safe to call even
         * if the target has already been freed, and is automatically called
         * during ~RenderTarget()
         */
        virtual void Close();

        void Clear(SDG::Color color = Color::CornflowerBlue());
        void SwapBuffers();

        /// Will evaluate to true or false if the internal target is null or not.
        operator bool() const;
    private:
        GPU_Target *target;
    };
}
