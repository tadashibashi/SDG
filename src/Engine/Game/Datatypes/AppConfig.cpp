#include "AppConfig.h"
#include <SDL_video.h>
#include <Engine/Filesys/Json.h>
#include <Engine/Exceptions.h>

namespace SDG
{
    static void ParseWindow(const json &j, AppConfig::Window &window)
    {
        String tTitle; int tWidth, tHeight; uint32_t tWinFlags = 0;

        tTitle = j.value("title", "");
        tWidth = j["size"].value("x", 640);
        tHeight = j["size"].value("y", 480);
        if (j.value("borderless", false))
            tWinFlags |= SDL_WINDOW_BORDERLESS;
        if (j.value("fullscreen", false))
            tWinFlags |= SDL_WINDOW_FULLSCREEN;
        if (j.value("hidden", false))
            tWinFlags |= SDL_WINDOW_HIDDEN;

        window.title = std::move(tTitle);
        window.width = tWidth;
        window.height = tHeight;
        window.winFlags = tWinFlags;
    }

    void AppConfig::LoadJsonImpl(const json &j)
    {
        String tName, tOrg;
        std::vector<AppConfig::Window> tWindows;

        auto &app  = j.at("app");
        tName     = app.at("name").get<String>();
        tOrg      = app.at("org").get<String>();

        if (auto window = app.find("window") != app.end())
        {
            AppConfig::Window w;
            ParseWindow(window, w);
            tWindows.emplace_back(w);
        }
        else if (auto windows = app.find("windows") != app.end())
        {
            for(auto &window : app.at("windows"))
            {
                AppConfig::Window w;
                ParseWindow(window, w);
                tWindows.emplace_back(w);
            }
        }
        else
        {
            throw DomainException("Missing an app \"window\" or \"windows\" field in config file");
        }

        appName = tName;
        orgName = tOrg;
        windows.swap(tWindows);
    }
}
