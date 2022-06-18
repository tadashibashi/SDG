#pragma once
#include <Engine/Graphics/Texture.h>
#include <Engine/Lib/Shared.h>

namespace SDG
{
    class Tileset
    {
    public:
        Tileset();
        Tileset(const Shared<Texture> &texture, size_t tileWidth, size_t tileHeight, size_t idOffset);
        
        auto TileCount() const { return (tileWidth == 0 || tileHeight == 0) ? 0 : (tileWidth / texture->Size().X()) * (tileHeight / texture->Size().Y()); }
        auto TileWidth() const { return tileWidth; }
        auto TileHeight() const { return tileHeight; }

        bool IsLoaded() const { return static_cast<bool>(texture.Get()) && TileCount() > 0; }
    private:
        Shared<Texture> texture;
        size_t tileWidth, tileHeight;
        size_t idOffset;
    };
}
