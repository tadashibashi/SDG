//
//  IO.cpp
//  SDG_Engine
//
//  Low-level functions to read and write files.
//
#include "IO.h"
#include <cassert>
#include <SDL_rwops.h>
#include <string>
#include <vector>

using std::string;

static const string encryptionKey = "john316";
static string errorStr = "No errors.";

static bool
ReadFileStrImpl(const char *path, char **data, size_t *size, bool appendNull);

static bool
ReadEncryptedFileStrImpl(const char *path, char **data, size_t *size, bool appendNull);

static SDL_RWops *
_OpenRW(const char *path, const char *mode, int64_t *oFileSize);

bool
SDG::IO::ReadFile(const char *path, char **data, size_t *size)
{
    return ReadFileStrImpl(path, data, size, false);
}

bool
SDG::IO::ReadFileStr(const char *path, char **data, size_t *size)
{
    return ReadFileStrImpl(path, data, size, true);
}

bool
ReadFileStrImpl(const char *path, char **data, size_t *size, bool appendNull)
{
    SDL_RWops *io;
    char *mem;
    int64_t fileSize;

    // open the file
    io = _OpenRW(path, "rb", &fileSize);
    if (!io)
    {
        errorStr = SDL_GetError();
        return false;
    }

    // load file to memory
    mem = (char *)malloc(fileSize + (int)appendNull); // +1 for null terminator
    if (!mem)
    {
        errorStr = string("error while allocating memory buffer: out of memory");
        SDL_RWclose(io);
        return false;
    }

    // Read file all at once. Underlying system should handle buffering.
    if (io->read(io, mem, fileSize, 1) != 1)
    {
        errorStr = string("error while reading file: ") + SDL_GetError();
        free(mem);
        SDL_RWclose(io);
        return false;
    }

    if (appendNull)
        mem[fileSize] = '\0'; // append null terminator to make file readable as a c-string.


    // close file
    if (SDL_RWclose(io) < 0)
    {
        errorStr = string("error while closing file: ") + SDL_GetError();
        free(mem);
        return false;
    }

    *data = mem;
    errorStr = string("No errors.");
    return true;
}


SDL_RWops *
_OpenRW(const char *path, const char *mode, int64_t *oFileSize)
{
    SDL_RWops *io = SDL_RWFromFile(path, "rb");
    if (!io)
    {
        errorStr = SDL_GetError();
        return nullptr;
    }

    int64_t size = SDL_RWsize(io);
    if (size < 0)
    {
        errorStr = SDL_GetError();
        return nullptr;
    }

    if (oFileSize)
        *oFileSize = size;

    return io;
}


// private helper to load / decrypt a file
bool
_DecryptFile(const char *path, bool nullTerminated, char **mem, size_t *oFileSize)
{
    int64_t fileSize;
    SDL_RWops *io = _OpenRW(path, "rb", &fileSize);
    if (!io) // errorStr set within OpenRW
        return false;

    // Allocate buffer, and fill it with encrypted data
    auto *fileData = (unsigned char *)malloc(fileSize + nullTerminated); // +1 for null terminator to make it a valid c-str

    int position = 0;
    for (unsigned char *ptr = fileData, *end = fileData + fileSize; ptr != end; ++ptr)
    {
        unsigned char c;
        size_t objsRead = SDL_RWread(io, &c, 1, 1);
        if (objsRead == 0)
        {
            errorStr = string("error while reading file: ") + SDL_GetError();
            free(fileData);
            SDL_RWclose(io);
            return false;
        }

        unsigned char add = encryptionKey[position % encryptionKey.length()];
        *ptr = (unsigned char)(c - add + position);
        *ptr ^= ~add;
        ++position;
    }

    if (SDL_RWclose(io) < 0)
    {
        errorStr = string("error while closing file: ") + SDL_GetError();
        free(fileData);
        return false;
    }

    if (nullTerminated)
        fileData[fileSize] = '\0';

    if (oFileSize)
        *oFileSize = (size_t)fileSize;

    *mem = (char *)fileData;
    return true;
}


bool
SDG::IO::ReadEncryptedFile(const char *path, char **mem, size_t *oFileSize)
{
    return _DecryptFile(path, false, mem, oFileSize);
}


bool
SDG::IO::ReadEncryptedFileStr(const char *path, char **mem, size_t *oFileSize)
{
    return _DecryptFile(path, true, mem, oFileSize);
}

bool
SDG::IO::WriteEncryptedFile(const char *path, const std::vector<unsigned char> &bytes)
{
    // TODO: Implement saving backup of any preexisting file if there is an error during writing.
    SDL_RWops *io = _OpenRW(path, "w+b", nullptr);
    if (!io)
    {
        return false;
    }

    // Encrypt file
    int bytesRead = 0;
    for(unsigned char c : bytes)
    {
        unsigned char add = encryptionKey[bytesRead % encryptionKey.length()];
        c ^= ~add;
        c = (unsigned char)(c + add - bytesRead);
        size_t objsWritten = SDL_RWwrite(io, &c, 1, 1);

        if (objsWritten == 0)
        {
            return false;
        }

        ++bytesRead;
    }
    SDL_RWclose(io);

    return true;
}

string SDG::IO::GetError()
{
    return errorStr;
}
