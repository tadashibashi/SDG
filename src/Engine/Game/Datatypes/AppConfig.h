/* ====================================================================================================================
 * @file    AppConfig.h – SDG_Engine
 * @author  Aaron Ishibashi
 *
 * @class   SDG::AppConfig
 * Contains basic information to start an application
 *
 * ==================================================================================================================*/
#pragma once
#include <Engine/Lib/String.h>
#include <Engine/Filesys/Path.h>

#include <cstdint>

namespace SDG
{
    class AppConfig
    {
    public:
        AppConfig() : width(), height(), winFlags(), title(), appName(), orgName() { }
        AppConfig(int width, int height, uint32_t winFlags, const String &title, const String &appName, const String &orgName) :
            width(width), height(height), winFlags(winFlags), title(title), appName(appName), orgName(orgName) { }

        int width, height;
        uint32_t winFlags;
        String title, appName, orgName;

        bool LoadJson(const Path &path);
    };
}
