#pragma once
#include "TmxObject.h"
#include "Object.h"
#include "Tileset.h"

namespace SDG::Tiled
{
    class Template : public TmxObject
    {
    public:
        Template() : TmxObject("template") { }

    private:
        Tileset tileset;
        Object object;
    };
}