#include "FileSys.h"
#include <SDG/Debug/Assert.h>
#include <SDL_filesystem.h>

std::string
SDG::FileSys::BasePath()
{
    if (basePath.empty())
    {
        char *temp = SDL_GetBasePath();
        basePath = temp;
        SDL_free(temp);
    }

    SDG_Assert(!basePath.empty());

    return basePath;
}

void
SDG::FileSys::Initialize(const std::string &pAppName, const std::string &pOrgName)
{
    appName = pAppName;
    orgName = pOrgName;
}

std::string
SDG::FileSys::PrefPath()
{
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
