#pragma once
#include <Engine/Filesys/Xml/XmlElement.h>

namespace SDG::Tiled
{
    class TmxObject
    {
    public:
        explicit TmxObject(const char *staticName) : name(staticName), wasLoaded() { }

        /// Loads the Tiled tmx object
        void Load(const Xml::XmlElement &element);

        /// Checks if this Tiled data structure was loaded.
        bool WasLoaded() const { return wasLoaded; }

        /// Will automatically resolve to a boolean to check if it was loaded.
        explicit operator bool() { return wasLoaded; }
    private:
        /// All subclasses just need to load this.
        virtual void LoadImpl(const Xml::XmlElement &element) = 0;
        const char *name;
        bool wasLoaded;
    };
}
