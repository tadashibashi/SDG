#pragma once
#include <Engine/FileSys/Xml/XmlElement.h>

namespace SDG::Tiled
{
    class TmxObject
    {
    public:
        TmxObject(const char *staticName, const Xml::XmlElement &element) : name(staticName), wasLoaded()
        {
            Load(element);
        }

        explicit TmxObject(const char *staticName) : name(staticName), wasLoaded() { }
        void Load(const Xml::XmlElement &element);
        bool WasLoaded() const { return wasLoaded; }

        explicit operator bool() { return wasLoaded; }
    private:
        virtual void LoadImpl(const Xml::XmlElement &element) = 0;
        const char *name;
        bool wasLoaded;
    };
}
