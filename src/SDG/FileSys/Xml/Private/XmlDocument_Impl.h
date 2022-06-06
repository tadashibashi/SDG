#pragma once
#include "../XmlDocument.h"
#include <tinyxml2.h>
#include "../XmlElement.h"

namespace SDG::Xml
{
    struct XmlDocument::Impl
    {
        Impl() : doc(), isOpen(), root(), filepath() { }
        tinyxml2::XMLDocument doc;
        XmlElement root;
        Path filepath;
        bool isOpen;
    };
}