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
static string prefPath = basePath;
static string appName;
static string orgName;
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
        SDL_RWclose(io);
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
        SDL_RWclose(io);
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
    SDL_RWclose(io);

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
SDG::FileSys::EncryptFile(const string &path, const std::vector<char> &bytes)
{
    SDL_RWops *io = SDL_RWFromFile((prefPath + path).c_str(), "w+b");
    if (!io)
    {
        SDG_Err("Problem opening file at ({}) for writing.", path);
        return false;
    }

    // Encrypt file
    int bytesRead = 0;
    for(char byte : bytes)
    {
        unsigned char c = byte;
        unsigned char add = encryptionKey[bytesRead % encryptionKey.length()];
        c ^= ~add;
        c = (unsigned char)(c + add - bytesRead);
        size_t bytesWritten = io->write(io, &c, 1, 1);

        if (bytesWritten == 0)
        {
            SDG_Err("Error while writing file ({}): {}", path, SDL_GetError());
            return false;
        }
    }
    SDG_Log("Wrote file to path: {}", prefPath + path);
    SDL_RWclose(io);

    return true;
}

void
SDG::FileSys::SetAppInfo(const string &name, const string &org)
{
    char *tPrefPath = SDL_GetPrefPath(org.c_str(), name.c_str());
    ::prefPath.copy(tPrefPath, strlen(tPrefPath));
    SDG_Log("name {}, org {} => prefPath received: {} {}", name, org, prefPath, tPrefPath);
    SDL_free(tPrefPath);

    ::appName = name;
    ::orgName = org;
}
