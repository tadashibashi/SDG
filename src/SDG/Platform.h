/// ===== Platform Indicators Definitions ====================
/// Windows: SDG_TARGET_WINDOWS 1
/// Linux  : SDG_TARGET_LINUX 1
/// MacOS  : SDG_TARGET_MAC 1
///    Intel: SDG_TARGET_MAC_INTEL 1
/// Desktop: SDG_TARGET_DESKTOP 1
///    Either Windows, Linux, or MacOS
/// WebGL  : SDG_TARGET_WEBGL 1
///    Built with Emscripten

/// --- Not tested yet ---
/// Android: SDG_TARGET_ANDROID 1
/// iOS    : SDG_TARGET_IPHONE 1
/// MacOS ARM64: SDG_TARGET_MAC_SILICON 1
#pragma once

#if   defined(__EMSCRIPTEN__)
    #include <emscripten.h>
    #define SDG_TARGET_WEBGL 1
#else
    #define SDG_TARGET_WEBGL 0
#endif

// Apple
#if defined(__APPLE__)
    #include <TargetConditionals.h>

    // Mac
    #if (TARGET_OS_MAC)
        #define SDG_TARGET_MAC 1

        #if (TARGET_CPU_ARM64)
            #define SDG_TARGET_MAC_SILICON 1
            #define SDG_TARGET_MAC_INTEL 0
        #elif (TARGET_CPU_X86_64)
            #define SDG_TARGET_MAC_INTEL 1
            #define SDG_TARGET_MAC_SILICON 0
        #endif
    #else
        #define SDG_TARGET_MAC 0
        #define SDG_TARGET_MAC_SILICON 0
        #define SDG_TARGET_MAC_INTEL 0
    #endif

    // iOS
    #if (TARGET_OS_IOS)
        #define SDG_TARGET_IOS 1
    #else
        #define SDG_TARGET_IOS 0
    #endif
#endif

// Windows
#if defined(_WIN32)
    #if !defined(_WIN64)
    #error Windows 32-bit not supported!
    #endif
    #define SDG_TARGET_WINDOWS 1
#else
    #define SDG_TARGET_WINDOWS 0
#endif

// Android
#if defined(__ANDROID__)
    #define SDG_TARGET_ANDROID 1
#else
    #define SDG_TARGET_ANDROID 0
#endif

// Linux Desktop
#if defined(__linux__) && !defined(__ANDROID__)
    #define SDG_TARGET_LINUX 1
#else
    #define SDG_TARGET_LINUX 0
#endif

// Desktop platform checks
#if SDG_TARGET_WINDOWS || SDG_TARGET_LINUX || SDG_TARGET_MAC
    #define SDG_TARGET_DESKTOP 1
#else
    #define SDG_TARGET_DESKTOP 0
#endif


/// DEBUG is defined by CMake when CMAKE_BUILD_TYPE is set to Debug or RelWithDebugInfo
/// Usage: #if SDG_DEBUG
#if defined(DEBUG) || defined(_DEBUG)
    #define SDG_DEBUG 1
#else
    #define SDG_DEBUG 0
#endif

/// Compatibility
#if (!SDG_TARGET_WINDOWS)
    // MSVC complains if strcpy is used, preferring strcpy_s instead.
    // For non-MSVC compilers, we convert it to strcpy for compatibility.
    // Note: please do not use the return value of strcpy_s
    #define strcpy_s(dest, dsize, src) strcpy(dest, src)
#endif

