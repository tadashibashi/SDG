#pragma once

#include <SDG/Graphics/Texture2D.h>
#include <SDG/Graphics/Window.h>
#include <SDG/Math/Rectangle.h>

class GPU_Target;

namespace SDG
{
    enum class SortMode
    {
        Texture,
        FrontToBack,
        BackToFront
    };
    enum class Flip
    {
        None = 0,
        Horizontal,
        Vertical,
        Both
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

        // TODO: Wrap gpu target in either a layer, or pass the window into the SpriteBatch to get target
        void Begin(GPU_Target *target, SortMode sort = SortMode::FrontToBack);
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
        GPU_Target *target;
    };
}
