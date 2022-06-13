#pragma once
#include "XmlElement.h"

#include <Engine/Filesys/Path.h>
#include <Engine/Lib/String.h>
#include <Engine/Debug/Trace.h>

namespace SDG::Xml
{
    class XmlDocument
    {
        struct Impl;
    public:
        XmlDocument();
        XmlDocument(const Path &filepath);
        ~XmlDocument();

        bool Open(const Path &filepath);
        [[nodiscard]] bool IsOpen() const;

        void Close();
        [[nodiscard]] size_t ChildCount() const;
        [[nodiscard]] bool NoChildren() const;

        [[nodiscard]] const XmlElement Root(Validation check = Optional) const;
        [[nodiscard]] XmlElement Root(Validation check = Optional);
        [[nodiscard]] const XmlElement FirstChild(Validation check = Optional) const;
        [[nodiscard]] XmlElement FirstChild(Validation check = Optional);
        [[nodiscard]] const XmlElement FirstChild(const String &name, Validation check = Optional) const;
        [[nodiscard]] XmlElement FirstChild(const String &name, Validation check = Optional);
        [[nodiscard]] const XmlElement ChildAt(size_t index, Validation check = Optional) const;
        [[nodiscard]] XmlElement ChildAt(size_t index, Validation check = Optional);

        [[nodiscard]] const XmlElement operator[] (size_t index) const;
        [[nodiscard]] XmlElement operator[] (size_t index);
        [[nodiscard]] const XmlElement operator[] (const String &name) const;
        [[nodiscard]] XmlElement operator[] (const String &name);
        [[nodiscard]] const Path &Filepath() const;

    private:
        Impl *impl;
    };
}