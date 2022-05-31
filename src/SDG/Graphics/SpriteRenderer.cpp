#include "SpriteRenderer.h"
#include "Sprite.h"
#include "SpriteBatch.h"

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
        index = fmodf(deltaSeconds * fps * speed + index, (float)sprite->Size());
    }
}
