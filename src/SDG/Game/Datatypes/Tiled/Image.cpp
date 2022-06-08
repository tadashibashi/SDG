#include "Image.h"
#include <SDG/FileSys/Path.h>
#include <algorithm>

void SDG::Tiled::Image::LoadImpl(const Xml::XmlElement &el)
{
    // Required
    // not supported by Tiled because embedded images aren't used. 
    // Just grab from source's extension for now.
    String format; 
    String source;

    // Optional
    int width = -1, height = -1;
    StringView transStr;

    el.Attribute("source", Xml::Required).Query(source);
    el.Attribute("format", Xml::Optional).Query(format);
    if (format.Empty())
        format = Path(source).Filename();

    el.Attribute("width").Query(width);
    el.Attribute("height").Query(height);
    el.Attribute("trans").Query(transStr);
    Color trans;
    if (!transStr.Empty())
    {

    }
   

    
}
