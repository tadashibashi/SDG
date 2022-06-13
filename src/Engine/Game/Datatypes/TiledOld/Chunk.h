#pragma once
#include "TmxObject.h"
#include "Tile.h"

#include <vector>

namespace SDG::Tiled
{
    class Chunk : public TmxObject
    {
    public:
        Chunk() : TmxObject("chunk"), x(), y(), width(), height(), tiles() { }
    private:
        void LoadImpl(const Xml::XmlElement &el);

        size_t x, y; // coordinate of the chunk in tiles
        size_t width, height; // size of the chunk in tiles
        std::vector<Tile> tiles;
    };
}