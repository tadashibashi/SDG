#pragma once
#include <SDG/FileSys/Xml/XmlElement.h>
#include <SDG/Lib/String.h>

namespace SDG::Tiled
{
    class TmxObject
    {
    public:
        TmxObject(const char *staticName, const Xml::XmlElement &element) : name(staticName) 
        {
            Load(element);
        }

        explicit TmxObject(const char *staticName) : name(staticName) { }
        void Load(const Xml::XmlElement &element);

    private:
        virtual void LoadImpl(const Xml::XmlElement &element) = 0;
        const char *name;
    };
}
