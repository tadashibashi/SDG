//
// Created by Aaron Ishibashi on 4/15/22.
//
#include "XMLReader.h"
#include "FileSys.h"
#include <tinyxml2.h>
#include "Logging.h"
#include <exception>

using namespace tinyxml2;



class XMLReaderException : public std::exception
{


public:
    XMLReaderException(const std::string &doing, XMLError error)
    {
        message = "XMLReaderException occurred while " + doing
                  + ": ";
        message += XMLDocument::ErrorIDToName(error);
    }

    const char *what() const noexcept override
    {
        return message.c_str();
    }


private:
    std::string message;

};


// Check XMLError; throw exception if a problem occurred.
void
CheckResult(int result, const std::string &doing)
{
    if ((XMLError)result != XML_SUCCESS)
        throw XMLReaderException(doing, (XMLError)result);
}


static void
OpenXML(const std::string &path, XMLDocument *outDoc)
{
    int64_t size;
    SDG::RWopsMem io = SDG::FileSys::DecryptFileStr(path);
    try {
        CheckResult(outDoc->Parse(reinterpret_cast<char *>(io.memory)), "loading file at " + path);
    }
    catch(const std::exception &e)
    {
        SDG_Err("Exception while parsing Xml document ({}): {}", path, e.what());
        io.Free();
        throw e;
    }

    io.Free();
}


bool
SDG::XMLReader::ParseGameConfig(const std::string &path, std::string *title, int *width, int *height, bool *fullscreen)
{
    // Retrieve the window element
    XMLDocument doc; XMLElement *win;
    {
        OpenXML(path, &doc);

        auto root = doc.RootElement();
        if (!root)
        {
            SDG_Err("Could not parse game config file. The xml file is missing a root element.");
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



    *title = tTitle;
    *width = tWidth;
    *height = tHeight;
    *fullscreen = tFullscreen;
    return true;
}
