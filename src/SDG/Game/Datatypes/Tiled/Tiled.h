#pragma once
#include <SDG/Lib/Version.h>

#define SDG_TILED_VERSION_MAJOR 1
#define SDG_TILED_VERSION_MINOR 8
#define SDG_TILED_VERSION_PATCH 0

#define SDG_TILED_VERSION_MIN SDG_VERSION_HASH(SDG_TILED_VERSION_MAJOR, SDG_TILED_VERSION_MINOR, SDG_TILED_VERSION_PATCH)

/// Checks if Tiled support is available for the specified version
#define SDG_TILED_VERSION_GREATER(major, minor, patch) \
    (SDG_VERSION_HASH(major, minor, patch) >= SDG_TILED_VERSION_MIN)

#if (SDG_TILED_VERSION_GREATER(1, 7, ))
int yo;
#else
int sup;
#endif