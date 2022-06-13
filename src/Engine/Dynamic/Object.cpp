#include "Object.h"
#include "Struct.h"
#include "Array.h"
#include <Engine/Exceptions.h>
#include <Engine/Debug/Log.h>
#include <Engine/Lib/String.h>

#include <ostream>
#include <variant>

namespace SDG::Dynamic
{
    struct Object::Impl
    {
        Impl() : value(), type() { }
        std::variant<double, String, Struct, Array> value;
        Type type;
    };

    Object::Object() : impl(new Impl) {}
    Object::Object(const Object &obj) : impl(new Impl) { Assign(obj); }
    Object::Object(const Struct &s) : impl(new Impl) { Assign(s); }
    Object::Object(const Array &arr) : impl(new Impl) { Assign(arr); }
    Object::Object(const String &str) : impl(new Impl) { Assign(str); }
    Object::Object(double d) : impl(new Impl) { Assign(d); }

    Object::~Object() { delete impl; }

    const double &Object::AsReal() const 
    { 
        return std::get<double>(impl->value);
    }

    double &Object::AsReal() 
    { 
        return std::get<double>(impl->value); 
    }

    const String &Object::AsString() const 
    { 
        return std::get<String>(impl->value); 
    }

    String &Object::AsString()
    {
        return std::get<String>(impl->value);
    }

    const Struct &Object::AsStruct() const 
    { 
        return std::get<Struct>(impl->value); 
    }

    Struct &Object::AsStruct() 
    { 
        return std::get<Struct>(impl->value); 
    }
    
    const Array &Object::AsArray() const 
    { 
        return std::get<Array>(impl->value); 
    }

    Array &Object::AsArray()
    { 
        return std::get<Array>(impl->value); 
    }

    Type Object::GetType() const { return impl->type; }
    bool Object::Is(Type type) const { return impl->type == type; }

    String GetTypeName(Type type)
    {
        switch (type)
        {
        case Type::Null: return "null";
        case Type::Real: return "real";
        case Type::String: return "string";
        case Type::Struct: return "struct";
        default: return "unknown";
        }
    }

    const Object null;




    Object &Object::operator[] (const String &key)
    {
        if (impl->type != Type::Struct)
            throw RuntimeException(SDG_FUNC + ": \"this\" must be a struct. Actual type: " + 
                GetTypeName(impl->type));
        return AsStruct()[key];
    }

    const Object &Object::operator[] (const String &key) const
    {
        switch (impl->type)
        {
        case Type::Array: return AsArray()[key.ToNumber<size_t>()];
        case Type::Struct: return AsStruct()[key];
        default:
            throw RuntimeException(SDG_FUNC + ": type " + GetTypeName(impl->type) + " cannot be indexed. "
                "Must be an Array or Struct");
        }
    }

    Object &Object::operator[] (size_t index)
    {
        switch (impl->type)
        {
        case Type::Array: return AsArray()[index];
        case Type::Struct: return AsStruct()[ToString(index)];
        default:
            throw RuntimeException(SDG_FUNC + ": type " + GetTypeName(impl->type) + " cannot be indexed. "
                "Must be an Array or Struct");
        }
    }

    const Object &Object::operator[] (size_t index) const
    {
        switch (impl->type)
        {
        case Type::Array: return AsArray()[index];
        case Type::Struct: return AsStruct()[ToString(index)];
        default:
            throw RuntimeException(SDG_FUNC + ": type " + GetTypeName(impl->type) + " cannot be indexed. "
                "Must be an Array of Struct");
        }
    }


    bool Object::operator==(const Object &other) const
    {
        if (impl->type != other.impl->type) return false;

        switch (impl->type)
        {
        case Type::Null: return true;
        case Type::Real: return operator==(other.AsReal());
        case Type::String: return operator==(other.AsString());
        case Type::Struct: return operator==(other.AsStruct());
        case Type::Array: return operator==(other.AsArray());
        default:
            throw RuntimeException(SDG_FUNC + ": unknown type");
        }
    }

    bool Object::operator==(const Struct &s) const
    {
        return AsStruct() == s;
    }

    bool Object::operator==(double d) const
    {
        return AsReal() == d;
    }

    bool Object::operator==(const String &str) const
    {
        return AsString() == str;
    }

    bool Object::operator==(const Array &arr) const
    {
        return AsArray() == arr;
    }

    void Object::Assign(const Object &other)
    {
        switch (other.impl->type)
        {
        case Type::Null:
            AssignNull();
            break;
        case Type::Real:
            Assign(other.AsReal());
            break;
        case Type::String:
            Assign(other.AsString());
            break;
        case Type::Struct:
            Assign(other.AsStruct());
            break;
        case Type::Array:
            Assign(other.AsArray());
            break;
        default:
            throw RuntimeException(SDG_FUNC + ": unknown type");
            break;
        }

        impl->type = other.impl->type;
    }

    void Object::Assign(const Struct &s)
    {    
        impl->value = s;
        impl->type = Type::Struct;
    }

    void Object::Assign(const Array &arr)
    {
        impl->value = arr;
        impl->type = Type::Array;
    }

    void Object::Assign(const String &str)
    {
        impl->value = str;
        impl->type = Type::String;
    }

    void Object::Assign(double d)
    {
        impl->value = d;
        impl->type = Type::Real;
    }

    void Object::AssignNull()
    {
        impl->type = Type::Null;
    }


    Object &Object::operator += (double n)
    {
        if (impl->type != Type::Real)
            throw RuntimeException(SDG_FUNC + ": Operation failed: Object is not a real number");
        AsReal() += n;
        return *this;
    }

    Object &Object::operator += (const String &str)
    {
        if (impl->type != Type::String)
            throw RuntimeException(SDG_FUNC + ": Operation failed: Object is not a string");
        
        AsString() += str;
        return *this;
    }

    Object &Object::operator -= (double n)
    {
        if (impl->type != Type::Real)
            throw RuntimeException(SDG_FUNC + ": Operation failed: Object is not a real number");
        AsReal() -= n;
        return *this;
    }

    Object &Object::operator *= (double n)
    {
        if (impl->type != Type::Real)
            throw RuntimeException(SDG_FUNC + ": Operation failed: Object is not a real number");
        AsReal() *= n;
        return *this;
    }

    Object &Object::operator /= (double n)
    {
        if (impl->type != Type::Real)
            throw RuntimeException(SDG_FUNC + ": Operation failed: Object is not a real number");
        if (n == 0)
            throw DivisionByZeroException();
        AsReal() /= n;
        return *this;
    }

    Object &Object::operator %= (double n)
    {
        if (impl->type != Type::Real)
            throw RuntimeException(SDG_FUNC + ": Operation failed: Object is not a real number");
        AsReal() = std::fmod(AsReal(), n);
        return *this;
    }

    void Object::NewImpl()
    {
        impl = new Impl;
    }
}

std::ostream &operator<<(std::ostream &os, const SDG::Dynamic::Object &obj)
{
    switch (obj.GetType())
    {
    case SDG::Dynamic::Type::Real: os << obj.AsReal();
        break;
    case SDG::Dynamic::Type::String: os << obj.AsString();
        break;
    case SDG::Dynamic::Type::Struct: os << "{struct} size: " << obj.AsStruct().Members().size(); //obj.AsStruct();
        break;
    case SDG::Dynamic::Type::Array: os << "[";
        for (const auto &t : obj.AsArray())
            os << t << " ";
        os << "]\n";
        break;
    case SDG::Dynamic::Type::Null: os << "null";
        break;
    }

    return os;
}