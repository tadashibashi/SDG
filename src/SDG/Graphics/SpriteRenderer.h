#pragma once
#include "Color.h"
#include "Flip.h"

#include <SDG/Math/Vector2.h>
#include <SDG/Math/Math.h>
#include <SDG/Lib/Ref.h>

namespace SDG
{
    class SpriteRenderer
    {
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
        SpriteRenderer &Scale(Vector2 position) { this->scale = scale; return *this; }
        const Vector2 &Scale() const { return scale; }

        SpriteRenderer &Angle(float angle) { this->angle = angle; return *this; }
        float Angle() const { return angle; }

        SpriteRenderer &Speed(float speed) { this->speed = speed; return *this; }
        float Speed() const { return speed; }

        SpriteRenderer &Fps(float fps) { this->fps = fps; return *this; }
        float Fps() const { return fps; }

        SpriteRenderer &Flip(SDG::Flip flip) { this->flip = flip; return *this; }
        SDG::Flip Flip() const { return flip; }

        SpriteRenderer &Index(float index) { this->index = index; return *this; }
        float Index() const { return index; }

        SpriteRenderer &Depth(float depth) { this->depth = depth; return *this; }
        float Depth() const { return depth; }

        SpriteRenderer &Tint(Color tint) { this->tint = tint;  return *this; }
        Color Tint() const { return tint; }

    private:
        Ref<class Sprite> sprite;
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