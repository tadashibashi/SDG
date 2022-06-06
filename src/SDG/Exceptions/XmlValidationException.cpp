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

SDG::XmlValidationException::XmlValidationException(const Xml::XmlDocument &parent, size_t targetIndex, Xml::NodeType targetType)
{
    switch (targetType)
    {
    case Xml::NodeType::Element:
        message = String::Format("XmlDocument ({}): "
            "required child at index [{}] was out of bounds!", parent.Filepath().Filename(), targetIndex);
        break;
    case Xml::NodeType::Attribute:
        message = String::Format("XmlDocument ({}): "
            "required attribute at index [{}] was out of bounds!", parent.Filepath().Filename(), targetIndex);
        break;
    default:
        message = String::Format("XmlDocument ({}): "
            "required entity with index [{}] was out of bounds!", parent.Filepath().Filename(), targetIndex);
        break;
    }
}

SDG::XmlValidationException::XmlValidationException(const Xml::XmlElement &element, Xml::NodeRelation targetRelation)
{
    switch (targetRelation)
    {
    case Xml::NodeRelation::Parent:
        message = String::Format("XmlElement <{}>:{}: "
            "required parent element is missing, or is not an element type", 
            element.Name(), element.LineNumber());
        break;
    case Xml::NodeRelation::Next:
        message = String::Format("XmlElement <{}>:{}: "
            "required next sibling element is missing!", element.Name(), element.LineNumber());
        break;
    default:
        message = String::Format("XmlElement <{}>:{}: "
            "required element of an unknown relationship is missing, or is not an element type",
            element.Name(), element.LineNumber());
        break;
    }
}

SDG::XmlValidationException::XmlValidationException(const Xml::XmlAttribute &attr, Xml::NodeRelation targetRelation)
{
    switch (targetRelation)
    {
    case Xml::NodeRelation::Parent:
        message = String::Format("XmlAttribute \"{}\":{}: "
            "required parent element is missing, or is not an element type!", 
            attr.Name(), attr.LineNumber());
        break;
    case Xml::NodeRelation::Next:
        message = String::Format("XmlAttribute \"{}\":{}: "
            "required next sibling attribute is missing!", attr.Name(), attr.LineNumber());
        break;
    default:
        message = String::Format("XmlAttribute \"{}\":{}: "
            "Internal error: unknown NodeRelation type", attr.Name(), attr.LineNumber());
        break;
    }

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
            "Internal exception error, the NodeRelation is unknown.", parent.Name(), parent.LineNumber());
        break;
    }
}

SDG::XmlValidationException::XmlValidationException(const Xml::XmlDocument &parent, const String &targetName, Xml::NodeType targetType)
{
    switch (targetType)
    {
    case Xml::NodeType::Element:
        message = String::Format("XmlDocument ({}): "
            "required child <{}> was not found!", parent.Filepath().Filename(), targetName);
        break;
    case Xml::NodeType::Attribute:
        message = String::Format("XmlDocument ({}): "
            "required attribute \"{}\" was not found!", parent.Filepath(), targetName);
        break;
    default:
        message = String::Format("XmlDocument ({}): "
            "required entity with name \"{}\" was out of bounds!", 
            parent.Filepath().Filename(), targetName);
        break;
    }
}
