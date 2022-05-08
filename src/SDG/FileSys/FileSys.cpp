#include "FileSys.h"
#include "SDG/Debug.hpp"

#include "SDL.h"

#include <vector>

static string
GetPrefPath();

// Cached base path to the executable.

static string appName;
static string orgName;


string
SDG::FileSys::RootPath()
{
    static string basePath;
    if (basePath.empty())
    {
        char *temp = SDL_GetBasePath();
        basePath = temp;
        SDL_free(temp);
    }

    SDG_Assert(!basePath.empty());

    return basePath;
}


string
SDG::FileSys::MakePath(const string &path, Base root)
{
    switch(root)
    {
        case Base::None: return path;
        case Base::Root: return RootPath() + path;
        case Base::Title: return TitleContainer() + path;
        default:
            SDG_Err("SDG::FileSys::MakePath: DirectoryBase was not recognized.");
            return string();
    }
}


string
SDG::FileSys::ExtractFilename(const string &path)
{
    auto pos = path.find_last_of('/');
    return (pos == string::npos) ? path : path.substr(pos + 1);
}


string
SDG::FileSys::GetExtension(const string &path)
{
    string filename = ExtractFilename(path);
    auto pos = filename.find_last_of('.');

    return (pos == string::npos || pos == 0) ? string() : filename.substr(pos + 1);
}

string
GetPrefPath()
{
    static string prefPath;
    if (prefPath.empty())
    {
        char *tPrefPath = SDL_GetPrefPath(orgName.c_str(), appName.c_str());
        prefPath = tPrefPath;
        SDL_free(tPrefPath);
    }

    // There must be a returned path, or else writing is not available on this platform.
    SDG_Assert(!prefPath.empty());

    return prefPath;
}

void
SDG::FileSys::Initialize(const string &appName, const string &org)
{
    ::appName = appName;
    ::orgName = org;
}

string SDG::FileSys::TitleContainer()
{
    return ::TitleContainer();
}
