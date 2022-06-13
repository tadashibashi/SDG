#include "Filesys.h"

#include <Engine/Debug/Assert.h>
#include <Engine/Exceptions/RuntimeException.h>
#include <Engine/Filesys/Path.h>

#include <SDL_error.h>
#include <SDL_filesystem.h>

static SDG::String basePath;

SDG::Filesys::Filesys(const String &pAppName, const String &pOrgName)
    : appName(pAppName), orgName(pOrgName), prefPath()
{
    
}

SDG::Filesys::Filesys()
    : appName(), orgName(), prefPath()
{

}

void
SDG::Filesys::Initialize(const String &pAppName, const String &pOrgName)
{
    appName = pAppName;
    orgName = pOrgName;
}

SDG::String
SDG::Filesys::BasePath()
{
    if (basePath.Empty())
    {
        char *temp = SDL_GetBasePath();
        if (!temp)
        {
            throw RuntimeException(
                    String("Problem retrieving BasePath: ") +
                    SDL_GetError());
        }
        basePath = temp;
        SDL_free(temp);
    }

    SDG_Assert(!basePath.Empty());

    return basePath;
}


SDG::String
SDG::Filesys::PrefPath() const
{
    if (prefPath.Empty())
    {
        char *tPrefPath = SDL_GetPrefPath(orgName.Cstr(), appName.Cstr());
        if (!tPrefPath)
        {
            throw RuntimeException(
                    String("Problem retrieving PrefPath with org name \"") + 
                    orgName + String(", and app name \"" + appName + "\"") +
                    SDL_GetError());
        }

        prefPath = tPrefPath;
        SDL_free(tPrefPath);
    }

    SDG_Assert(!prefPath.Empty());

    return prefPath;
}

