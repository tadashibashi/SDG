#include "Property.h"
#include "Class.h"
#include <Engine/Lib/Memory.h>
#include <Engine/Exceptions/InvalidArgumentException.h>

namespace SDG::Tiled
{
    struct Property::Impl
    {
        Impl() : name(), type(Type::Null), value() { }

        SDG::String name;
        enum Type type;
        std::variant< String, int, float, bool, Color, uint64, Class > value;
    };

    Property::Property() : TmxObject("property"), impl(new Impl)
    { }

    

    void Property::LoadImpl(const Xml::XmlElement &el)
    {
        String name;
        String typeStr;
        String valStr;
        enum Type type;
        std::variant<String, int, float, bool, Color, uint64, Class> value;

        el.Attribute("name", Xml::Required).Query(name);
        el.Attribute("type", Xml::Optional).Query(typeStr);
        el.Attribute("value", Xml::Required).Query(valStr);

        if (typeStr == "string" || typeStr.Empty())
        {
            type = Type::String;
            value = valStr;
        }
        else if (typeStr == "int")
        {
            type = Type::Int;
            value = valStr.ToNumber<int>();
        }
        else if (typeStr == "float")
        {
            type = Type::Float;
            value = valStr.ToNumber<float>();
        }
        else if (typeStr == "bool")
        {
            type = Type::Bool;
            value = (valStr == "true");
        }
        else if (typeStr == "color")
        {
            type = Type::Color;
            value = Color::FromString(valStr, Color::Format::ARGB8888);
        }
        else if (typeStr == "file")
        {
            type = Type::File;
            value = valStr;
        }
        else if (typeStr == "object")
        {
            type = Type::Object;
            value = valStr.ToNumber<uint64>();
        }
        else if (typeStr == "class")
        {
            type = Type::Class;
            Class c;
        }

        impl->type = type;
        impl->name = std::move(name);
        impl->value = std::move(value);
    }

    Property &Property::Set(const String &name, enum Type type, const std::any &value)
    {
        impl->name = name;
        impl->type = type;

        switch (type)
        {
        case Type::String:
            impl->value = std::any_cast<SDG::String>(value);
            break;
        case Type::Int:
            impl->value = std::any_cast<int>(value);
            break;        
        case Type::Float:
            impl->value = std::any_cast<float>(value);
            break;        
        case Type::Bool:
            impl->value = std::any_cast<bool>(value);
            break;
        case Type::Color:
            impl->value = std::any_cast<SDG::Color>(value);
            break;
        case Type::File:
            impl->value = std::any_cast<SDG::String>(value);
            break;
        case Type::Object:
            impl->value = std::any_cast<uint64>(value);
            break;
        case Type::Class:
            impl->value = std::any_cast<Tiled::Class>(value);
            break;
        default:
            throw InvalidArgumentException("Property::Property(enum Type type, const std::any &value)", "type");
        }

        return *this;
    }

    Property::~Property() { delete impl;  }

    const SDG::String &Property::Name() const { return impl->name; }

    enum Property::Type Property::Type() const { return impl->type; }

    const String &Property::StringValue() const
    {
        return std::get<String>(impl->value);
    }

    int Property::IntValue() const
    {
        return std::get<int>(impl->value);
    }

    float Property::FloatValue() const
    {
        return std::get<float>(impl->value);
    }

    bool Property::BoolValue() const
    {
        return std::get<bool>(impl->value);
    }

    const Color &Property::ColorValue() const
    {
        return std::get<Color>(impl->value);
    }

    const String &Property::FileValue() const
    {
        return std::get<String>(impl->value);
    }

    size_t Property::ObjectValue() const
    {
        return std::get<size_t>(impl->value);
    }

    const Class &Property::ClassValue() const
    {
        return std::get<Class>(impl->value);
    }

    Property::operator bool() const
    {
        return impl->type != Type::Null;
    }
   
}