#include "Layer.h"

namespace SDG::Tiled
{
    void Layer::LoadImpl(const Xml::XmlElement &el)
    {
        uint64_t id;
        uint64_t x = 0, y = 0, width, height;
        String name;
        float opacity;
        bool visible;
        Color tintcolor;
        float offsetx, offsety;
        float parallaxx, parallaxy;
        Properties properties;

        el.Attribute("id", Xml::Required).Query(id);
    }
}