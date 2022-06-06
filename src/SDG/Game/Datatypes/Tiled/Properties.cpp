#include "Properties.h"

namespace SDG::Tiled
{
    Properties::Properties() : props()
    { }

    Properties::Properties(const Array<Property> &props) : props()
    {
        Initialize(props);
    }

    void Properties::Initialize(const Array<Property> &props)
    {
        this->props.clear();
        for (auto it = props.cbegin(), end = props.cend(); it != end; ++it)
        {
            this->props[it->Name().Hash()] = *it;
        }
    }

    const Property &Properties::At(const String &key) const
    {
        return props.at(key.Hash());
    }

    const Property &Properties::At(uint64_t keyhash) const
    {
        return props.at(keyhash);
    }

    const Property &Properties::operator[](const String &key)
    {
        return props[key.Hash()];
    }

    const Property &Properties::operator[](uint64_t keyhash)
    {
        return props[keyhash];
    }

    bool Properties::Empty() const
    {
        return props.empty();
    }

    size_t Properties::Size() const
    {
        return props.size();
    }
    
    Properties::ConstIterator Properties::begin()
    {
        return props.begin();
    }

    Properties::ConstIterator Properties::end()
    {
        return props.end();
    }

    Properties::ConstIterator Properties::cbegin() const
    {
        return props.cbegin();
    }

    Properties::ConstIterator Properties::cend() const
    {
        return props.cend();
    }
}

