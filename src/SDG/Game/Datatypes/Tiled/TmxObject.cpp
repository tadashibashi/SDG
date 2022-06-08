#include "TmxObject.h"
#include <SDG/Exceptions/XmlFormattingException.h>
#include <SDG/Exceptions/XmlValidationException.h>

void SDG::Tiled::TmxObject::Load(const Xml::XmlElement &element)
{
    try {
        LoadImpl(element);
    }
    catch (const XmlValidationException &e)
    {
        SDG_Core_Err("Tiled {}: Xml validation error while parsing element <{}>:line {}: {}",
            name, element.Name(), element.LineNumber(), e.what());
        return;
    }
    catch (const XmlFormattingException &e)
    {
        SDG_Core_Err("Tiled {}: Xml formatting error while parsing element <{}>:line {}: {}",
            name, element.Name(), element.LineNumber(), e.what());
        return;
    }
    catch (const Exception &e)
    {
        SDG_Core_Err("Tiled {}: engine error while loading from xml element <{}>:line {}: {}",
            name, element.Name(), element.LineNumber(), e.what());
    }
    catch (const std::exception &e)
    {
        SDG_Core_Err("Tiled {}: std library error while loading from xml element <{}>:line {}: {}",
            name, element.Name(), element.LineNumber(), e.what());
    }
    catch (...)
    {
        SDG_Core_Err("Tiled {}: unexpected error while loading from xml element <{}>:line {}",
            name, element.Name(), element.LineNumber());
    }

    wasLoaded = true;
}
