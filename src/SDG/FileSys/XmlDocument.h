#pragma once
#include "XmlElement.h"
#include "Path.h"
#include <SDG/Lib/String.h>
#include <SDG/Debug/Trace.h>

#define SDG_Check(statement) try {\
    (statement);\
} catch(const std::exception &e) {\
    SDG_Core_Err("{}: {}", SDG_TRACE(), #statement);\
    throw e;\
}\

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
        bool IsOpen() const;

        void Close();
        size_t ChildCount() const;
        bool NoChildren() const;

        XmlElement Root() const;
        XmlElement FirstChild() const;
        XmlElement FirstChild(const String &name);
        XmlElement ChildAt(size_t index) const;

        XmlElement operator[] (size_t index) const;
        const Path &Filepath() const;

    private:
        Impl *impl;
    };
}