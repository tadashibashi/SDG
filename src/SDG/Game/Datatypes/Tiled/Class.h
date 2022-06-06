#pragma once
#include "Property.h"
#include <SDG/Lib/Array.h>
#include <SDG/Lib/String.h>
#include <map>
#include <cstdint>

namespace SDG::Tiled
{
    struct Class
    {
    public:
        Class(size_t id, const String &name, const Array<Property> &props);

        size_t id;
        String name;
        const Property &operator [] (const String &str);
        size_t PropertyCount() const { return props.size(); }
    private:
        std::map<int64_t, Property> props;
    };
}