/*!
 * @file SpriteBatch.h
 * @namespace SDG
 * @class SpriteBatch
 * Renders images, with ability to specify transformation matrix,
 * depth sorting, render target, etc.
 * 
 */
#pragma once

#include <SDG/ClassMacros.h>
#include <SDG/Graphics/Texture2D.h>
#include <SDG/Graphics/Window.h>
#include <SDG/Math/Rectangle.h>
#include <SDG/Ref.h>
#include "Flip.h"

namespace SDG
{
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
        SDG_NOCOPY(SpriteBatch);
    public:
        SpriteBatch();
        ~SpriteBatch() = default;

        void Begin(Ref<class RenderTarget> target, 
            CRef<class Matrix4x4> transformMatrix = CRef<class Matrix4x4>{}, 
            SortMode sort = SortMode::FrontToBack);
        void End();
        void DrawTexture(Texture2D *texture, Rectangle src, FRectangle dest, float rotation, Vector2 anchor, Flip flip, Color color, float depth);

        /// Quick and easy draw
        void DrawTexture(Texture2D *texture, Vector2 position, Vector2 scale = Vector2(1.f, 1.f),
                         Vector2 normAnchor = Vector2(.5f, .5f),
                         float rotation = 0, float depth = 0, Color color = Color::White());
    private:
        struct BatchCall;
        void RenderBatches();
        void SortBatches();
        
        std::vector<BatchCall>   batch;
        SortMode                 sortMode;
        Ref <class RenderTarget> target;
        CRef<class Matrix4x4>    matrix;
    };

    struct SpriteBatch::BatchCall 
    {
        BatchCall(Texture2D *texture, Rectangle src, FRectangle dest, float rotation,
                    Vector2 anchor, Flip flip, Color color, float depth);
        Texture2D *texture;
        Rectangle  src;
        FRectangle dest;
        float      rotation;
        Vector2    anchor;
        Flip       flip;
        Color      color;
        float      depth;
    };
}
