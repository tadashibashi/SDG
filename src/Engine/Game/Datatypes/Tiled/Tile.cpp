#include "Tile.h"

namespace SDG::Tiled
{
    void Tile::LoadImpl(const Xml::XmlElement &el)
    {
        unsigned id = 0;
        float probability = 0;
        StringView type;
        
        el.Attribute("id", Xml::Required).Query(id);
        
        if (auto attr = el.Attribute("type", Xml::Optional))
            type = attr.Value();
        
        if (auto attr = el.Attribute("probability", Xml::Optional))
            attr.Query(probability);

        this->id = id;
        this->type = type;
        this->probability = probability;
    }
}
