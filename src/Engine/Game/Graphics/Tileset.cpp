#include "Tileset.h"

namespace SDG
{
    Tileset::Tileset() : texture(), tileWidth(), tileHeight() { }

    Tileset::Tileset(const Shared<Texture> &texture, size_t tileWidth, size_t tileHeight, size_t idOffset) :
        texture(texture), tileWidth(tileWidth), tileHeight(tileHeight), idOffset(idOffset)
    {

    }
    
    
}