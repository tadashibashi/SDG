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
}
