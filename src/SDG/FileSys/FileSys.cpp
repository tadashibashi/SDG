#include "FileSys.h"
#include <SDG/Debug/Assert.h>
#include <SDL_error.h>
#include <SDL_filesystem.h>
#include <stdexcept>

std::string
SDG::FileSys::BasePath()
{
    if (basePath.empty())
    {
        char *temp = SDL_GetBasePath();
        if (!temp)
        {
            throw std::runtime_error(
                    std::string("Problem retrieving BasePath: ") +
                    SDL_GetError());
        }
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
        if (!tPrefPath)
        {
            throw std::runtime_error(
                    std::string("Problem retrieving PrefPath: ") +
                    SDL_GetError());
        }

        prefPath = tPrefPath;
        SDL_free(tPrefPath);
    }

    SDG_Assert(!prefPath.empty());

    return prefPath;
}
