#include "Tilemap.h"
#include "Texture.h"
#include "Tile.h"

namespace SDG
{
    struct Tilemap::Impl
    {
        Impl() : texture(), width(), tiles(), instances(1) { }
        Texture texture;
        size_t width;
        std::vector<Tile> tiles;
        size_t instances;
    };

    Tilemap::Tilemap() : impl(new Impl)
    { }

    Tilemap::Tilemap(const Tilemap &tilemap) : impl(tilemap.impl)
    {
        ++impl->instances;
    }

    Tilemap &Tilemap::operator= (const Tilemap &tilemap)
    {
        if (tilemap.impl != impl)
        {
            Close();
            impl = tilemap.impl;
            ++impl->instances;
        }

        return *this;
    }

    Tilemap::Tilemap(Tilemap &&tiles) noexcept : impl(tiles.impl)
    {
        tiles.impl = nullptr;
    }

    Tilemap &Tilemap::operator= (Tilemap &&tilemap) noexcept
    {
        if (impl != tilemap.impl)
        {
            Close();
            impl = tilemap.impl;
            tilemap.impl = nullptr;
        }

        return *this;
    }

    Tilemap::~Tilemap()
    {
        Close();
    }

    Tilemap &Tilemap::Set(const std::vector<Tile> &tiles, const Texture &texture, size_t tilesWide)
    {
        impl->texture = texture;
        impl->tiles = tiles;
        impl->width = tilesWide;
        return *this;
    }

    Tilemap &Tilemap::SetTile(size_t tileX, size_t tileY, Tile tile)
    {
        if (tileX >= impl->width || tileY * impl->width >= impl->tiles.size())
            throw OutOfRangeException(String::Format("Tilemap tile position: (x={}, y={}) out of range. "
                "Max dimensions: (x={}, y={})", tileX, tileY, impl->width-1, impl->tiles.size()/impl->width - 1));
        impl->tiles[tileX + tileY*impl->width] = tile;
        return *this;
    }

    bool Tilemap::operator==(const Tilemap &tilemap)
    {
        return tilemap.impl == impl;
    }



    void Tilemap::Close()
    {
        if (--impl->instances == 0)
            delete impl;
    }
}