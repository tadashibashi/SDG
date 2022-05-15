//
// FileSys.h
// SDG_Engine
// 
// Class that contains static helper functions to manipulate file paths.
//
#pragma once
#include <string>
#include <vector>

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
        // The readable and writable directory for this app title.
        // Store saves, preferences, user-data, etc. here.
        Title
    };

    /**
     * Gets the path to the program's root directory, including the final slash.
     * e.g. "path/to/root/".
     * On Mac, this points to the app's Resource folder.
     */
    [[nodiscard]] string RootPath();

    /// Gets the path to this app title's writable file location.
    [[nodiscard]] string TitleContainer();

    /**
     * Makes a path appended to the executable's root directory.
     * @param path The path to append to the root directory.
     * @return The full appended path
     */
    [[nodiscard]] string MakePath(const string &path, Base base);


    void Initialize(const string &pAppName, const string &pOrgName);
}
