//
// Created by Aaron Ishibashi on 4/15/22.
//
#include "XMLReader.h"
#include "SDG/FileSys/FileSys.h"
#include "File.h"

#include "tinyxml2.h"
#include "SDG/Debug.hpp"
#include "SDG/Exceptions/XMLReaderException.h"

using namespace tinyxml2;

static void
CheckResult(int result, const std::string &doing);

static void
OpenXML(const std::string &path, SDG::FileSys::Base base, XMLDocument *outDoc);

bool
SDG::XMLReader::ParseGameConfig(const string &path, GameConfig *config)
{
    if (!config)
    {
        SDG_Err("Error: failed to parse game config file: passed a nullptr GameConfig.");
        return false;
    }



    // Retrieve the window element
    XMLDocument doc; XMLElement *root, *win, *app;
    {
        OpenXML(path, FileSys::Base::Root, &doc);

        root = doc.RootElement();
        if (!root)
        {
            SDG_Err("Could not parse game config file. The xml file is missing a root element.");
            return false;
        }

        app = root->FirstChildElement("app");
        if (!app)
        {
            SDG_Err("Could not parse game config file. It's missing an app element.");
            return false;
        }

        win = root->FirstChildElement("window");
        if (!win)
        {
            SDG_Err("Could not parse game config file. It's missing a window element.");
            return false;
        }
    }

    // Get the attributes
    const char *tTitle; int tWidth, tHeight; bool tFullscreen;
    {
        CheckResult(win->QueryAttribute("fullscreen", &tFullscreen), "querying fullscreen attribute");
        CheckResult(win->QueryAttribute("width", &tWidth), "querying width attribute");
        CheckResult(win->QueryAttribute("height", &tHeight), "querying height attribute");
        CheckResult(win->QueryAttribute("title", &tTitle), "querying title attribute");
    }

    const char *tAppName, *tAppOrg;
    {
        CheckResult(app->QueryAttribute("name", &tAppName), "querying name attribute from app");
        CheckResult(app->QueryAttribute("org", &tAppOrg), "querying org attribute from app");
    }

    config->appName = tAppName;
    config->appOrg = tAppOrg;
    config->title = tTitle;
    config->width = tWidth;
    config->height = tHeight;
    config->fullscreen = tFullscreen;
    return true;
}

// ======= Static helper function implementation =================================================
// Check XMLError; throw exception if a problem occurred.
void
CheckResult(int result, const std::string &doing)
{
    if ((XMLError)result != XML_SUCCESS)
        throw SDG::XMLReaderException(doing, (XMLError)result);
}


void
OpenXML(const std::string &path, SDG::FileSys::Base base, XMLDocument *outDoc)
{
    SDG::FileSys::File file;
    file.Open(SDG::FileSys::MakePath(path, base));
    try {
        CheckResult(outDoc->Parse(reinterpret_cast<const char *>(file.Data())), "loading file at " + path);
    }
    catch(const std::exception &e)
    {
        SDG_Err("Exception while parsing Xml file ({}): {}", path, e.what());
    }
}
