#include "SpriteRenderer.h"
#include "Sprite.h"
#include "SpriteBatch.h"

#include <Engine/Math/Math.h>

SDG::SpriteRenderer::SpriteRenderer() : sprite(), position(), scale(1.f, 1.f),
flip(), angle(), fps(4.f), speed(1.f), paused(),
index(), depth(), tint(Color::White()) { }

// todo: fix this once atlas making has been set up with crunch
void SDG::SpriteRenderer::Render(Ref<class SpriteBatch> spriteBatch) const
{
    const Frame &frame = sprite->At((unsigned)index);
    Vector2 position = this->position - frame.OffsetRect().Position();

    FRectangle dest(position, (Vector2)frame.FrameRect().Size());

    spriteBatch->DrawTexture(frame.Texture(), frame.FrameRect(), dest, frame.Angle() + angle,
        (Vector2)frame.Anchor(), flip, tint, depth);
}

void SDG::SpriteRenderer::Update(float deltaSeconds)
{
    if (!paused)
    {
        index = Math::WrapF<float>(deltaSeconds * fps * speed + index, 0.f, (float)sprite->Length());
    }
}

SDG::SpriteRenderer &
SDG::SpriteRenderer::Angle(float angle) 
{
    this->angle = Math::WrapF(angle, 0.f, 360.f); 
    return *this; 
}

SDG::SpriteRenderer &
SDG::SpriteRenderer::Index(float index) 
{ 
    this->index = sprite ? Math::WrapF<float>(index, 0.f, (float)sprite->Length()) : index; 
    return *this; 
}
