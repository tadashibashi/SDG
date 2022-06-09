#include "AppConfig.h"
#include <SDL_video.h>

bool SDG::AppConfig::LoadImpl(const Xml::XmlDocument &doc)
{
    String tName, tOrg, tTitle;
    uint32_t tWinFlags = 0;
    int tWidth, tHeight;

    auto config = doc.FirstChild("config", Xml::Required); // add requirements to doc

    auto app = config.FirstChild("app", Xml::Required);
    tName = app.Attribute("name", Xml::Required).Value();
    tOrg  = app.Attribute("org", Xml::Required).Value();

    auto window = config.FirstChild("window", Xml::Required);
    tWidth  = window.Attribute("width", Xml::Required).IntValue();
    tHeight = window.Attribute("height", Xml::Required).IntValue();
    if (auto attr = window.Attribute("fullscreen"))
        tWinFlags = attr.BoolValue() ? tWinFlags |= SDL_WINDOW_FULLSCREEN : tWinFlags;    
    if (auto attr = window.Attribute("borderless"))
        tWinFlags = attr.BoolValue() ? tWinFlags |= SDL_WINDOW_BORDERLESS : tWinFlags;
    if (auto attr = window.Attribute("hidden"))
        tWinFlags = attr.BoolValue() ? tWinFlags |= SDL_WINDOW_HIDDEN : tWinFlags;

    appName = tName;
    orgName = tOrg;
    width   = tWidth;
    height  = tHeight;
    winFlags = tWinFlags;
    title   = tTitle;

    return true;
}