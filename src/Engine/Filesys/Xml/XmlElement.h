#pragma once
#include "XmlAttribute.h"
#include "XmlValidation.h"
#include <Engine/Lib/String.h>

// forward declaration
namespace tinyxml2 { class XMLElement; }

namespace SDG::Xml
{
    class XmlElement
    {
    public:
        XmlElement(tinyxml2::XMLElement *element = nullptr);

        [[nodiscard]] XmlElement Parent(Validation check = Optional) const;
        [[nodiscard]] XmlElement NextSibling(Validation check = Optional) const;
        [[nodiscard]] XmlElement NextSibling(const String &name, Validation check = Optional) const;
        [[nodiscard]] XmlElement FirstChild(Validation check = Optional) const;
        /// Gets the first child element with a particular name or a null
        /// element if there is none.
        [[nodiscard]] XmlElement FirstChild(const String &name, Validation check = Optional) const;
        [[nodiscard]] size_t ChildCount() const;
        [[nodiscard]] bool NoChildren() const;
        [[nodiscard]] XmlElement ChildAt(size_t index, Validation check = Optional) const;

        [[nodiscard]] XmlAttribute Attribute(const String &name, Validation check = Optional) const;
        [[nodiscard]] XmlAttribute AttributeAt(size_t index, Validation check = Optional) const;
        [[nodiscard]] size_t AttributeCount() const;
        [[nodiscard]] bool NoAttributes() const;
        [[nodiscard]] XmlAttribute FirstAttribute(Validation check = Optional) const;

        [[nodiscard]] StringView Name() const;
        [[nodiscard]] int LineNumber() const;

        /// Index the element's child elements
        [[nodiscard]] XmlElement operator [] (const String &name) const;
        
        XmlElement &operator ++();
        XmlElement operator ++(int);
        [[nodiscard]] explicit operator bool() const { return static_cast<bool>(element); }
    private:
        tinyxml2::XMLElement *element;
    };
}
