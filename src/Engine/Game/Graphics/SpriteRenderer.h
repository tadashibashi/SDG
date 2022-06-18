#pragma once
#include <Engine/Graphics/Color.h>
#include <Engine/Graphics/Flip.h>

#include <Engine/Math/Vector2.h>
#include <Engine/Math/Math.h>
#include <Engine/Lib/Ref.h>

namespace SDG
{
    class SpriteRenderer
    {
    public:
        SpriteRenderer();

        // Driver

        void Render(Ref<class SpriteBatch> spriteBatch) const;
        void Update(float deltaSeconds);

        // Getters / Setters

        SpriteRenderer &Paused(bool paused) { this->paused = paused; return *this; }
        bool Paused() const { return paused; }

        SpriteRenderer &Position(float x, float y) { position.Set(x, y); return *this; }
        SpriteRenderer &Position(Vector2 position) { this->position = position; return *this; }
        const Vector2 &Position() const { return position; }

        SpriteRenderer &Scale(float x, float y) { scale.Set(x, y); return *this; }
        SpriteRenderer &Scale(Vector2 scale) { this->scale = scale; return *this; }
        const Vector2 &Scale() const { return scale; }

        /// Angle in degrees to project the image
        /// Automatically wrapped between 0 and 360 degrees
        SpriteRenderer &Angle(float angle);
        float Angle() const { return angle; }

        SpriteRenderer &Speed(float speed) { this->speed = speed; return *this; }
        float Speed() const { return speed; }

        SpriteRenderer &Fps(float fps) { this->fps = fps; return *this; }
        float Fps() const { return fps; }

        SpriteRenderer &Flip(SDG::Flip flip) { this->flip = flip; return *this; }
        SDG::Flip Flip() const { return flip; }

        SpriteRenderer &Index(float index);
        float Index() const { return index; }

        SpriteRenderer &Depth(float depth) { this->depth = depth; return *this; }
        float Depth() const { return depth; }

        SpriteRenderer &Tint(Color tint) { this->tint = tint;  return *this; }
        Color Tint() const { return tint; }

        SpriteRenderer &Sprite(Ref<const class Sprite> sprite) { this->sprite = sprite; return *this; }
        Ref<const class Sprite> Sprite() const { return sprite; }

    private:
        Ref<const class Sprite> sprite;
        Vector2 position;
        Vector2 scale;
        SDG::Flip flip;
        float angle; // in degrees
        float fps;
        float speed; // speed multiplier, default 1
        bool paused;
        float index;
        float depth;

        Color tint;
    };
}