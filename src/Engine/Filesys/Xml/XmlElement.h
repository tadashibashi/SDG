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
        
        const XmlElement &operator=(const XmlElement &e) { element = e.element; return *this; }
        XmlElement &operator=(XmlElement &e) { element = e.element; return *this; }

        [[nodiscard]] const XmlElement Parent(Validation check = Optional) const;
        [[nodiscard]] XmlElement Parent(Validation check = Optional);

        [[nodiscard]] XmlElement NextSibling(Validation check = Optional);
        [[nodiscard]] const XmlElement NextSibling(Validation check = Optional) const;
        [[nodiscard]] XmlElement NextSibling(const String &name, Validation check = Optional);
        [[nodiscard]] const XmlElement NextSibling(const String &name, Validation check = Optional) const;
        [[nodiscard]] const XmlElement FirstChild(Validation check = Optional) const;
        [[nodiscard]] XmlElement FirstChild(Validation check = Optional);
        /// Gets the first child element with a particular name or a null
        /// element if there is none.
        [[nodiscard]] const XmlElement FirstChild(const String &name, Validation check = Optional) const;
        [[nodiscard]] XmlElement FirstChild(const String &name, Validation check = Optional);
        [[nodiscard]] size_t ChildCount() const;
        [[nodiscard]] bool NoChildren() const;
        [[nodiscard]] const XmlElement ChildAt(size_t index, Validation check = Optional) const;
        [[nodiscard]] XmlElement ChildAt(size_t index, Validation check = Optional);

        [[nodiscard]] const XmlAttribute Attribute(const String &name, Validation check = Optional) const;
        [[nodiscard]] XmlAttribute Attribute(const String &name, Validation check = Optional);
        [[nodiscard]] const XmlAttribute AttributeAt(size_t index, Validation check = Optional) const;
        [[nodiscard]] XmlAttribute AttributeAt(size_t index, Validation check = Optional);
        [[nodiscard]] size_t AttributeCount() const;
        [[nodiscard]] bool NoAttributes() const;
        [[nodiscard]] const XmlAttribute FirstAttribute(Validation check = Optional) const;
        [[nodiscard]] XmlAttribute FirstAttribute(Validation check = Optional);

        [[nodiscard]] String Text() const;
        XmlElement &Text(const String &text);

        [[nodiscard]] String Name() const;
        XmlElement &Name(const String &name);

        [[nodiscard]] int LineNumber() const;

        /// Index the element's child elements
        [[nodiscard]] const XmlElement operator [] (const String &name) const;
        [[nodiscard]] XmlElement operator [] (const String &name);
        
        XmlElement &operator ++();
        const XmlElement &operator ++() const;
        XmlElement operator ++(int);
        const XmlElement operator ++(int) const;
        [[nodiscard]] explicit operator bool() const { return static_cast<bool>(element); }
    private:
        mutable tinyxml2::XMLElement *element;
    };
}
