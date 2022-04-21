//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "FileSys.h"
#include "Logging.h"
#include <SDL.h>
#include <vector>

static SDL_RWops *
_LoadFile(const string &path, int64_t *oFileSize);

static SDG::RWopsMem
_DecryptFile(const string &path, bool nullTerminated, int64_t *oFileSize);

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

static const int RWopsErrorCode = -1;


SDL_RWops *
_LoadFile(const string &path, int64_t *oFileSize)
{
    SDL_RWops *io = SDL_RWFromFile(path.c_str(), "rb");
    if (!io)
    {
        SDG_Err("Failed to load file ({}): {}", path, SDL_GetError());
        return nullptr;
    }

    // Get the length of the file
    if (SDL_RWseek(io, 0, RW_SEEK_END) == -1)
    {
        SDG_Err("Failure while seeking file ({}), cancelling file load: {}", path, SDL_GetError());
        SDL_FreeRW(io);
        return nullptr;
    }

    int64_t fileSize = SDL_RWtell(io);
    if (fileSize == -1)
    {
        SDG_Err("Buffer position could not be determined in file ({}): {}", path, SDL_GetError());
    }

    if (SDL_RWseek(io, 0, RW_SEEK_SET) == -1)
    {
        SDG_Err("Failure while seeking file ({}), cancelling file load: {}", path, SDL_GetError());
        SDL_FreeRW(io);
        return nullptr;
    }

    if (oFileSize)
        *oFileSize = fileSize;

    return io;
}


// private helper to load / decrypt a file
SDG::RWopsMem
_DecryptFile(const string &path, bool nullTerminated, int64_t *oFileSize)
{
    SDG::RWopsMem returnThis;
    string fullPath = SDG::FileSys::MakePath(path).append(".sdgc");

    int64_t fileSize;
    SDL_RWops *io = _LoadFile(fullPath, &fileSize);
    if (!io)
        return returnThis;

    // Allocate buffer, and fill it with encrypted data
    unsigned char *fileData = (unsigned char *)malloc(fileSize + (int)nullTerminated); // +1 for null terminator to make it a valid c-str

    int position = 0;
    for (unsigned char *ptr = fileData, *end = fileData + fileSize; ptr != end; ++ptr)
    {
        unsigned char c;
        SDL_RWread(io, &c, 1, 1);
        unsigned char add = encryptionKey[position % encryptionKey.length()];

        *ptr = (unsigned char)(c - add + position);
        *ptr ^= ~add;
        ++position;
    }
    SDL_FreeRW(io);

    if (nullTerminated)
        fileData[fileSize] = '\0';

    io = SDL_RWFromMem(fileData, (int)fileSize + (int)nullTerminated);
    if (!io)
    {
        SDG_Err("Failed to create RWops from memory: {}", SDL_GetError());
        return returnThis;
    }

    if (oFileSize)
        *oFileSize = fileSize;
    returnThis.memory = fileData;
    returnThis.rwops = io;

    return returnThis;
}


SDG::RWopsMem
SDG::FileSys::DecryptFile(const string &path, int64_t *oFileSize)
{
    return _DecryptFile(path, false, oFileSize);
}


SDG::RWopsMem
SDG::FileSys::DecryptFileStr(const string &path, int64_t *oFileSize)
{
    return _DecryptFile(path, true, oFileSize);
}

// TODO: Implement Encrypt File (saving files)
bool
SDG::FileSys::EncryptFile(const string &path, const string &key, const std::vector<char> &bytes)
{
    return false;
}
