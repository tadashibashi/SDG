#pragma once

#include <SDG/Graphics/Texture2D.h>
#include <SDG/Graphics/Window.h>

#include <SDG/Math/Rectangle.h>
#include <SDG/Ref.h>
#include "Flip.h"

namespace SDG
{
    class RenderTarget;
    class Matrix4x4;

    /// SpriteBatch depth sort mode.
    enum class SortMode
    {
        /// Sort by texture ptr
        Texture,
        /// Uses depth parameter to sort. Lower depth values in front; higher in back.
        FrontToBack,
        /// Uses depth parameter to sort. Higher depth values in front; lower in back.
        BackToFront
    };

    class SpriteBatch
    {
        struct BatchCall
        {
            BatchCall(Texture2D *texture, Rectangle src, FRectangle dest, float rotation,
                      Vector2 anchor, Flip flip, Color color, float depth);
            Texture2D *texture;
            Rectangle src;
            FRectangle dest;
            float rotation;
            Vector2 anchor;
            Flip flip;
            Color color;
            float depth;
        };

    public:
        SpriteBatch();
        ~SpriteBatch() = default;

        // no copying
        SpriteBatch(const SpriteBatch &) = delete;
        SpriteBatch &operator=(const SpriteBatch &) = delete;

        void Begin(Ref<RenderTarget> target, CRef<Matrix4x4> transformMatrix = CRef<Matrix4x4>{}, SortMode sort = SortMode::FrontToBack);
        void End();
        void DrawTexture(Texture2D *texture, Rectangle src, FRectangle dest, float rotation, Vector2 anchor, Flip flip, Color color, float depth);

        /// Quick and easy draw
        void DrawTexture(Texture2D *texture, Vector2 position, Vector2 scale = Vector2(1.f, 1.f),
                         Vector2 normAnchor = Vector2(.5f, .5f),
                         float rotation = 0, float depth = 0, Color color = Color::White());
    private:
        void RenderBatches();
        void SortBatches();

        std::vector<BatchCall> batch;
        SortMode sortMode;
        Ref<RenderTarget> target;
        CRef<Matrix4x4> matrix;
    };
}
