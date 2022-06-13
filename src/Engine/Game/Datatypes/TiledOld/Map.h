#pragma once
#include "TmxObject.h"
#include "Properties.h"

#include <Engine/Lib/Version.h>
#include <Engine/Graphics/Color.h>

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

	class Map : public TmxObject
	{
	public:
		Map() : TmxObject("map") { }

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

		Properties properties;
		// Todo: add sub objects

	private:
		void LoadImpl(const Xml::XmlElement &el);
	};
}