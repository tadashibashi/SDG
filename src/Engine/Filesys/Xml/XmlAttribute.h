#pragma once
#include <Engine/Lib/StringView.h>

namespace tinyxml2
{
    class XMLAttribute;
}

namespace SDG::Xml
{
    class XmlAttribute
    {
    public:
        XmlAttribute(const tinyxml2::XMLAttribute *attr = nullptr, bool required = false);
        [[nodiscard]] StringView Name() const;
        [[nodiscard]] StringView Value() const;

        /// Gets the next Attribute in the same element
        [[nodiscard]] XmlAttribute Next() const;

        bool Query(bool &b) const;
        bool Query(int &i) const;
        bool Query(int64_t &i) const;
        bool Query(unsigned &u) const;
        bool Query(uint64_t &u) const;
        bool Query(float &f) const;
        bool Query(double &d) const;
        bool Query(String &s) const;
        /// Please be aware, the string view will become invalidated once the 
        /// XmlDocument object goes out of scope, or  is cleared, altered, etc.
        bool Query(StringView &s) const;

        [[nodiscard]] bool      BoolValue() const;
        [[nodiscard]] int       IntValue() const;
        [[nodiscard]] int64_t   Int64Value() const;
        [[nodiscard]] unsigned  UintValue() const;
        [[nodiscard]] uint64_t  Uint64Value() const;
        [[nodiscard]] float     FloatValue() const;
        [[nodiscard]] double    DoubleValue() const;

        /// Gets the line number this attribute is on, if the associated 
        /// document was loaded from a file. 
        /// Returns -1 if inner attribute is null.
        [[nodiscard]] int LineNumber() const;
        [[nodiscard]] explicit operator bool() const;
        XmlAttribute &operator ++();
        XmlAttribute operator ++(int);
    private:
        const tinyxml2::XMLAttribute *attr;
        bool required;
    };
}