#pragma once
#include <initializer_list>

namespace SDG
{
    struct Tile
    {
        size_t index;
    };

    struct AnimatedTile
    {
        AnimatedTile() : indices(nullptr), length(0), speed(1.f), index(0) { }
        AnimatedTile(const std::initializer_list<size_t> &reel, float speed);
        AnimatedTile(const AnimatedTile &tile);
        AnimatedTile &operator= (const AnimatedTile &tile);

        AnimatedTile(AnimatedTile &&tile) noexcept;
        AnimatedTile &operator= (AnimatedTile &&tile) noexcept;
        size_t &At(size_t index);
        const size_t &At(size_t index) const;

        size_t &operator[](size_t index) { return indices[index]; }
        const size_t &operator[](size_t index) const { return indices[index]; }
        size_t *begin() { return indices; }
        const size_t *begin() const { return indices; }
        size_t *end() { return indices + length; }
        const size_t *end() const { return indices + length; }
        
        size_t Length() const { return length; }
        float Index() const { return index; }
        float Speed() const { return speed; }

        AnimatedTile &Index(float index) { this->index = index; return *this; }
        AnimatedTile &Speed(float speed) { this->speed = speed; return *this; }

    private:
        size_t *indices;
        size_t length;
        float speed;
        float index;
    };
}