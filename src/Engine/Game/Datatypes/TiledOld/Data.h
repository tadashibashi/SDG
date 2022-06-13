#pragma once
#include "TmxObject.h"
#include "Chunk.h"
#include "Tile.h"

#include <Engine/Lib/Buffer.h>

#include <vector>

namespace SDG::Tiled
{
    class Data : public TmxObject
    {
    public:
        Data() : TmxObject("data") { }
        String encoding, compression;
        std::vector<size_t> data;
        std::vector<Tile> tiles;
        std::vector<Chunk> chunks;
    private:
        void LoadImpl(const Xml::XmlElement &el) override;


    };
}