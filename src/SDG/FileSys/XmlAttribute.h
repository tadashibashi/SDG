#pragma once
#include <SDG/Lib/StringView.h>

namespace tinyxml2
{
    class XMLAttribute;
}

namespace SDG::Xml
{
    class XmlAttribute
    {
    public:
        XmlAttribute(const tinyxml2::XMLAttribute *attr = nullptr);
        StringView Name() const;
        StringView Value() const;

        /// Gets the next Attribute in the same element
        XmlAttribute Next() const;

        bool Query(bool &b) const;
        bool Query(int &i) const;
        bool Query(int64_t &i) const;
        bool Query(unsigned &u) const;
        bool Query(uint64_t &u) const;
        bool Query(float &f) const;
        bool Query(double &d) const;

        bool      BoolValue() const;
        int       IntValue() const;
        int64_t   Int64Value() const;
        unsigned  UintValue() const;
        uint64_t  Uint64Value() const;
        float     FloatValue() const;
        double    DoubleValue() const;

        /// Gets the line number this attribute is on, if the associated 
        /// document was loaded from a file. 
        /// Returns -1 if inner attribute is null.
        int LineNumber() const;
        explicit operator bool() const;
        XmlAttribute &operator ++();
        XmlAttribute operator ++(int);
    private:
        const tinyxml2::XMLAttribute *attr;
    };
}