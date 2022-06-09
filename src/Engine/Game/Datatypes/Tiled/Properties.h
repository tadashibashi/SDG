#pragma once
#include "Property.h"

#include <Engine/Lib/Array.h>

#include <map>
#include <cstdint>

namespace SDG::Tiled
{
    class Properties
    {
    public:
        /// Creates a blank property container. Should be initialized later.
        Properties();

        /// Initializes property container with passed properties.
        explicit Properties(const Array<Property> &props);

        void Initialize(const Array<Property> &props);
        
        /// Safely retrieve a property from the container.
        /// Throws an exception if property with key does not exist.
        const Property &At(const String &key) const;        
        
        /// Safely retrieve a property from the container.
        /// Throws an exception if property with key does not exist.
        /// You may cache the key hash of a String by calling
        /// its Hash() member parameter.
        const Property &At(uint64_t keyhash) const;

        /// Access a property from the container. It will return a null
        /// property if property with the key does not exist.
        const Property &operator[] (const String &key);

        /// Access a property from the container. It will return a null
        /// property if property with the key does not exist.
        /// You may cache the key hash of a String by calling
        /// its Hash() member parameter.
        const Property &operator[] (uint64_t keyhash);

        bool Empty() const;
        size_t Size() const;

        typedef std::map<uint64_t, Property>::const_iterator ConstIterator;
        
        ConstIterator begin();
        ConstIterator end();
        ConstIterator cbegin() const;
        ConstIterator cend() const;

    private:
        std::map<uint64_t, Property> props;
    };
}
