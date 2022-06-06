#include "Class.h"

namespace SDG::Tiled
{
    Class::Class() : id(), name(), props()
    {
    }

    Class::Class(size_t id, const String &name, const Array<Property> &props) : id(id), name(name), props(props)
    {
        
    }

    void Class::Initialize(size_t id, const String &name, const Array<Property> &props)
    {
        this->id = id; this->name = name; this->props.Initialize(props);
    }

    const Property &Class::operator[](const String &str)
    {
        return props[str.Hash()];
    }

    const Property &Class::operator[](uint64_t keyhash)
    {
        return props[keyhash];
    }
}