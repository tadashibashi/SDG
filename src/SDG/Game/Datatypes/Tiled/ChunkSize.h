#pragma once
#include "TmxObject.h"

namespace SDG::Tiled
{
    // The width and height of chunks used for infinite maps(default to 16).
    class ChunkSize : public TmxObject
    {
    public:
        ChunkSize() : TmxObject("chunksize"), width(), height() { }

        size_t Width() const { return width; }
        size_t Height() const { return height; }
    private:
        void LoadImpl(const Xml::XmlElement &el);
        size_t width, height;
    };
}
