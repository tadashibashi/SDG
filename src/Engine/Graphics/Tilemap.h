#pragma once
#include "Tile.h"

#include <vector>

namespace SDG
{
    class Tilemap
    {
        struct Impl;
    public:
        Tilemap();
        Tilemap(const Tilemap &tilemap);
        Tilemap &operator= (const Tilemap &tilemap);
        Tilemap(Tilemap &&tiles) noexcept;
        Tilemap &operator= (Tilemap &&tilemap) noexcept;
        ~Tilemap();

        void CopyTo(Tilemap &tilemap);

        Tilemap &Set(const std::vector<Tile> &tiles, const class Texture &texture, size_t tilesWide, size_t tileWidth, size_t tileHeight);
        Tilemap &SetTile(size_t tileX, size_t tileY, Tile tile);

        /// Checks if the same inner Tilemap instance (copy constructed/assigned from, moved to, etc.)
        [[nodiscard]] bool operator== (const Tilemap &tilemap);
        void Close();
    private:
        Impl *impl;
    };
}