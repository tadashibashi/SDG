//
// Created by Aaron Ishibashi on 4/15/22.
//

#include "FileSys.h"
#include "Debug.h"
#include <SDL.h>
#include <vector>

static SDL_RWops *
_LoadFile(const string &path, int64_t *oFileSize);

static SDG::RWopsMem
_DecryptFile(const string &path, bool nullTerminated, int64_t *oFileSize);

static string
GetPrefPath();

// Cached base path to the executable.

static string appName;
static string orgName;
static const string encryptionKey = "john316";

string
SDG::FileSys::GetBasePath()
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
        case Base::Root: return GetBasePath() + path;
        case Base::Pref: return GetPrefPath() + path;
        default:
            SDG_Err("SDG::FileSys::MakePath: DirectoryBase was not recognized.");
            return string();
    }
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
_DecryptFile(const string &path, SDG::FileSys::Base base, bool nullTerminated, int64_t *oFileSize)
{
    SDG::RWopsMem returnThis;
    string fullPath = SDG::FileSys::MakePath(path, base);

    int64_t fileSize;
    SDL_RWops *io = _LoadFile(fullPath, &fileSize);
    if (!io)
        return returnThis;

    // Allocate buffer, and fill it with encrypted data
    auto *fileData = (unsigned char *)malloc(fileSize + (int)nullTerminated); // +1 for null terminator to make it a valid c-str

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
SDG::FileSys::DecryptFile(const string &path, Base base, int64_t *oFileSize)
{
    return _DecryptFile(path, base, false, oFileSize);
}


SDG::RWopsMem
SDG::FileSys::DecryptFileStr(const string &path, Base base, int64_t *oFileSize)
{
    return _DecryptFile(path, base, true, oFileSize);
}

bool
SDG::FileSys::EncryptFile(const string &path, const std::vector<unsigned char> &bytes)
{
    // TODO: Implement saving backup of any preexisting file if there is an error during writing.

    SDL_RWops *io = SDL_RWFromFile((GetPrefPath() + path).c_str(), "w+b");
    if (!io)
    {
        SDG_Err("Problem opening file at ({}) for writing.", path);
        return false;
    }

    // Encrypt file
    int bytesRead = 0;
    for(unsigned char c : bytes)
    {
        unsigned char add = encryptionKey[bytesRead % encryptionKey.length()];
        c ^= ~add;
        c = (unsigned char)(c + add - bytesRead);
        size_t bytesWritten = io->write(io, &c, 1, 1);

        if (bytesWritten == 0)
        {
            SDG_Err("Error while writing file ({}): {}", path, SDL_GetError());
            return false;
        }

        ++bytesRead;
    }
    SDG_Log("Wrote file to path: {}", GetPrefPath() + path);
    SDL_RWclose(io);

    return true;
}

void
SDG::FileSys::Initialize(const string &appName, const string &org)
{
    ::appName = appName;
    ::orgName = org;
}
