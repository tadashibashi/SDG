//
//  IO.cpp
//  SDG_Engine
//
//  Low-level functions to read and write files.
//
#include "IO.h"
#include "SDL_rwops.h"

static const SDG::String encryptionKey = "john316";
static SDG::String errorStr = "No errors.";

static bool
ReadFileStrImpl(const char *path, uint8_t **data, size_t *size, bool appendNull);

static SDL_RWops *
_OpenRW(const char *path, const char *mode, int64_t *oFileSize);

bool
SDG::IO::ReadFile(const char *path, uint8_t **data, size_t *size)
{
    return ReadFileStrImpl(path, data, size, false);
}

bool
SDG::IO::ReadFileStr(const char *path, uint8_t **data, size_t *size)
{
    return ReadFileStrImpl(path, data, size, true);
}

bool
ReadFileStrImpl(const char *path, uint8_t **data, size_t *size, bool appendNull)
{
    SDL_RWops *io;
    uint8_t *mem;
    int64_t fileSize;

    // open the file
    io = _OpenRW(path, "rb", &fileSize);
    if (!io)
    {
        errorStr = SDL_GetError();
        return false;
    }

    // load file to memory
    mem = (uint8_t *)malloc(fileSize + (int)appendNull); // +1 for null terminator
    if (!mem)
    {
        errorStr = SDG::String("error while allocating memory buffer: out of memory");
        SDL_RWclose(io);
        return false;
    }

    // Read file all at once. Underlying system should handle buffering.
    if (io->read(io, mem, fileSize, 1) != 1)
    {
        errorStr = SDG::String("error while reading file: ") + SDL_GetError();
        free(mem);
        SDL_RWclose(io);
        return false;
    }

    if (appendNull)
        mem[fileSize] = '\0'; // append null terminator to make file readable as a c-string.


    // close file
    if (SDL_RWclose(io) < 0)
    {
        errorStr = SDG::String("error while closing file: ") + SDL_GetError();
        free(mem);
        return false;
    }

    if (size)
        *size = fileSize;

    *data = mem;
    errorStr = SDG::String("No errors.");
    return true;
}


SDL_RWops *
_OpenRW(const char *path, const char *mode, int64_t *oFileSize)
{
    SDL_RWops *io = SDL_RWFromFile(path, mode);
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
_DecryptFile(const char *path, bool nullTerminated, uint8_t **mem, size_t *oFileSize)
{
    int64_t fileSize;
    SDL_RWops *io = _OpenRW(path, "rb", &fileSize);
    if (!io) // errorStr set within OpenRW
        return false;

    // Allocate buffer, and fill it with encrypted data
    uint8_t *fileData;
    fileData = (uint8_t *)malloc(fileSize + nullTerminated); // +1 for null terminator to make it a valid c-str

    int position = 0;
    for (uint8_t *ptr = fileData, *end = fileData + fileSize; ptr != end; ++ptr)
    {
        uint8_t c;
        size_t objsRead = SDL_RWread(io, &c, 1, 1);
        if (objsRead == 0)
        {
            errorStr = SDG::String("error while reading file: ") + SDL_GetError();
            free(fileData);
            SDL_RWclose(io);
            return false;
        }

        unsigned char add = encryptionKey[position % encryptionKey.Length()];
        *ptr = (unsigned char)(c - add + position);
        *ptr ^= ~add;
        ++position;
    }

    if (SDL_RWclose(io) < 0)
    {
        errorStr = SDG::String("error while closing file: ") + SDL_GetError();
        free(fileData);
        return false;
    }

    if (nullTerminated)
        fileData[fileSize] = '\0';

    if (oFileSize)
        *oFileSize = (size_t)fileSize;

    *mem = (uint8_t *)fileData;
    return true;
}


bool
SDG::IO::ReadEncryptedFile(const char *path, uint8_t **mem, size_t *oFileSize)
{
    return _DecryptFile(path, false, mem, oFileSize);
}


bool
SDG::IO::ReadEncryptedFileStr(const char *path, uint8_t **mem, size_t *oFileSize)
{
    return _DecryptFile(path, true, mem, oFileSize);
}

bool
SDG::IO::WriteEncryptedFile(const char *path, const uint8_t *mem, size_t size)
{
    // TODO: Implement saving backup of any preexisting file if there is an error during writing.
    SDL_RWops *io = _OpenRW(path, "w+b", nullptr);
    if (!io)
    {
        return false;
    }

    // Encrypt file
    int bytesRead = 0;
    for (const uint8_t *p = mem, *end = mem + size; p != end; ++p)
    {
        uint8_t c = *p;
        uint8_t add = (uint8_t)encryptionKey[bytesRead % encryptionKey.Length()];
        c ^= ~add;
        c = (unsigned char)(c + add - bytesRead);
        size_t objsWritten = SDL_RWwrite(io, &c, 1, 1);

        if (objsWritten != 1)
        {
            SDL_RWclose(io);
            return false;
        }

        ++bytesRead;
    }
    SDL_RWclose(io);

    return true;
}

bool
SDG::IO::WriteFile(const char *path, const uint8_t *mem, size_t size)
{
    SDL_RWops *io = _OpenRW(path, "w+b", nullptr);
    if (!io)
    {
        return false;
    }

    size_t writtenObjs = SDL_RWwrite(io, mem, size, 1);
    if (writtenObjs != 1)
    {
        SDL_RWclose(io);
        return false;
    }
    
    SDL_RWclose(io);
    return true;
}

SDG::String SDG::IO::GetError()
{
    return errorStr;
}
