#pragma once
#include "Exception.h"
#include <SDG/FileSys/XmlElement.h>
#include <SDG/FileSys/XmlAttribute.h>
#include <cstddef>

namespace SDG
{
    namespace Xml {
        enum class NodeType
        {
            Unknown,
            Document,
            Element,
            Attribute
        };

        enum class NodeRelation
        {
            Next
        };
    }
    
    class XmlValidationException : public Exception
    {
    public:
        XmlValidationException(const Xml::XmlElement &parent, size_t targetIndex, Xml::NodeType targetType);
        XmlValidationException(const Xml::XmlElement &element, Xml::NodeRelation targetRelation);
        XmlValidationException(const Xml::XmlAttribute &attr, Xml::NodeRelation targetRelation);
        XmlValidationException(const Xml::XmlElement &parent, const String &targetName, Xml::NodeType targetType);
    };
}