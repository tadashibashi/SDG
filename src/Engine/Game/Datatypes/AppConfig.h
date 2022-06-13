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
#include <Engine/Filesys/Json/JsonLoadable.h>

#include <vector>
#include <cstdint>

namespace SDG
{
    class AppConfig : public JsonLoadable
    {
    public:
        AppConfig() : JsonLoadable("AppConfig"), windows(), appName(), orgName() { }
        AppConfig(int width, int height, uint32_t winFlags, const String &title, const String &appName, const String &orgName) :
            JsonLoadable("AppConfig"), windows(), appName(appName), orgName(orgName)
        {
            windows.emplace_back(Window{ width, height, winFlags, title });
        }

        struct Window
        {
            Window() : width(), height(), winFlags(), title() { }
            Window(int width, int height, uint32_t winFlags, const String &title) :
                width(width), height(height), winFlags(winFlags), title(title) { }
            int width, height;
            uint32_t winFlags;
            String title;
        };

        String appName, orgName;
        std::vector<Window> windows;
    private:
        void LoadJsonImpl(const json &j) override;
    };
}
