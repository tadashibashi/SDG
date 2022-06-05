#include "XmlValidationException.h"

SDG::XmlValidationException::XmlValidationException(const Xml::XmlElement &parent, size_t targetIndex, Xml::NodeType targetType)
{
    switch (targetType)
    {
    case Xml::NodeType::Element:
        message = String::Format("XmlElement <{}>:{}: "
            "required child at index [{}] was out of bounds!", parent.Name(), parent.LineNumber(), targetIndex);
        break;
    case Xml::NodeType::Attribute:
        message = String::Format("XmlElement <{}>:{}: "
            "required attribute at index [{}] was out of bounds!", parent.Name(), parent.LineNumber(), targetIndex);
        break;
    default:
        message = String::Format("XmlElement <{}>:{}: "
            "required entity with index [{}] was out of bounds!", parent.Name(), parent.LineNumber(), targetIndex);
        break;
    }
}

SDG::XmlValidationException::XmlValidationException(const Xml::XmlElement &element, Xml::NodeRelation targetRelation)
{
    // Only have NodeRelation::Next for now, so no conditional logic has been set up for this yet.
    message = String::Format("XmlElement <{}>:{}: "
        "required next sibling element is missing!", element.Name(), element.LineNumber());
}

SDG::XmlValidationException::XmlValidationException(const Xml::XmlAttribute &attr, Xml::NodeRelation targetRelation)
{
    // Only have NodeRelation::Next for now, so no conditional logic has been set up for this yet.
    message = String::Format("XmlAttribute \"{}\":{}: "
        "required next sibling attribute is missing!", attr.Name(), attr.LineNumber());
}

SDG::XmlValidationException::XmlValidationException(
    const Xml::XmlElement &parent, const String &targetName, Xml::NodeType targetType)
{
    switch (targetType)
    {
    case Xml::NodeType::Element:
        message = String::Format("XmlElement <{}>:{}: "
            "required child <{}> was not found!", parent.Name(), parent.LineNumber(), targetName);
        break;
    case Xml::NodeType::Attribute:
        message = String::Format("XmlElement <{}>:{}: "
            "required attribute \"{}\" was not found!", parent.Name(), parent.LineNumber(), targetName);
        break;
    default:
        message = String::Format("XmlElement <{}>:{}: "
            "required entity with name \"{}\" was out of bounds!", parent.Name(), parent.LineNumber(), targetName);
        break;
    }
}
