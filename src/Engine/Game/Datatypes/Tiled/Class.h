#pragma once
#include "Properties.h"
#include <Engine/Lib/Array.h>
#include <Engine/Lib/String.h>
#include <map>
#include <cstdint>

namespace SDG::Tiled
{
    struct Class
    {
    public:
        /// Creates a default class object, that should be Initialized later.
        Class();
        /// Immediately sets the class members.
        Class(size_t id, const String &name, const Array<Property> &props);
        /// Call this if the default constructor was used to initialize/reset the members.
        void Initialize(size_t id, const String &name, const Array<Property> &props);

        size_t ID() const { return id; }
        const String &Name() const { return name; }

        const Property &operator [] (const String &key);
        const Property &operator [] (uint64_t keyhash);

        size_t PropertyCount() const { return props.Size(); }
    private:
        size_t id;
        String name;
        Properties props;
    };
}
