#include "Tilemap.h"
#include "Texture.h"
#include "Tile.h"

namespace SDG
{
    struct Tilemap::Impl
    {
        Impl() : texture(), width(), tiles(), count(1) { }
        Texture texture;
        size_t width;
        std::vector<Tile> tiles;
        size_t count;
    };

    Tilemap::Tilemap() : impl(new Impl)
    { }

    Tilemap::Tilemap(const Tilemap &tiles) : impl(tiles.impl)
    {
        ++impl->count;
    }

    Tilemap &Tilemap::operator= (const Tilemap &tiles)
    {
        if (tiles.impl != impl)
        {
            Close();
            impl = tiles.impl;
            ++impl->count;
        }

        return *this;
    }

    Tilemap::Tilemap(Tilemap &&tiles) noexcept : impl(tiles.impl)
    {
        tiles.impl = nullptr;
    }

    Tilemap &Tilemap::operator= (Tilemap &&tiles) noexcept
    {
        if (impl != tiles.impl)
        {
            Close();
            impl = tiles.impl;
            tiles.impl = nullptr;
        }

        return *this;
    }

    Tilemap::~Tilemap()
    {
        Close();
    }

    void Tilemap::Close()
    {
        if (--impl->count == 0)
            delete impl;
    }
}