#include "Property.h"
#include "Class.h"
#include <SDG/Lib/Memory.h>
#include <SDG/Exceptions/InvalidArgumentException.h>

namespace SDG::Tiled
{
    struct Property::Impl
    {
        Impl() : name(), type(), value() { }

        SDG::String name;
        enum Type type;
        std::variant< String, int, float, bool, Color, size_t, Class > value;
    };

    Property::Property() : impl(new Impl)
    {
        impl->type = Type::Null;
    }

    Property::Property(const String &name, enum Type type, const std::any &value) : impl(new Impl)
    { 
        impl->name = name;
        impl->type = type;

        switch (type)
        {
        case Type::String:
            impl->value = std::any_cast<String>(value);
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
            impl->value = std::any_cast<Color>(value);
            break;
        case Type::File:
            impl->value = std::any_cast<String>(value);
            break;
        case Type::Object:
            impl->value = std::any_cast<size_t>(value);
            break;
        case Type::Class:
            impl->value = std::any_cast<Class>(value);
            break;
        default:
            throw InvalidArgumentException("Property::Property(enum Type type, const std::any &value)", "type");
        }
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