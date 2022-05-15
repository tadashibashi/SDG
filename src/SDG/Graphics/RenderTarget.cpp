#include "RenderTarget.h"

namespace SDG
{
    RenderTarget::RenderTarget() : target()
    {

    }

    RenderTarget::~RenderTarget()
    {
        Close();
    }

    RenderTarget::RenderTarget(Ref<GPU_Target> target) : target(target.Get())
    {

    }

    RenderTarget &
    RenderTarget::EmplaceTarget(Ref<GPU_Target> pTarget)
    {
        Close(); // Make sure we're working with a clean slate

        target = pTarget.Get();
        return *this;
    }

    Ref<GPU_Target>
    RenderTarget::Target() const
    {
        return Ref{target};
    }

    Rectangle
    RenderTarget::Viewport() const
    {
        return {(int)target->viewport.x,
                (int)target->viewport.y,
                (int)target->viewport.w,
                (int)target->viewport.h};
    }

    RenderTarget &
    RenderTarget::Viewport(Rectangle viewport)
    {
        GPU_SetViewport(target, {(float)viewport.X(), (float)viewport.Y(), (float)viewport.Width(), (float)viewport.Height()});
        return *this;
    }

    Point
    RenderTarget::Size() const
    {
        return {(int)target->w, (int)target->h};
    }

    Point
    RenderTarget::BaseSize() const
    {
        return {(int)target->base_w, (int)target->base_h};
    }

    RenderTarget::operator bool() const
    {
        return static_cast<bool>(target);
    }

    void RenderTarget::Close()
    {
        if (target)
        {
            GPU_FreeTarget(target);
            target = nullptr;
        }
    }

    Color RenderTarget::Color() const
    {
        return {target->color.r, target->color.g, target->color.b, target->color.a};
    }

    void
    RenderTarget::Clear(SDG::Color color)
    {
        GPU_ClearColor(target, {color.R(), color.G(), color.B(), color.A()});
    }

    void RenderTarget::SwapBuffers()
    {
        GPU_Flip(target);
    }
}
