#include "XmlAttribute.h"
#include <SDG/Exceptions/NullReferenceException.h>
#include <SDG/Exceptions/XmlFormattingException.h>
#include <tinyxml2.h>

namespace SDG::Xml
{
    XmlAttribute::XmlAttribute(const tinyxml2::XMLAttribute *attr) : attr(attr) { }

    StringView XmlAttribute::Name() const
    {
        return attr ? attr->Name() : throw NullReferenceException();
    }

    StringView XmlAttribute::Value() const
    {
        return attr ? attr->Value() : throw NullReferenceException();
    }

    XmlAttribute XmlAttribute::Next() const
    {
        return attr ? attr->Next() : throw NullReferenceException();
    }

    bool XmlAttribute::Query(bool &b) const
    {
        if (!attr)
            throw NullReferenceException();
        if (attr->QueryBoolValue(&b) != tinyxml2::XML_SUCCESS)
        {
            throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query a bool value",
                attr->Name(), attr->Value(), attr->GetLineNum()));
        }

        return true;
    }

    bool XmlAttribute::Query(int &i) const
    {
        if (!attr)
            throw NullReferenceException();
        if (attr->QueryIntValue(&i) != tinyxml2::XML_SUCCESS)
        {
            throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query an int value",
                attr->Name(), attr->Value(), attr->GetLineNum()));
        }

        return true;
    }

    bool XmlAttribute::Query(int64_t &i) const
    {
        if (!attr)
            throw NullReferenceException();
        if (attr->QueryInt64Value(&i) != tinyxml2::XML_SUCCESS)
        {
            throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query an int64_t value",
                attr->Name(), attr->Value(), attr->GetLineNum()));
        }

        return true;
    }

    bool XmlAttribute::Query(unsigned &u) const
    {
        if (!attr)
            throw NullReferenceException();
        if (attr->QueryUnsignedValue(&u) != tinyxml2::XML_SUCCESS)
        {
            throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query an unsigned int value",
                attr->Name(), attr->Value(), attr->GetLineNum()));
        }

        return true;
    }

    bool XmlAttribute::Query(uint64_t &u) const
    {
        if (!attr)
            throw NullReferenceException();
        if (attr->QueryUnsigned64Value(&u) != tinyxml2::XML_SUCCESS)
        {
            throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query a uint64_t value",
                attr->Name(), attr->Value(), attr->GetLineNum()));
        }

        return true;
    }

    bool XmlAttribute::Query(float &f) const
    {
        if (!attr)
            throw NullReferenceException();
        if (attr->QueryFloatValue(&f) != tinyxml2::XML_SUCCESS)
        {
            throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query a float value",
                attr->Name(), attr->Value(), attr->GetLineNum()));
        }

        return true;
    }

    bool XmlAttribute::Query(double &d) const
    {
        if (!attr)
            throw NullReferenceException();
        if (attr->QueryDoubleValue(&d) != tinyxml2::XML_SUCCESS)
        {
            throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query a double value int",
                attr->Name(), attr->Value(), attr->GetLineNum()));
        }

        return true;
    }

    bool XmlAttribute::BoolValue() const
    {
        bool res;
        Query(res);
        return res;
    }

    int XmlAttribute::IntValue() const
    {
        int res;
        Query(res);
        return res;
    }

    int64_t XmlAttribute::Int64Value() const
    {
        int64_t res;
        Query(res);
        return res;
    }

    unsigned XmlAttribute::UintValue() const
    {
        unsigned res;
        Query(res);
        return res;
    }

    uint64_t XmlAttribute::Uint64Value() const
    {
        uint64_t res;
        Query(res);
        return res;
    }

    float XmlAttribute::FloatValue() const
    {
        float res;
        Query(res);
        return res;
    }

    double XmlAttribute::DoubleValue() const
    {
        double res;
        Query(res);
        return res;
    }

    int XmlAttribute::LineNumber() const
    {
        return attr ? attr->GetLineNum() : -1;
    }

    XmlAttribute::operator bool() const
    {
        return static_cast<bool>(attr);
    }

    XmlAttribute &XmlAttribute::operator++()
    {
        return *this = Next();
    }

    XmlAttribute XmlAttribute::operator++(int)
    {
        XmlAttribute temp = *this;
        *this = Next();
        return temp;
    }
}
