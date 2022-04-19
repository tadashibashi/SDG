//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "FileSys.h"
#include <SDL.h>

static const string basePath = SDL_GetBasePath();

string
SDG::FileSys::GetBasePath()
{
    return basePath;
}

string
SDG::FileSys::MakePath(const string &path)
{
    return basePath + path;
}

string
SDG::FileSys::GetFileName(const string &path)
{
    auto pos = path.find_last_of('/');
    return (pos == string::npos) ? path : path.substr(pos + 1);
}

string
SDG::FileSys::GetExtension(const string &path)
{
    string filename = GetFileName(path);
    auto pos = filename.find_last_of('.');

    return (pos == string::npos || pos == 0) ? string() : filename.substr(pos + 1);
}
