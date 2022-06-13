#pragma once
#include "TmxObject.h"
#include <Engine/Lib/String.h>

namespace SDG::Tiled
{
    enum class ObjectAlignment
    {
        Unspecified, // default
        TopLeft,
        Top,
        TopRight,
        Left,
        Center,
        Right,
        BottomLeft,
        Bottom,
        BottomRight
    };

    class Tileset : public TmxObject
    {
    public:
        Tileset() : TmxObject("tileset") { }

        unsigned FirstGID() const { return firstgid; }
        const String &Source() const { return source; }
    private:
        unsigned firstgid;

        // If this tileset is stored in an external TSX (Tile Set XML) file, this
        // attribute refers to that file. That TSX file has the same structure as the
        // <tileset> element described here. (There is the firstgid attribute missing and
        // this source attribute is also not there. These two attributes are kept in the 
        // TMX map, since they are map specific.)
        String source;
        String name;
        unsigned tilewidth, tileheight;

        // The spacing in pixels between the tiles in this tileset (applies to
        // the tileset image, defaults to 0). Irrelevant for image collection tilesets.
        unsigned spacing = 0;
        unsigned margin = 0;
        unsigned tilecount;

        // The number of tile columns in the tileset. For image collection tilesets it is 
        // editable and is used when displaying the tileset. (since 0.15)
        unsigned columns;

        // Controls the alignment for tile objects. Valid values are unspecified,
        // topleft, top, topright, left, center, right, bottomleft, bottom and
        // bottomright. The default value is unspecified, for compatibility reasons. 
        // When unspecified, tile objects use bottomleft in orthogonal mode and bottom
        // in isometric mode. (since 1.4)
        ObjectAlignment objectalignment;
        
    };
}