#pragma once
#include "XmlElement.h"

#include <SDG/FileSys/Path.h>
#include <SDG/Lib/String.h>
#include <SDG/Debug/Trace.h>

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

        [[nodiscard]] XmlElement Root(Validation check = Optional) const;
        [[nodiscard]] XmlElement FirstChild(Validation check = Optional) const;
        [[nodiscard]] XmlElement FirstChild(const String &name, Validation check = Optional) const;
        [[nodiscard]] XmlElement ChildAt(size_t index, Validation check = Optional) const;

        [[nodiscard]] XmlElement operator[] (size_t index) const;
        [[nodiscard]] const Path &Filepath() const;

    private:
        Impl *impl;
    };
}