#include "XmlElement.h"
#include <SDG/Exceptions/NullReferenceException.h>
#include <SDG/Exceptions/XmlValidationException.h>
#include <tinyxml2.h>

namespace SDG::Xml
{
    static XmlElement ValidateElement(const XmlElement &element, const XmlElement &parent,  size_t index, Validation check)
    {
        if (!element && check == Required)
            throw XmlValidationException(parent, index, Xml::NodeType::Element);
        return element;
    }

    static XmlElement ValidateElement(const XmlElement &element, const XmlElement &parent, const String &name, Validation check)
    {
        if (!element && check == Required)
            throw XmlValidationException(parent, name, Xml::NodeType::Element);
        return element;
    }

    static XmlAttribute ValidateAttribute(const XmlAttribute &attr, const XmlElement &parent, const String &name, Validation check)
    {
        if (!attr && check == Required)
            throw XmlValidationException(parent, name, Xml::NodeType::Attribute);
        return attr;
    }

    XmlElement::XmlElement(tinyxml2::XMLElement *element) : element(element) { }

    XmlElement XmlElement::Parent(Validation check) const
    {
        if (!element) throw NullReferenceException();
        tinyxml2::XMLNode *pNode = element->Parent();

        if (!pNode)
        {
            if (check == Required)
                throw XmlValidationException(*this, NodeRelation::Parent);
            else
                return nullptr;
        }

        XmlElement e = pNode->ToElement();
        if (!e)
        {
            if (check == Required)
                throw XmlValidationException(*this, NodeRelation::Parent);
            else
                return nullptr;
        }

        return e;
    }

    XmlElement XmlElement::NextSibling(const String &name, Validation check) const
    {
        if (!element) throw NullReferenceException();

        return ValidateElement(element->NextSiblingElement(name.Cstr()), *this, name, check);
    }

    XmlElement XmlElement::FirstChild(Validation check) const
    {
        if (!element) throw NullReferenceException();

        return ValidateElement(element->FirstChildElement(), *this, 0, check);
    }

    XmlElement XmlElement::FirstChild(const String &name, Validation check) const
    {
        if (!element) throw NullReferenceException();

        return ValidateElement(element->FirstChildElement(name.Cstr()), *this, name, check);
    }

    size_t XmlElement::ChildCount() const
    {
        size_t count = 0;
        for (XmlElement e = FirstChild(); e; ++e)
            ++count;
        return count;
    }

    bool XmlElement::NoChildren() const
    {
        return element ? element->NoChildren() : throw NullReferenceException();
    }

    XmlElement XmlElement::ChildAt(size_t index, Validation check) const
    {
        XmlElement e = FirstChild();
        for (size_t i = 0; i < index; ++i)
            if (!e++)
            {
                if (check == Required)
                    throw XmlValidationException(*this, index, Xml::NodeType::Element);
                else
                    return nullptr;
            }

        return e;
    }

    XmlAttribute XmlElement::Attribute(const String &name, Validation check) const
    {
        if (!element) throw NullReferenceException();

        return ValidateAttribute(XmlAttribute(element->FindAttribute(name.Cstr()), check == Required), 
            *this, name, check);
    }

    XmlAttribute XmlElement::AttributeAt(size_t index, Validation check) const
    {
        XmlAttribute a = FirstAttribute();
        for (size_t i = 0; i < index; ++i)
        {
            if (!a++)
            {
                if (check == Required)
                    throw XmlValidationException(*this, index, Xml::NodeType::Attribute);
                else 
                    return nullptr;
            }
        }

        return a;
    }

    size_t XmlElement::AttributeCount() const
    {
        size_t count = 0;
        for (XmlAttribute a = FirstAttribute(); a; ++a)
            ++count;
        return count;
    }

    bool XmlElement::NoAttributes() const
    {
        return element ? !element->FirstAttribute() : 
            throw NullReferenceException("XmlElement::NoAttributes: XmlElement was null");
    }

    XmlAttribute XmlElement::FirstAttribute(Validation check) const
    {
        if (!element) throw NullReferenceException("Attempted to access an attribute from a null XmlElement");

        return ValidateAttribute(XmlAttribute(element->FirstAttribute(), check == Required),
            *this, 0, check);
    }

    StringView XmlElement::Name() const
    {
        return element ? element->Name() : throw NullReferenceException();
    }

    int XmlElement::LineNumber() const
    {
        return element ? element->GetLineNum() : throw NullReferenceException();
    }

    XmlElement XmlElement::operator[](const String &name) const
    {
        return FirstChild(name, Required);
    }

    XmlElement &XmlElement::operator++()
    {
        return *this = NextSibling();
    }

    XmlElement XmlElement::operator++(int)
    {
        XmlElement temp = *this;
        *this = NextSibling();
        return temp;
    }

    XmlElement XmlElement::NextSibling(Validation check) const
    {
        if (!element) throw NullReferenceException();
        XmlElement e = element->NextSiblingElement();

        if (!e && check == Required)
            throw XmlValidationException(*this, NodeRelation::Next);
        
        return e;
    }
}

