#pragma once
#include "Exception.h"
#include <SDG/FileSys/Xml/XmlElement.h>
#include <SDG/FileSys/Xml/XmlAttribute.h>
#include <SDG/FileSys/Xml/XmlDocument.h>
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
            Next,
            Parent
        };
    }
    
    class XmlValidationException : public Exception
    {
    public:
        XmlValidationException(const Xml::XmlElement &parent, size_t targetIndex, Xml::NodeType targetType);
        XmlValidationException(const Xml::XmlDocument &parent, size_t targetIndex, Xml::NodeType targetType);
        XmlValidationException(const Xml::XmlElement &element, Xml::NodeRelation targetRelation);
        XmlValidationException(const Xml::XmlAttribute &attr, Xml::NodeRelation targetRelation);
        XmlValidationException(const Xml::XmlElement &parent, const String &targetName, Xml::NodeType targetType);
        XmlValidationException(const Xml::XmlDocument &parent, const String &targetName, Xml::NodeType targetType);
    };
}