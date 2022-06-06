#pragma once

#include <SDG/Lib/String.h>

namespace SDG::Tiled
{
    struct Image
    {
        Image() : format(), source(), trans(), width(-1), height(-1) { }

        /// Used for embedded images, in combination with a data child element. 
        /// (Embedded images currently not implemented in Tiled.)
        /// Valid values for file extensions: png, gif, jpg, bmp
        String format;

        /// The reference path to the tileset image file relative to the .tmx file
        String source;

        /// Defines a specific color that is treated as transparent (example value: "#FF00FF" for magenta)
        /// Including the "#" is optional and Tiled leaves it out for compatibility reasons.
        String trans;

        /// The image width in pixels (optional, used for tile index correction when the image changes)
        int width;

        /// The image height in pixels (optional)
        int height
    };
}