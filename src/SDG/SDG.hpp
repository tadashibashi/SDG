#pragma once

#include "App.h"
#include "AssetMgr.h"
#include "Platform.h"
#include "Ref.h"
#include "String.h"
#include "ServiceProvider.h"

#include "Templates/Delegate.h"
#include "Templates/FixedPool.h"
#include "Templates/Pool.h"

#include "FileSys.hpp"
#include "Graphics.hpp"
#include "Math.hpp"
#include "Input.hpp"
#include "Debug.hpp"

// Todo: create a header for MSVC undefs
#ifdef CreateWindow
#undef CreateWindow
#endif