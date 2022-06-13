#include "Export.h"

void SDG::Tiled::Export::LoadImpl(const Xml::XmlElement &el)
{
    String target, format;
    el.Attribute("target", Xml::Validation::Required).Query(target);
    el.Attribute("format", Xml::Validation::Required).Query(format);
    
    this->target = target;
    this->format = format;
}
