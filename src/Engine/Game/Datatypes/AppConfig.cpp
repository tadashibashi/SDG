#include "AppConfig.h"
#include <SDL_video.h>
#include <Engine/Filesys/Json.h>

bool SDG::AppConfig::LoadJson(const Path &path)
{
    String tName, tOrg, tTitle;
    uint32_t tWinFlags = 0;
    int tWidth, tHeight;

    json j = OpenJson(path);
    auto &app  = j.at("app");
    tName     = app.at("name");
    tOrg      = app.at("org");

    auto &window = j.at("window");
    tTitle = window.value("title", "");
    tWidth = window["size"].value("x", 640);
    tHeight = window["size"].value("y", 480);
    if (window.value("borderless", false)) 
        tWinFlags |= SDL_WINDOW_BORDERLESS;
    if (window.value("fullscreen", false))
        tWinFlags |= SDL_WINDOW_FULLSCREEN;
    if (window.value("hidden", false))
        tWinFlags |= SDL_WINDOW_HIDDEN;

    appName = tName;
    orgName = tOrg;
    title = tTitle;
    winFlags = tWinFlags;
    width = tWidth;
    height = tHeight;
    return true;
}
