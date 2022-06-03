/*!
 * @file SpriteBatch.h
 * @namespace SDG
 * @class SpriteBatch
 * Renders images, with ability to specify transformation matrix,
 * depth sorting, render target, etc.
 * 
 */
#pragma once

#include "Flip.h"
#include "Texture.h"
#include "Window.h"

#include <SDG/Lib/ClassMacros.h>
#include <SDG/Lib/Ref.h>
#include <SDG/Math/Rectangle.h>

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

        bool Initialize(Ref<Window> context);
        void Begin(Ref<class RenderTarget> target, 
            CRef<class Matrix4x4> transformMatrix = CRef<class Matrix4x4>{}, 
            SortMode sort = SortMode::FrontToBack);
        void End();
        void DrawTexture(CRef<Texture> texture, Rectangle src, FRectangle dest, float rotation, Vector2 anchor, Flip flip, Color color, float depth);

        /// Quick and easy draw
        void DrawTexture(CRef<Texture> texture, Vector2 position, Vector2 scale = Vector2(1.f, 1.f),
                         Vector2 normAnchor = Vector2(.5f, .5f),
                         float rotation = 0, float depth = 0, Color color = Color::White());
        void DrawRectangle(FRectangle rect, Vector2 anchor, Color color, float rotation = 0, float depth = 0);
    private:    
        struct BatchCall;

        void RenderBatches();
        void SortBatches();
        
        std::vector<BatchCall>   batch;
        SortMode                 sortMode;
        Ref <class RenderTarget> target;
        CRef<class Matrix4x4>    matrix;
        Texture                  pixel;

    };



    struct SpriteBatch::BatchCall 
    {
        BatchCall(CRef<Texture> texture, Rectangle src, FRectangle dest, float rotation,
                    Vector2 anchor, Flip flip, Color color, float depth);
        CRef<Texture> texture;
        Rectangle src;
        FRectangle dest;
        float      rotation;
        Vector2    anchor;
        Color      color;
        Flip       flip;
        float      depth;
    };



}
