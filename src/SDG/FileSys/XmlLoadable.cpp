//
// Created by Aaron Ishibashi on 4/15/22.
//
#include "XmlLoadable.h"
#include "File.h"

#include <SDG/Debug.hpp>
#include <SDG/Exceptions/XMLReaderException.h>
#include <SDG/Exceptions/XmlValidationException.h>
#include <SDG/Exceptions/XmlFormattingException.h>

using namespace SDG::Xml;

bool
SDG::XmlLoadable::Load(const SDG::Path &path)
{
    XmlDocument doc(path);
    if (!doc.IsOpen())
    {
        SDG_Core_Err("{} xml load failed.", name);
        return false;
    }

    return Load(doc);
}

bool
SDG::XmlLoadable::Load(const SDG::Xml::XmlDocument &doc)
{
    try {
        return LoadImpl(doc);
    }
    catch (const XmlValidationException &e)
    {
        SDG_Core_Err("Xml validation error while loading {}: {}", name, e.what());
        return false;
    }
    catch (const XmlFormattingException &e)
    {
        SDG_Core_Err("Xml formatting error while loading {}: {}", name, e.what());
    }
    catch (const SDG::Exception &e)
    {
        SDG_Core_Err("SDG engine error while loading {}: {}", name, e.what());
    }
    catch (const std::exception &e)
    {
        SDG_Core_Err("Standard library error while loading {}: {}", name, e.what());
        return false;
    }
    catch (...)
    {
        SDG_Core_Err("Unknown error while loading {}", name);
        return false;
    }
}
