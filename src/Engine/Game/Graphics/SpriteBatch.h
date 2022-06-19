/* ====================================================================================================================
 * @file SpriteBatch.h
 * @class SDG::SpriteBatch
 * Renders images in batches, with settings for each batch, such as depth sorting, render target, 
 * matrix transformation, etc.
 *
 * ==================================================================================================================*/
#pragma once

#include <Engine/Graphics/Flip.h>
#include <Engine/Graphics/Window.h>
#include <Engine/Graphics/Texture.h>
#include <Engine/Graphics/Private/GPU_Target_Fwd.h>

#include <Engine/Lib/ClassMacros.h>
#include <Engine/Lib/Ref.h>
#include <Engine/Lib/Unique.h>
#include <Engine/Math/Rectangle.h>

#include <vector>

namespace SDG
{
    /// SpriteBatch depth sort mode.
    enum class SortMode
    {
        /// No sorting. Depth results from the order of calls to SpriteBatch rendering
        None,
        /// Sort by texture ptr
        Texture,
        /// Uses depth parameter to sort. Lower depth values in front; higher in back.
        FrontToBack,
        /// Uses depth parameter to sort. Higher depth values in front; lower in back.
        BackToFront
    };

    class SpriteBatch
    {
        struct Impl;
        SDG_NOCOPY(SpriteBatch);
    public:
        SpriteBatch();
        ~SpriteBatch();

        bool Initialize(Ref<Window> context);

        /// Starts a render batch. Must be paired with a call to End
        /// @param target - target to blit textures to. If not provided, the last Window or RenderTarget set as active target will be used.
        /// @param transformMatrix - matrix by which to transform each image. This object should be alive at least until after End is called. (optional)
        /// @param sortMode - method by which to sort the render order of the batch. (optional: default is front to back)
        void Begin(Ref<class RenderTarget> target = nullptr,
            Ref<const class Matrix4x4> transformMatrix = nullptr,
            SortMode sortMode = SortMode::FrontToBack);

        /// Sorts and renders batch
        void End();
        void DrawTexture(const Texture *texture, const Rectangle &src, const FRectangle &dest, float rotation, const Vector2 &anchor, Flip flip, const Color &color, float depth);

        /// Quick and easy draw
        void DrawTexture(const Texture *texture, const Vector2 &position, const Vector2 &scale = Vector2{ 1.f, 1.f },
            const Vector2 &normAnchor = Vector2{.5f, .5f}, float rotation = 0, float depth = 0, const Color &color = Color::White());
        void DrawRectangle(const FRectangle &rect, const Vector2 &anchor, const Color &color, float rotation = 0, float depth = 0);
        void DrawLine(const Vector2 &a, const Vector2 &b, float thickness, const Color &color, float depth);
        void DrawLine(const Vector2 &base, float length, float angle, float thickness, const Color &color, float depth);
        void DrawLines(const std::vector<Vector2> &points, float thickness, const Color &color, float depth);
    private:    
        void RenderBatches();
        void SortBatches();
        
        Impl *impl;
    };
}
