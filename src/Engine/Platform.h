/*!
 * @file Platform.h
 * Contains platform definitions for both SDG_Engine and end user.
 * All defines will be set with 1 (true) or 0 (false).
 * Please make sure to check #if (SDG_TARGET_WINDOWS) as opposed to checking
 * with #ifdef or #if defined(SDG_TARGET_WINDOWS).
 * ===========================================================================
 * Windows: SDG_TARGET_WINDOWS
 * Linux  : SDG_TARGET_LINUX
 * MacOS  : SDG_TARGET_MAC
 *    Intel x86_64: SDG_TARGET_MAC_INTEL
 * Desktop: SDG_TARGET_DESKTOP
 *    Either Windows, Linux, or MacOS
 * WebGL  : SDG_TARGET_WEBGL
 *    Built with Emscripten
 *
 * --- Not tested yet ---
 * Android: SDG_TARGET_ANDROID
 * iOS    : SDG_TARGET_IPHONE
 * MacOS ARM64: SDG_TARGET_MAC_SILICON
 * 
 */
#pragma once

// ===== SDG Version ==========================================================

#define SDG_VERSION_MAJOR 0
#define SDG_VERSION_MINOR 0
#define SDG_VERSION_PATCH 1

// ===== SDG Target Platform ==================================================

// HTML5/WebGL
#if   defined(__EMSCRIPTEN__)
    #include <emscripten.h>
    #define SDG_TARGET_WEBGL 1
#else
    #define SDG_TARGET_WEBGL 0
#endif

// Apple
#if defined(__APPLE__) && !defined(__EMSCRIPTEN__)
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
#else
    #define SDG_TARGET_MAC 0
    #define SDG_TARGET_MAC_INTEL 0
    #define SDG_TARGET_MAC_SILICON 0
    #define SDG_TARGET_IOS 0
#endif

// Windows
#if defined(_WIN32) && !defined(__EMSCRIPTEN__)
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
#if defined(__linux__) && !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
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

// Mobile platform checks
#if (SDG_TARGET_IOS || SDG_TARGET_ANDROID)
#define SDG_TARGET_MOBILE 1
#else
#define SDG_TARGET_MOBILE 0
#endif

// ===== Build Type ===========================================================

/// This define is set by CMake when CMAKE_BUILD_TYPE is set to 
/// "Debug" or "RelWithDebugInfo"
#if (DEBUG)
    #define SDG_DEBUG 1
#else
    #define SDG_DEBUG 0
#endif

namespace SDG
{
    /// Gets the string representation of the platform name.
    const char *TargetPlatformName();
}

// ===== Compiler Definitions =================================================

#if defined(WIN32) && defined(_MSC_VER)
#define __func__ __FUNCTION__
#define SDG_MSVC 1
#else
#define SDG_MSVC 0
#endif

#ifdef __clang__
#define SDG_CLANG 1
#else
#define SDG_CLANG 0
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#define SDG_GCC 1
#else
#define SDG_GCC 0
#endif
