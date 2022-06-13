#include "Chunk.h"

void SDG::Tiled::Chunk::LoadImpl(const Xml::XmlElement &el)
{
    std::vector<Tile> tiles;
    uint64_t x, y, width, height;

    el.Attribute("x", Xml::Required).Query(x);
    el.Attribute("y", Xml::Required).Query(y);
    el.Attribute("width", Xml::Required).Query(width);
    el.Attribute("height", Xml::Required).Query(height);

    /// Get any tiles inside
    if (!el.NoChildren())
    {
        for (auto e = el.FirstChild(); e; ++e)
        {
            if (e.Name() == "tile")
                tiles.emplace_back().Load(e);
        }
    }

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->tiles.swap(tiles);
}
