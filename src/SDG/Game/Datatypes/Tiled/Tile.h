#pragma once
#include <SDG/Lib/String.h>

namespace SDG::Tiled
{
    struct Tile
    {
        /// The local tile ID within its tileset.
        int id;

        /// The type of the tile. Refers to an object type and is used by tile objects
        /// (optional) (since 1.0)
        String type;

        /// A percentage indicating the probability that this tile is chosen
        /// when it competes with others while editing with the terrain tool. 
        /// (defaults to 0)
        float probability;
    };
}