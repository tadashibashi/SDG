//
// FileSys.h
// SDG_Engine
// 
// Class that contains static helper functions to manipulate file paths.
//
#pragma once
#include <string>
#include <vector>
#include "SDL_rwops.h"

using std::string;
using std::vector;

namespace SDG::FileSys
{
    /**
     * Enumeration dictating which relative directory for certain functions to base off of.
     */
    enum class Base {
        // Represents no directory to root from
        None,
        // The directory of the executable, or if Mac, the App's Resources sub-folder. Read-only.
        // While this directory may be writable on some systems, it is not portable to do so.
        // It is preferred to use the Pref directory for writes.
        Root,
        // The readable and writable directory to store saves, preferences, user-data, etc.
        Pref
    };

    /**
     * Gets the path to the program's root directory, including the final slash.
     * e.g. "path/to/root/".
     * On Mac, this points to the app's Resource folder.
     */
    [[nodiscard]] string GetBasePath();

    /// Gets the path to the program's writable file location.
    [[nodiscard]] string GetPrefPath();

    /**
     * Gets a file name portion from a full or relative path.
     * @param path The file path to perform this function with
     * @return The filename (including extension)
     */
    [[nodiscard]] string GetFileName(const string &path);


    /**
     * Gets the extension of a file from a given path.
     * @param path The path to the file
     * @return The extension, not including the '.'. A blank string
     * will be returned if there is no extension.
     */
    [[nodiscard]] string GetExtension(const string &path);

    /**
     * Makes a path appended to the executable's root directory.
     * @param path The path to append to the root directory.
     * @return The full appended path
     */
    [[nodiscard]] string MakePath(const string &path, Base base);


    void Initialize(const string &appName, const string &org);
}
