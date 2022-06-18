/// Master header that aims to include every relevant header in SDG Engine
#pragma once

#include "Engine.h"
#include "Game/AssetMgr.h"
#include "Game/Component.h"
#include "Game/ComponentList.h"
#include "Game/Datatypes/AppConfig.h"
#include "Game/Entity.h"
#include "Game/Graphics/Camera2D.h"
#include "Game/Graphics/Frame.h"
#include "Game/Graphics/Sprite.h"
#include "Game/Graphics/SpriteBatch.h"
#include "Game/Graphics/SpriteRenderer.h"
#include "Game/Graphics/Tile.h"
#include "Game/Graphics/Tilemap.h"
#include "Game/Graphics/Tileset.h"


// Todo: make a Lib super header
#include "Lib/Endian.h"
#include "Lib/Ref.h"
#include "Lib/String.h"
#include "Lib/Delegate.h"
#include "Lib/FixedPool.h"
#include "Lib/Pool.h"
#include "Lib/Memory.h"
#include "Lib/Swap.h"
#include "Lib/StringView.h"
#include "Lib/Unique.h"
#include "Lib/ClassMacros.h"

#include "Filesys.h"
#include "Graphics.h"
#include "Math.h"
#include "Input.h"
#include "Debug.h"

// Todo: create a header for MSVC undefs
#ifdef CreateWindow
#undef CreateWindow
#endif
