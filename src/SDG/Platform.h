//
// Platform-specific headers and defines.
// SDG Engine will only support 64-bit operating systems.
//
#pragma once

#if   defined(__EMSCRIPTEN__)
    #include <emscripten.h>

    #define SDG_TARGET_HTML5 1
#elif defined(__APPLE__)
    #include <TargetConditionals.h>

    #if (TARGET_OS_IPHONE)
        #define SDG_TARGET_IPHONE 1
    #elif (TARGET_OS_MAC)
        #define SDG_TARGET_MAC 1
        #if (TARGET_CPU_ARM64)
            #define SDG_MAC_SILICON 1
        #elif (TARGET_CPU_X86_64)
            #define SDG_MAC_INTEL 1
        #endif
    #endif
#elif defined(_WIN32)
    #if !defined(_WIN64)
    #error Windows 32-bit not supported!
    #endif

    #define SDG_TARGET_WINDOWS 1
#elif defined(__ANDROID__)
    #define SDG_TARGET_ANDROID 1
#elif defined(__linux__) && !defined(__ANDROID__)
    #define SDG_TARGET_LINUX 1
#endif

#if defined(DEBUG) || defined(_DEBUG)
    #define SDG_DEBUG 1
#endif

#ifndef SDG_TARGET_WINDOWS
    // Please don't use the return value of strcpy
    #define strcpy_s(dest, dsize, src) strcpy(dest, src)
#endif