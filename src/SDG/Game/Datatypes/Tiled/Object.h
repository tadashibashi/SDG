#pragma once
#include "Properties.h"
#include <SDG/Lib/String.h>

namespace SDG::Tiled
{
    struct Object
    {
        size_t id;
        String name;
        String type;
        int x, y, width, height;
        Properties props;
    };
}