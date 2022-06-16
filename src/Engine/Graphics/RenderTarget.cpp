/// RenderTarget implementation file
#include "RenderTarget.h"

#include "Private/TranslateFlip.h"
#include "Private/Conversions.h"
#include "Texture.h"

#include <Engine/Math/Private/Conversions.h>

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
    RenderTarget::EmplaceTarget(GPU_Target *pTarget)
    {
        Close(); // Make sure we're working with a clean slate

        target = std::move(pTarget);
        return *this;
    }

    auto
    RenderTarget::Target() -> GPU_Target *
    {
        return target;
    }

    auto
    RenderTarget::Target() const -> const GPU_Target *
    {
        return target;
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
    RenderTarget::DrawTexture(Ref<Texture> texture, Rectangle src, FRectangle dest,
                              float rotation, Vector2 anchor, Flip flip)
    {
        // Create rects
        GPU_Rect gpuSrc = Conv::ToGPURect(src);
        GPU_Rect gpuDest = Conv::ToGPURect(dest);

        // Blit to the current target
        GPU_BlitRectX((GPU_Image *)texture->Image(), &gpuSrc, target,
                      &gpuDest, rotation, anchor.X(), anchor.Y(),
                      TranslateFlip[(int)flip]);
    }

    auto RenderTarget::DrawRectangle(FRectangle rect) -> void
    {
        GPU_Rectangle2(target,
                       Conv::ToGPURect(rect),
                       target->color);
    }

    auto RenderTarget::DrawCircle(Circle circle) -> void
    {
        GPU_CircleFilled(target, circle.X(), circle.Y(), circle.Radius(),
            target->color);
    }

    auto RenderTarget::MakeActiveTarget() -> void
    {
        GPU_SetActiveTarget(target);
    }

    auto RenderTarget::IsOpen() const -> bool
    {
        return static_cast<bool>(target);
    }
}
