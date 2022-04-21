//
// FileSys.h
// SDG_Engine
// 
// Class that contains static helper functions to manipulate file paths.
//
#pragma once
#include <string>

#include <SDL_rwops.h>

#include <vector>

using std::string;

namespace SDG
{
    struct RWopsMem
    {
        RWopsMem() : memory{}, rwops{} {}

        void Free()
        {
            SDL_FreeRW(rwops);
            free(memory);
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
    string GetBasePath();


    /**
     * Gets a file name portion from a full or relative path.
     * @param path The file path to perform this function with
     * @return The filename (including extension)
     */
    string GetFileName(const string &path);


    /**
     * Gets the extension of a file from a given path.
     * @param path The path to the file
     * @return The extension, not including the '.', or a blank string if
     * there is none.
     */
    string GetExtension(const string &path);


    /**
     * Makes a path appended to the executable's root directory.
     * @param path The path to append to the root directory.
     * @return The full appended path
     */
    string MakePath(const string &path);

    /**
     * Decrypts a file and returns an RWops handle, or nullptr if it failed.
     * @param path The path to the file relative to the executable's root dir.
     * @return Handle to the file or nullptr if there was an error.
     */
    RWopsMem DecryptFile(const string &path, int64_t *oFileSize = nullptr);
}
