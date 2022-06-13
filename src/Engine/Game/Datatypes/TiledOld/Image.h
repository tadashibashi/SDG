#pragma once
#include "TmxObject.h"
#include <Engine/Graphics/Color.h>
#include <Engine/Lib/String.h>

namespace SDG::Tiled
{
    
    class Image : public TmxObject
    {
    public:
        Image() : TmxObject("image"), format(), source(), trans(), width(-1), height(-1) { }

        /// Used for embedded images, in combination with a data child element. 
        /// (Embedded images currently not implemented in Tiled.)
        /// Valid values for file extensions: png, gif, jpg, bmp
        String Format() const { return format; }

        /// The reference path to the image file relative to the .tmx file
        const String &Source() const { return source; }

        /// Defines a specific color that is treated as transparent
        const Color &Transparent() const { return trans; }

        /// The image width in pixels (optional, used for tile index correction when the image changes)
        int Width() const { return width; }

        /// The image height in pixels (optional)
        int Height() const { return height; }
    private:
        void LoadImpl(const Xml::XmlElement &el);

        String format;
        
        String source;

        /// Defines a specific color that is treated as transparent (example value: "#FF00FF" for magenta)
        /// Including the "#" is optional and Tiled leaves it out for compatibility reasons.
        Color trans;

        /// The image width in pixels (optional, used for tile index correction when the image changes)
        int width;

        /// The image height in pixels (optional)
        int height;
    };
}
