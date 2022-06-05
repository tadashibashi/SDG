#pragma once
#include <SDG/Lib/String.h>
#include "XmlAttribute.h"
#include "XmlValidation.h"

namespace tinyxml2
{
    class XMLElement;
}

namespace SDG::Xml
{
    class XmlElement
    {
    public:
        XmlElement(tinyxml2::XMLElement *element = nullptr);

        XmlElement NextSibling(Validation check = Optional) const;
        XmlElement NextSibling(const String &name, Validation check = Optional) const;
        XmlElement FirstChild(Validation check = Optional) const;
        /// Gets the first child element with a particular name or a null
        /// element if there is none.
        XmlElement FirstChild(const String &name, Validation check = Optional) const;
        size_t ChildCount() const;
        bool NoChildren() const;
        XmlElement ChildAt(size_t index, Validation check = Optional);

        XmlAttribute Attribute(const String &name, Validation check = Optional) const;
        XmlAttribute AttributeAt(size_t index, Validation check = Optional) const;
        size_t AttributeCount() const;
        bool NoAttributes() const;
        XmlAttribute FirstAttribute(Validation check = Optional) const;

        StringView Name() const;
        int LineNumber() const;

        /// Index the element's child elements
        [[nodiscard]] XmlElement operator [] (const String &name) const;
        

        XmlElement &operator ++();
        XmlElement operator ++(int);
        explicit operator bool() const { return static_cast<bool>(element); }
    private:
        tinyxml2::XMLElement *element;
    };

}