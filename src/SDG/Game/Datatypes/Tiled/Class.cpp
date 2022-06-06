#include "Class.h"

namespace SDG::Tiled
{
    Class::Class(size_t id, const String &name, const Array<Property> &props) : id(id), name(name), props()
    {
        for (auto it = props.cbegin(), end = props.cend(); it != end; ++it)
        {
            this->props[it->Name().Hash()] = *it;
        }
    }

    const Property &Class::operator[](const String &str)
    {
        return props[str.Hash()];
    }
}