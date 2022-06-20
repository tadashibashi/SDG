#include "Sprite.h"
#include <Engine/Exceptions/OutOfRangeException.h>

namespace SDG
{
    Sprite::Sprite() : frames(), reel(), name()
    {
    }

    Sprite::Sprite(const String &name, const Array<Frame> &frames,
        const Array<unsigned> &reel)
        : frames(frames), reel(reel), name(name)
    {
        // Check that reel is within frame boundaries
        for (unsigned i : this->reel)
        {
            if (i >= this->frames.Size())
            {
                throw OutOfRangeException(i, "Sprite reel contains index "
                    "that is outside of Frame array boundaries.");
            }
        }
    }

    const Frame &Sprite::operator[] (unsigned index) const
    {
        return frames[reel[index]];
    }

    const Frame &Sprite::At(unsigned index) const
    {
        if (index >= reel.Size())
        {
            throw OutOfRangeException(index, "Sprite's max frame index: " +
                std::to_string(frames.Size() - 1));
        }

        return frames[reel[index]];
    }

    size_t Sprite::Length() const
    {
        return reel.Size();
    }

    bool Sprite::Empty() const
    {
        return reel.Empty();
    }

    auto Sprite::LoadFromStrip(const String &name, Ref<class Texture> texture, size_t frameCount, Vector2 anchor) -> bool
    {
        if (frameCount == 0 || texture.Get() == nullptr) return false;

        Point size = texture->Size() / Vector2{ (float)frameCount, 1 };
        Array<Frame> frames(frameCount);
        Array<unsigned int> reel(frameCount);
        for (size_t i = 0; i < frameCount; ++i)
        {
            Rectangle frame{ (int)i * size.X(), 0, size.X(), size.Y() };
            //frames[i] = { frame, frame, false, (Point)(size * anchor), texture.Get() };
            reel[i] = i;
        }

        this->frames = std::move(frames);
        this->reel = std::move(reel);
        this->name = name;
        return true;
    }
}
