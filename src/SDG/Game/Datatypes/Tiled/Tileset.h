#pragma once
#include <SDG/FileSys/Xml/XmlElement.h>
#include <SDG/Lib/Version.h>
#include <SDG/Graphics/Color.h>

namespace SDG::Tiled
{
	enum class MapOrientation
	{
		Orthogonal,
		Isometric,
		Staggered,
		Hexagonal
	};

	// The order in which tiles on tile layers are rendered
	// In all cases, the map is drawn row-by-row (only supported by orthogonal maps at the moment)
	enum class RenderOrder
	{
		RightDown, // default
		RightUp,
		LeftDown,
		LeftUp
	};

	enum class Axis
	{
		X, Y
	};

	enum class StaggerIndex
	{
		Even, Odd
	};

	struct Tileset
	{
		Version version;
		Version tiledVersion;
		RenderOrder renderOrder;
		int compressionLevel;
		size_t width, height,  // size of map in tiles
		tileWidth, tileHeight; // size of tiles in pixels
		size_t hexSideLength;  // Only for hexagonal maps. Determines the width or height(depending on the staggered axis) of the tile’s edge, in pixels.
		Axis staggerAxis;
		StaggerIndex staggerIndex;
		int parallaxOriginX;
		int parallaxOriginY;
		Color backgroundColor;
		size_t nextLayerID;
		size_t nextObjectID;
		bool infinite;

		// Todo: add sub objects
	};
}