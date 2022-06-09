#include "XmlAttribute.h"
#include <Engine/Debug/Log.h>
#include <Engine/Exceptions/NullReferenceException.h>
#include <Engine/Exceptions/XmlFormattingException.h>
#include <tinyxml2.h>


namespace SDG::Xml
{
    XmlAttribute::XmlAttribute(const tinyxml2::XMLAttribute *attr, bool required) : 
        attr(attr), required(required) { }

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

    bool XmlAttribute::Query(String &str) const
    {
        if (required)
        {
            if (!attr)
                throw NullReferenceException();
        }
        else
        {
            if (!attr) return false;
        }
        
        str = attr->Value();
        return true;
    }

    bool XmlAttribute::Query(StringView &str) const
    {
        if (required)
        {
            if (!attr)
                throw NullReferenceException();
        }
        else
        {
            if (!attr) return false;
        }

        str = attr->Value();
        return true;
    }

    bool XmlAttribute::Query(bool &b) const
    {
        if (required)
        {
            if (!attr)
                throw NullReferenceException();
            if (attr->QueryBoolValue(&b) != tinyxml2::XML_SUCCESS)
            {
                throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query as a boolean value",
                    attr->Name(), attr->Value(), attr->GetLineNum()));
            }
        }
        else
        {
            if (!attr) return false;
            if (attr->QueryBoolValue(&b) != tinyxml2::XML_SUCCESS)
            {
                SDG_Core_Warn("XmlAttribute: {}=\"{}\": line {}: failed to query as a boolean value");
                return false;
            }
        }

        return true;
    }

    bool XmlAttribute::Query(int &i) const
    {
        if (required)
        {
            if (!attr)
                throw NullReferenceException();
            if (attr->QueryIntValue(&i) != tinyxml2::XML_SUCCESS)
            {
                throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query as an int value",
                    attr->Name(), attr->Value(), attr->GetLineNum()));
            }
        }
        else
        {
            if (!attr) return false;
            if (attr->QueryIntValue(&i) != tinyxml2::XML_SUCCESS)
            {
                SDG_Core_Warn("XmlAttribute: {}=\"{}\": line {}: failed to query as an int value");
                return false;
            }
        }

        return true;
    }

    bool XmlAttribute::Query(int64_t &i) const
    {
        if (required)
        {
            if (!attr)
                throw NullReferenceException();
            if (attr->QueryInt64Value(&i) != tinyxml2::XML_SUCCESS)
            {
                throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query as an int64 value",
                    attr->Name(), attr->Value(), attr->GetLineNum()));
            }
        }
        else
        {
            if (!attr) return false;
            if (attr->QueryInt64Value(&i) != tinyxml2::XML_SUCCESS)
            {
                SDG_Core_Warn("XmlAttribute: {}=\"{}\": line {}: failed to query as an int64 value");
                return false;
            }
        }

        return true;
    }

    bool XmlAttribute::Query(unsigned &u) const
    {
        if (required)
        {
            if (!attr)
                throw NullReferenceException();
            if (attr->QueryUnsignedValue(&u) != tinyxml2::XML_SUCCESS)
            {
                throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query as an unsigned int value",
                    attr->Name(), attr->Value(), attr->GetLineNum()));
            }
        }
        else
        {
            if (!attr) return false;
            if (attr->QueryUnsignedValue(&u) != tinyxml2::XML_SUCCESS)
            {
                SDG_Core_Warn("XmlAttribute: {}=\"{}\": line {}: failed to query as an unsigned int value");
                return false;
            }
        }

        return true;
    }

    bool XmlAttribute::Query(uint64_t &u) const
    {
        if (required)
        {
            if (!attr)
                throw NullReferenceException();
            if (attr->QueryUnsigned64Value(&u) != tinyxml2::XML_SUCCESS)
            {
                throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query as a uint64 value",
                    attr->Name(), attr->Value(), attr->GetLineNum()));
            }
        }
        else
        {
            if (!attr) return false;
            if (attr->QueryUnsigned64Value(&u) != tinyxml2::XML_SUCCESS)
            {
                SDG_Core_Warn("XmlAttribute: {}=\"{}\": line {}: failed to query as a uint64 value");
                return false;
            }
        }

        return true;
    }

    bool XmlAttribute::Query(float &f) const
    {
        if (required)
        {
            if (!attr)
                throw NullReferenceException();
            if (attr->QueryFloatValue(&f) != tinyxml2::XML_SUCCESS)
            {
                throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query as a float value",
                    attr->Name(), attr->Value(), attr->GetLineNum()));
            }
        }
        else
        {
            if (!attr) return false;
            if (attr->QueryFloatValue(&f) != tinyxml2::XML_SUCCESS)
            {
                SDG_Core_Warn("XmlAttribute: {}=\"{}\": line {}: failed to query as a float value");
                return false;
            }
        }

        return true;
    }

    bool XmlAttribute::Query(double &d) const
    {
        if (required)
        {
            if (!attr)
                throw NullReferenceException();
            if (attr->QueryDoubleValue(&d) != tinyxml2::XML_SUCCESS)
            {
                throw XmlFormattingException(String::Format("XmlAttribute: {}=\"{}\": line {}: failed to query as a double value",
                    attr->Name(), attr->Value(), attr->GetLineNum()));
            }
        }
        else
        {
            if (!attr) return false;
            if (attr->QueryDoubleValue(&d) != tinyxml2::XML_SUCCESS)
            {
                SDG_Core_Warn("XmlAttribute: {}=\"{}\": line {}: failed to query as a double value");
                return false;
            }
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
