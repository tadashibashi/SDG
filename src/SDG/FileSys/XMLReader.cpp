//
// Created by Aaron Ishibashi on 4/15/22.
//
#include "XMLReader.h"
#include "File.h"

#include <SDG/Debug.hpp>
#include <SDG/Exceptions/XMLReaderException.h>

#include <tinyxml2.h>

using namespace tinyxml2;

/// Test a tinyxml2 function that returns a result code
static void
CheckResult(int result, const SDG::String &doing);

/// Safely open an xml document
static void
OpenXML(const SDG::Path &path, tinyxml2::XMLDocument *outDoc);

bool
SDG::XMLReader::ParseGameConfig(const Path &path, GameConfig *config)
{
    if (!config)
    {
        SDG_Core_Err("Error: failed to parse game config file: passed a nullptr GameConfig.");
        return false;
    }

    // Retrieve the window element
    tinyxml2::XMLDocument doc; XMLElement *win;
    {
        XMLElement *root;
        OpenXML(path, &doc);

        root = doc.RootElement();
        if (!root)
        {
            SDG_Core_Err("Could not parse game config file. The xml file is missing a root element.");
            return false;
        }

        win = root->FirstChildElement("window");
        if (!win)
        {
            SDG_Core_Err("Could not parse game config file. It's missing a window element.");
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

    config->title = tTitle;
    config->width = tWidth;
    config->height = tHeight;
    config->fullscreen = tFullscreen;
    return true;
}

// ======= Static helper function implementation =================================================
// Check XMLError; throw exception if a problem occurred.
void
CheckResult(int result, const SDG::String &doing)
{
    if ((XMLError)result != XML_SUCCESS)
        throw SDG::XMLReaderException(doing, (XMLError)result);
}


void
OpenXML(const SDG::Path &path, XMLDocument *outDoc)
{
    SDG::File file;
    file.Open(path);
    try {
        CheckResult(outDoc->Parse(reinterpret_cast<const char *>(file.Data())),
                    "loading file at " + path.Str());
    }
    catch(const std::exception &e)
    {
        SDG_Core_Err("Exception while parsing Xml file ({}): {}", path.Str(),
                e.what());
    }
}
