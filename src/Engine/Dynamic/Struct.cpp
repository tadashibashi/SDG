#include "Struct.h"
#include "Object.h"
#include <Engine/Lib/String.h>
#include <utility>

namespace SDG::Dynamic
{
    struct Struct::Impl {
        Impl() : members(), count(1) { }
        std::map<String, Object> members;
        size_t count;
    };

    const std::map<String, Object> &Struct::Members() const { return impl->members; }

    Struct::Struct() : impl(new Impl)
    {

    }

    Struct::~Struct()
    {
        --impl->count;
        if (impl->count == 0)
            delete impl;
    }

    Struct::Struct(std::map<String, class Object> map) : impl(new Impl)
    {
        impl->members = std::move(map);
    }

    Struct::Struct(const Struct &s) : impl(s.impl)
    {
        ++impl->count;
    }

    Struct &Struct::operator = (const Struct &s)
    {
        if (impl != s.impl)
        {
            --impl->count;
            if (impl->count == 0)
                delete impl;
            impl = s.impl;
            ++impl->count;
        }

        return *this;
    }

    const Object &Struct::operator[] (const String &key) const
    {
        return impl->members.at(key);
    }

    Object &Struct::operator[] (const String &key)
    {
        return impl->members[key];
    }

    bool Struct::Contains(const String &key) const
    {
        return impl->members.find(key) != impl->members.end();
    }

}


std::ostream &operator << (std::ostream &os, const SDG::Dynamic::Struct &obj)
{
    os << "Struct {";
    for (const auto &[k, v] : obj.Members())
        os << " \"" << k << "\": " << v << '\n';

    return os << "}";
}
