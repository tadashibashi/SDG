#pragma once
#include "XmlDocument.h"
#include <Engine/Filesys/Path.h>
#include <Engine/Lib/String.h>

namespace SDG
{
    class XmlLoadable
    {
    public:
        XmlLoadable(const String &typeName) : name(typeName) { }
        XmlLoadable() = delete;
        virtual ~XmlLoadable() = default;

        bool Load(const Path &path);
        bool Load(const Xml::XmlDocument &doc);
        const String &TypeName() const { return name; }
    private:
        virtual bool LoadImpl(const Xml::XmlDocument &doc) = 0;
        String name;
    };
}
