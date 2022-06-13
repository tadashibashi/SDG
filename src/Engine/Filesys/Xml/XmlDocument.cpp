#include "XmlDocument.h"
#include "Private/XmlDocument_Impl.h"

#include <Engine/Filesys/File.h>
#include <Engine/Exceptions.h>
#include <Engine/Debug.h>

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
            SDG_Core_Err("Xml data parsing error occurred ({}:{}): {}", 
                filepath.Filename(), impl->doc.ErrorLineNum(), impl->doc.ErrorStr());
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

    const XmlElement XmlDocument::Root(Validation check) const
    {
        XmlElement e = impl->doc.FirstChildElement();
        if (!e && check == Validation::Required)
            throw XmlValidationException(*this, 0, NodeType::Element);
        return e;
    }

    XmlElement XmlDocument::Root(Validation check)
    {
        XmlElement e = impl->doc.FirstChildElement();
        if (!e && check == Validation::Required)
            throw XmlValidationException(*this, 0, NodeType::Element);
        return e;
    }

    const XmlElement XmlDocument::FirstChild(Validation check) const
    {
        XmlElement e = impl->doc.FirstChildElement();
        if (!e && check == Validation::Required)
            throw XmlValidationException(*this, 0, NodeType::Element);
        return e;
    }

    XmlElement XmlDocument::FirstChild(Validation check)
    {
        XmlElement e = impl->doc.FirstChildElement();
        if (!e && check == Validation::Required)
            throw XmlValidationException(*this, 0, NodeType::Element);
        return e;
    }

    const XmlElement XmlDocument::FirstChild(const String &name, Validation check) const
    {
        XmlElement e = impl->doc.FirstChildElement(name.Cstr());

        if (!e && check == Validation::Required)
            throw XmlValidationException(*this, name, NodeType::Element);
        return e;
    }

    XmlElement XmlDocument::FirstChild(const String &name, Validation check)
    {
        XmlElement e = impl->doc.FirstChildElement(name.Cstr());

        if (!e && check == Validation::Required)
            throw XmlValidationException(*this, name, NodeType::Element);
        return e;
    }

    const XmlElement XmlDocument::ChildAt(size_t index, Validation check) const
    {
        XmlElement e = impl->doc.RootElement();
        for (size_t i = 0; i < index; ++i)
        {
            if (!e++)
            {
                if (check == Required)
                    throw XmlValidationException(*this, index, NodeType::Element);
                else
                    return nullptr;
            }  
        }

        return e;
    }

    XmlElement XmlDocument::ChildAt(size_t index, Validation check)
    {
        XmlElement e = impl->doc.RootElement();
        for (size_t i = 0; i < index; ++i)
        {
            if (!e++)
            {
                if (check == Required)
                    throw XmlValidationException(*this, index, NodeType::Element);
                else
                    return nullptr;
            }
        }

        return e;
    }

    const XmlElement XmlDocument::operator[](size_t index) const
    {
        return ChildAt(index, Validation::Required);
    }
    
    XmlElement XmlDocument::operator[](size_t index)
    {
        return ChildAt(index, Validation::Required);
    }

    const XmlElement XmlDocument::operator[](const String &name) const
    {
        return FirstChild(name, Validation::Required);
    }

    XmlElement XmlDocument::operator[](const String &name)
    {
        return FirstChild(name, Validation::Required);
    }

    const Path &XmlDocument::Filepath() const
    {
        return impl->filepath;
    }
}