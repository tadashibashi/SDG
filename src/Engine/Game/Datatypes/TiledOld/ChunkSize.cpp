#include "ChunkSize.h"

void SDG::Tiled::ChunkSize::LoadImpl(const Xml::XmlElement &el)
{
    unsigned width = 16, height = 16;
    el.Attribute("width", Xml::Required).Query(width);
    el.Attribute("height", Xml::Required).Query(height);

    this->width = width;
    this->height = height;
}
