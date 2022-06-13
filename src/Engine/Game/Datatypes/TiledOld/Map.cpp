#include "Map.h"

void SDG::Tiled::Map::LoadImpl(const Xml::XmlElement &el)
{
    Version version;
    Version tiledVersion;
	RenderOrder renderOrder;
	int compressionLevel;
	size_t width, height,  // size of map in tiles
		tilewidth, tileheight; // size of tiles in pixels
	size_t hexSideLength;  // Only for hexagonal maps. Determines the width or height(depending on the staggered axis) of the tile’s edge, in pixels.
	Axis staggerAxis;
	StaggerIndex staggerIndex;
	int parallaxOriginX;
	int parallaxOriginY;
	Color backgroundColor;
	size_t nextLayerID;
	size_t nextObjectID;
	bool infinite;



}
