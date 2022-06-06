#include "Tile.h"

namespace SDG::Tiled
{
    void Tile::LoadImpl(const Xml::XmlElement &el)
    {
        unsigned id   = el.Attribute("id", Xml::Required).UintValue();
        String   type = el.Attribute("type", Xml::Optional).Value();
        float    prob = el.Attribute("probability", Xml::Optional).FloatValue();

        this->id = id;
        this->objectType = type;
        this->probability = prob;
    }
}
