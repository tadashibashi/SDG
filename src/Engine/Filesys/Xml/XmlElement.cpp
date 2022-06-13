#include "XmlElement.h"
#include <Engine/Exceptions.h>
#include <tinyxml2.h>

namespace SDG::Xml
{
    static XmlElement ValidateElement(XmlElement element, const XmlElement &parent, size_t index, Validation check)
    {
        if (!element && check == Required)
            throw XmlValidationException(parent, index, Xml::NodeType::Element);
        return element;
    }

    static XmlElement ValidateElement(XmlElement element, const XmlElement &parent, const String &name, Validation check)
    {
        if (!element && check == Required)
            throw XmlValidationException(parent, name, Xml::NodeType::Element);
        return element;
    }

    static const XmlAttribute &ValidateAttribute(const XmlAttribute &attr, const XmlElement &parent, const String &name, Validation check)
    {
        if (!attr && check == Required)
            throw XmlValidationException(parent, name, Xml::NodeType::Attribute);
        return attr;
    }

    XmlElement::XmlElement(tinyxml2::XMLElement *element) : element(element) { }

    const XmlElement XmlElement::Parent(Validation check) const
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

    String XmlElement::Text() const 
    {
        if (!element) throw NullReferenceException();

        return element->GetText();
    }

    XmlElement &XmlElement::Text(const String &text)
    {
        if (!element) throw NullReferenceException();

        element->SetText(text.Cstr());
        return *this;
    }

    const XmlElement XmlElement::NextSibling(const String &name, Validation check) const
    {
        if (!element) throw NullReferenceException();

        return ValidateElement(element->NextSiblingElement(name.Cstr()), *this, name, check);
    }

    XmlElement XmlElement::NextSibling(const String &name, Validation check)
    {
        if (!element) throw NullReferenceException();

        return ValidateElement(element->NextSiblingElement(name.Cstr()), *this, name, check);
    }

    const XmlElement XmlElement::FirstChild(Validation check) const
    {
        if (!element) throw NullReferenceException();

        return ValidateElement(element->FirstChildElement(), *this, 0, check);
    }

    XmlElement XmlElement::FirstChild(Validation check)
    {
        if (!element) throw NullReferenceException();

        return ValidateElement(element->FirstChildElement(), *this, 0, check);
    }

    const XmlElement XmlElement::FirstChild(const String &name, Validation check) const
    {
        if (!element) throw NullReferenceException();

        return ValidateElement(element->FirstChildElement(name.Cstr()), *this, name, check);
    }

    XmlElement XmlElement::FirstChild(const String &name, Validation check)
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

    const XmlElement XmlElement::ChildAt(size_t index, Validation check) const
    {
        XmlElement e = FirstChild();
        for (size_t i = 0; i < index; ++i)
        {
            if (!e++)
            {
                if (check == Required)
                    throw XmlValidationException(*this, index, Xml::NodeType::Element);
                else
                    return nullptr;
            }
        }

        return e;
    }
     
    XmlElement XmlElement::ChildAt(size_t index, Validation check)
    {
        XmlElement e = FirstChild();
        for (size_t i = 0; i < index; ++i)
        {
            if (!e++)
            {
                if (check == Required)
                    throw XmlValidationException(*this, index, Xml::NodeType::Element);
                else
                    return nullptr;
            }
        }

        return e;
    }

    const XmlAttribute XmlElement::Attribute(const String &name, Validation check) const
    {
        if (!element) throw NullReferenceException();

        return ValidateAttribute(XmlAttribute(element->FindAttribute(name.Cstr()), check == Required), 
            *this, name, check);
    }

    XmlAttribute XmlElement::Attribute(const String &name, Validation check)
    {
        if (!element) throw NullReferenceException();

        return ValidateAttribute(XmlAttribute(element->FindAttribute(name.Cstr()), check == Required),
            *this, name, check);
    }

    const XmlAttribute XmlElement::AttributeAt(size_t index, Validation check) const
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

    XmlAttribute XmlElement::AttributeAt(size_t index, Validation check)
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

    const XmlAttribute XmlElement::FirstAttribute(Validation check) const
    {
        if (!element) throw NullReferenceException("Attempted to access an attribute from a null XmlElement");

        return ValidateAttribute(XmlAttribute(element->FirstAttribute(), check == Required),
            *this, 0, check);
    }

    XmlAttribute XmlElement::FirstAttribute(Validation check)
    {
        if (!element) throw NullReferenceException("Attempted to access an attribute from a null XmlElement");

        return ValidateAttribute(XmlAttribute(element->FirstAttribute(), check == Required),
            *this, 0, check);
    }

    String XmlElement::Name() const
    {
        return element ? element->Name() : throw NullReferenceException();
    }

    XmlElement &XmlElement::Name(const String &name)
    {
        if (!element) throw NullReferenceException("XmlElement's inner ptr was null");
        element->SetName(name.Cstr());

        return *this;
    }

    int XmlElement::LineNumber() const
    {
        return element ? element->GetLineNum() : throw NullReferenceException();
    }

    const XmlElement XmlElement::operator[](const String &name) const
    {
        return FirstChild(name, Required);
    }

    XmlElement XmlElement::operator[](const String &name)
    {
        return FirstChild(name, Required);
    }

    XmlElement &XmlElement::operator++()
    {
        if (!element) throw NullReferenceException();

        element = element->NextSiblingElement();
        
        return *this;
    }

    const XmlElement &XmlElement::operator++() const
    {
        if (!element) throw NullReferenceException();

        element = element->NextSiblingElement();

        return *this;
    }

    XmlElement XmlElement::operator++(int)
    {
        if (!element) throw NullReferenceException();
        XmlElement temp(element);

        element = element->NextSiblingElement();
        
        return temp;
    }

    const XmlElement XmlElement::operator++(int) const
    {
        if (!element) throw NullReferenceException();
        XmlElement temp(element);

        element = element->NextSiblingElement();

        return temp;
    }

    const XmlElement XmlElement::NextSibling(Validation check) const
    {
        if (!element) throw NullReferenceException();
        XmlElement e = element->NextSiblingElement();

        if (!e && check == Required)
            throw XmlValidationException(*this, NodeRelation::Next);
        
        return e;
    }

    XmlElement XmlElement::NextSibling(Validation check)
    {
        if (!element) throw NullReferenceException();
        XmlElement e = element->NextSiblingElement();

        if (!e && check == Required)
            throw XmlValidationException(*this, NodeRelation::Next);

        return e;
    }
}

