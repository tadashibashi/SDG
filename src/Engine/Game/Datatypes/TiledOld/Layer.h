#pragma once
#include "TmxObject.h"
#include "Properties.h"

#include <Engine/Graphics/Color.h>

#include <cstddef>

namespace SDG::Tiled
{
    class Layer : public TmxObject
    {
    public:
        Layer() : TmxObject("layer") { }
    private:
        void LoadImpl(const Xml::XmlElement &el);

        size_t id;
        String name;
        size_t x, y; // defaults to 0 and cannot be changed in Tiled
        size_t width, height;
        float opacity; // opacity of the layer as a value from 0 to 1. Default: 1
        bool visible;
        Color tintcolor; // multiplied with any tiles drawn by this layer
        float offsetx, offsety;
        float parallaxx, parallaxy; // parallax factors for this layer. Default: 1
        Properties properties;
    };
}
