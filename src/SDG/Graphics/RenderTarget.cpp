#include "RenderTarget.h"
#include "Private/TranslateFlip.h"
#include "Texture2D.h"
#include "Private/Conversions.h"
#include <SDG/Math/Private/Conversions.h>
#include <SDL_gpu.h>

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

    Color
    RenderTarget::DrawColor() const
    {
        return Conv::ToSDGColor(target->color);
    }

    void
    RenderTarget::Clear(SDG::Color color)
    {
        GPU_ClearColor(target, {color.R(), color.G(), color.B(), color.A()});
    }

    void
    RenderTarget::SwapBuffers()
    {
        GPU_Flip(target);
    }

    RenderTarget &
    RenderTarget::DrawColor(SDG::Color color)
    {
        GPU_SetTargetColor(target, Conv::ToSDLColor(color));
        return *this;
    }

    void
    RenderTarget::DrawTexture(Ref<Texture2D> texture, Rectangle src, FRectangle dest,
                              float rotation, Vector2 anchor, Flip flip)
    {
        // Create rects
        GPU_Rect gpuSrc = Conv::ToGPURect(src);
        GPU_Rect gpuDest = Conv::ToGPURect(dest);

        // Blit to the current target
        GPU_BlitRectX(texture->Image().Get(), &gpuSrc, target,
                      &gpuDest, rotation, anchor.X(), anchor.Y(),
                      TranslateFlip[(int)flip]);
    }

    void RenderTarget::DrawRectangle(FRectangle rect)
    {
        GPU_Rectangle2(target,
                       Conv::ToGPURect(rect),
                       target->color);
    }

    void RenderTarget::MakeCurrent()
    {
        GPU_SetCurrentRenderer(target->renderer->id);
        GPU_SetActiveTarget(target);
    }

    bool RenderTarget::IsOpen()
    {
        return target;
    }
}
