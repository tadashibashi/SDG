//
// FileSys.h
// SDG_Engine
// 
// Class that contains static helper functions to manipulate file paths.
//
#pragma once
#include <string>
#include <vector>
#include <SDL_rwops.h>

using std::string;

namespace SDG
{
    /**
     * An SDL_RWops wrapper with a dynamically allocated buffer to memory.
     * This is intended to be used for GPU_Load* functions requiring an RWops
     * object to read from memory.
     */
    struct RWopsMem
    {
        RWopsMem() : memory{}, rwops{} {}

        void Free()
        {
            SDL_FreeRW(rwops);
            free(memory);
            rwops = nullptr;
            memory = nullptr;
        }

        bool IsOpen() const
        {
            return rwops;
        }

        unsigned char *memory;
        SDL_RWops *rwops;
    };
}

namespace SDG::FileSys
{
    /**
     * Gets the path to the program's root directory, including the final slash.
     * e.g. "path/to/root/".
     * On Mac, this points to the app's Resource folder.
     */
    [[nodiscard]] string GetBasePath();


    /**
     * Gets a file name portion from a full or relative path.
     * @param path The file path to perform this function with
     * @return The filename (including extension)
     */
    [[nodiscard]] string GetFileName(const string &path);


    /**
     * Gets the extension of a file from a given path.
     * @param path The path to the file
     * @return The extension, not including the '.', or a blank string if
     * there is none.
     */
    [[nodiscard]] string GetExtension(const string &path);


    /**
     * Makes a path appended to the executable's root directory.
     * @param path The path to append to the root directory.
     * @return The full appended path
     */
    [[nodiscard]] string MakePath(const string &path);

    /**
     * Decrypts a file and returns an RWops wrapper, containing both ptr to data and SDL_RWops.
     * Please make sure to call Free on RWopsMem object when you are done with the data.
     * @param path The path to the file relative to the executable's root dir.
     * @param oFileSize The length of the file bytes buffer to receive.
     * @return RWopsMem, which is a container holding the allocated buffer and SDL_RWops *object.
     */
    [[nodiscard]] RWopsMem DecryptFile(const string &path, int64_t *oFileSize = nullptr);

    /**
     * Decrypts a file and returns an RWops wrapper, containing both ptr to data and SDL_RWops.
     * Additionally, the buffer is appended with a null-terminator, making it a viable c-string.
     * Please make sure to call Free on RWopsMem object when you are done with the data.
     * @param path The path to the file relative to the executable's root dir.
     * @param oStrLen length of the string of data (not counting the null terminator)
     * @return RWopsMem, which is a container holding the allocated buffer and SDL_RWops *object.
     */
    [[nodiscard]] RWopsMem DecryptFileStr(const string &path, int64_t *oStrLen = nullptr);

    /**
     * Writes an encrypted file.
     * @param path
     * @param bytes
     * @return
     */
    bool EncryptFile(const string &path, const string &key, const std::vector<char> &bytes);
}
