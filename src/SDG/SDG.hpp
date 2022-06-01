#pragma once

#include "App.h"
#include "AssetMgr.h"
#include "Platform.h"

// Todo: make a Lib super header
#include "Lib/Endian.h"
#include "Lib/Ref.h"
#include "Lib/String.h"
#include "Lib/ServiceProvider.h"
#include "Lib/Delegate.h"
#include "Lib/FixedPool.h"
#include "Lib/Pool.h"
#include "Lib/Memory.h"
#include "Lib/Swap.h"
#include "Lib/StringView.h"
#include "Lib/Unique.h"
#include "Lib/ClassMacros.h"

#include "FileSys.hpp"
#include "Graphics.hpp"
#include "Math.hpp"
#include "Input.hpp"
#include "Debug.hpp"

// Todo: create a header for MSVC undefs
#ifdef CreateWindow
#undef CreateWindow
#endif