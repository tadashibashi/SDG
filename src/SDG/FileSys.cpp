//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "FileSys.h"
#include "Logging.h"
#include <SDL.h>
#include <vector>


// Cached base path to the executable.
static const string basePath = SDL_GetBasePath();
static const string encryptionKey = "john316";

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

SDG::RWopsMem
SDG::FileSys::DecryptFile(const string &path, int64_t *oFileSize)
{
    RWopsMem ret;
    string fullPath = MakePath(path) + ".sdgc";
    SDL_RWops *io = SDL_RWFromFile(fullPath.c_str(), "rb");
    if (!io)
    {
        SDG_Err("Failed to load file ({}): {}", path, SDL_GetError());
        return ret;
    }

    unsigned char *fileData;

    // Get the length of the file
    SDL_RWseek(io, 0, RW_SEEK_END);
    Sint64 fileSize = SDL_RWtell(io);
    if (oFileSize)
        *oFileSize = fileSize;
    SDL_RWseek(io, 0, RW_SEEK_SET);
    fileData = (unsigned char *)malloc(fileSize);

    int position = 0;
    for (unsigned char *ptr = fileData, *end = fileData + fileSize; ptr != end; ++ptr)
    {
        unsigned char c;
        SDL_RWread(io, &c, 1, 1);
        unsigned char add = encryptionKey[position % encryptionKey.length()];

        *ptr = (unsigned char)(c - add + position);

        ++position;
    }
    SDL_FreeRW(io);

    io = SDL_RWFromMem(fileData, (int)fileSize);
    if (!io)
    {
        SDG_Err("Failed to create RWops from memory: {}", SDL_GetError());
        return ret;
    }

    ret.memory = fileData;
    ret.rwops = io;

    return ret;
}
