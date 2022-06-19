#include "Strip.h"

SDG::Strip::Strip() : frames(), texture() { }

SDG::Strip::Strip(Ref<class Texture> texture, size_t frameCount, Vector2 anchor)
{
    Init(texture, frameCount, anchor);
}

auto SDG::Strip::Init(Ref<class Texture> texture, size_t frameCount, Vector2 anchor) -> bool
{
    if (frameCount == 0 || texture.Get() == nullptr) return false;

    Point size = texture->Size() / Vector2{ (float)frameCount, 1 };
    std::vector<Frame> frames;
    for (size_t i = 0; i < frameCount; ++i)
    {
        Rectangle frame{ (int)i * size.X(), 0, size.X(), size.Y() };
        frames.emplace_back(frame, frame, false, (Point)(size * anchor), texture.Get());
    }

    this->frames.swap(frames);
    this->texture = texture;

    return true;
}
