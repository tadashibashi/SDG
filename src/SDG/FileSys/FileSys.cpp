#include "FileSys.h"

#include <SDG/Debug/Assert.h>
#include <SDG/Exceptions/RuntimeException.h>

#include <SDL_error.h>
#include <SDL_filesystem.h>

SDG::FileSys::FileSys(const String &pAppName, const String &pOrgName)
    : appName(pAppName), orgName(pOrgName), basePath(), prefPath()
{

}

SDG::FileSys::FileSys()
    : appName(), orgName(), basePath(), prefPath()
{

}

void
SDG::FileSys::Initialize(const String &pAppName, const String &pOrgName)
{
    appName = pAppName;
    orgName = pOrgName;
}

SDG::String
SDG::FileSys::BasePath() const
{
    if (basePath.Empty())
    {
        char *temp = SDL_GetBasePath();
        if (!temp)
        {
            throw RuntimeException(
                    std::string("Problem retrieving BasePath: ") +
                    SDL_GetError());
        }
        basePath = temp;
        SDL_free(temp);
    }

    SDG_Assert(!basePath.Empty());

    return basePath;
}


SDG::String
SDG::FileSys::PrefPath() const
{
    if (prefPath.Empty())
    {
        char *tPrefPath = SDL_GetPrefPath(orgName.Cstr(), appName.Cstr());
        if (!tPrefPath)
        {
            throw RuntimeException(
                    std::string("Problem retrieving PrefPath: ") +
                    SDL_GetError());
        }

        prefPath = tPrefPath;
        SDL_free(tPrefPath);
    }

    SDG_Assert(!prefPath.Empty());

    return prefPath;
}

