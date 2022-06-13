#pragma once
#include <Engine/Filesys/Xml.h>
#include "Map.h"

namespace SDG::Tiled
{
    class TmxFile : public XmlLoadable
    {
    public:

    private:
        bool LoadImpl(const Xml::XmlDocument &doc);
        Map map;
    };
}