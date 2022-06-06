#pragma once
#include "TmxObject.h"
#include <SDG/Lib/String.h>
#include <cstddef>

namespace SDG::Tiled
{
    class Tile : public TmxObject
    {
    public:
        Tile() : TmxObject("Tile") { }

        size_t ID() const { return id; }
        const String &ObjectType() const { return objectType; }
        float Probability() const { return probability; }

    private:
        void LoadImpl(const Xml::XmlElement &el) override;
        /// The local tile ID within its tileset.
        size_t id;

        /// The type of the tile. Refers to an object type and is used by tile objects
        /// (optional) (since 1.0)
        String objectType;

        /// A percentage indicating the probability that this tile is chosen
        /// when it competes with others while editing with the terrain tool. 
        /// (defaults to 0)
        float probability;
    };
}