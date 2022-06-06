#include "Platform.h"

const char *SDG::TargetPlatformName()
{
    static const char *platformName;

    if (!platformName)
    {
        if (SDG_TARGET_MAC_INTEL)
            platformName = "Apple MacOS Intel";
        else
        if (SDG_TARGET_MAC_SILICON)
            platformName = "Apple MacOS Apple Silicon";
        else
        if (SDG_TARGET_IOS)
            platformName = "Apple iOS";
        else
        if (SDG_TARGET_LINUX)
            platformName = "Linux";
        else
        if (SDG_TARGET_WINDOWS)
            platformName = "Windows";
        else
        if (SDG_TARGET_WEBGL)
            platformName = "WebGL Emscripten";
        else
        if (SDG_TARGET_ANDROID)
            platformName = "Android";
        else
        platformName = "Unknown";
    }

    return platformName;
}