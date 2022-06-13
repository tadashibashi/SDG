#include "Tile.h"
#include <Engine/Exceptions.h>

SDG::AnimatedTile::AnimatedTile(const std::initializer_list<size_t> &reel, float speed) :
    indices(nullptr), length(reel.size()), speed(speed), index(0)
{
    if (reel.size() > 0)
        indices = new size_t[]{ reel.size() };
    for (size_t i = 0; i < reel.size(); ++i)
        indices[i] = *(reel.begin() + i);
}

SDG::AnimatedTile::AnimatedTile(const AnimatedTile &tile) : indices(nullptr), length(tile.length), speed(tile.speed), index(tile.index)
{
    if (tile.length > 0)
    {
        indices = new size_t[](tile.length);
    }

    const size_t *p = tile.begin();
    for (auto it = begin(); p < tile.end(); ++it, ++p)
        *it = *p;
}

SDG::AnimatedTile &SDG::AnimatedTile::operator= (const AnimatedTile &tile)
{
    delete indices;
    indices = new size_t[](tile.length);

    const size_t *p = tile.begin();
    for (auto it = begin(); p < tile.end(); ++it, ++p)
        *it = *p;

    length = tile.length;
    speed = tile.speed;
    index = tile.index;

    return *this;
}

SDG::AnimatedTile::AnimatedTile(AnimatedTile &&tile) noexcept : 
    indices(tile.indices), length(tile.length), speed(tile.speed), index(tile.index)
{
    tile.indices = nullptr;
    tile.length = 0;
}

SDG::AnimatedTile &SDG::AnimatedTile::operator= (AnimatedTile &&tile) noexcept
{
    if (this != &tile)
    {
        indices = tile.indices;
        length = tile.length;
        speed = tile.speed;
        index = tile.index;

        tile.indices = nullptr;
        tile.length = 0;
    }

    return *this;
}

size_t &SDG::AnimatedTile::At(size_t index)
{
    if (index >= length)
        throw OutOfRangeException(index, "Outside of AnimatedTile index range");
    return indices[index];
}

const size_t &SDG::AnimatedTile::At(size_t index) const
{
    if (index >= length)
        throw OutOfRangeException(index, "Outside of AnimatedTile index range");
    return indices[index];
}
