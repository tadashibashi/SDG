#include "XmlDocument.h"
#include "Private/XmlDocument_Impl.h"
#include <SDG/FileSys/File.h>

namespace SDG::Xml
{
    XmlDocument::XmlDocument() : impl(new Impl)
    {

    }

    XmlDocument::XmlDocument(const Path &filepath) : impl(new Impl)
    {
        Open(filepath);
    }

    XmlDocument::~XmlDocument()
    {
        delete impl;
    }

    bool XmlDocument::Open(const Path &filepath)
    {
        Close();

        File file(filepath);
        if (!file.IsOpen())
        {
            SDG_Core_Err("Failed to open xml document ({}): {}", filepath.Filename(), file.GetError());
            return false;
        }
            
        
        if (impl->doc.Parse(file.Cstr(), file.Size()) != tinyxml2::XML_SUCCESS)
        {
            SDG_Core_Err("Xml data parsing error occurred ({}): {}", 
                filepath.Filename(), impl->doc.ErrorStr());
            return false;
        }

        impl->filepath = filepath;
        return impl->isOpen = true;
    }

    bool XmlDocument::IsOpen() const
    {
        return impl->isOpen;
    }

    void XmlDocument::Close()
    {
        if (impl->isOpen)
        {
            impl->doc.Clear();
            impl->isOpen = false;
            impl->filepath = Path();
        }
    }

    size_t XmlDocument::ChildCount() const
    {
        size_t count = 0;
        for (XmlElement e = impl->root; e; ++e)
            ++count;
        return count;
    }

    bool XmlDocument::NoChildren() const
    {
        return impl->doc.NoChildren();
    }

    XmlElement XmlDocument::Root() const
    {
        return FirstChild();
    }

    XmlElement XmlDocument::FirstChild() const
    {
        return impl->doc.RootElement();
    }

    XmlElement XmlDocument::FirstChild(const String &name)
    {
        return impl->doc.FirstChildElement(name.Cstr());
    }

    XmlElement XmlDocument::ChildAt(size_t index) const
    {
        XmlElement e = impl->doc.RootElement();
        for (size_t i = 0; i < index; ++i)
        {
            if (!e++) throw OutOfRangeException(index,
                "XmlDocument::ChildAt: child index out of bounds");
        }

        return e;
    }

    XmlElement XmlDocument::operator[](size_t index) const
    {
        XmlElement e = impl->doc.RootElement();
        for (size_t i = 0; i < index; ++i)
            if (!e++) return nullptr;

        return e;
    }

    const Path &XmlDocument::Filepath() const
    {
        return impl->filepath;
    }
}