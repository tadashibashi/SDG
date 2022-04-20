//
// FileSys.h
// SDG_Engine
// 
// Class that contains static helper functions to manipulate file paths.
//
#pragma once
#include <string>
using std::string;

namespace SDG
{
    class FileSys {
    public:


        /// <summary>
        /// Gets the path to the program's root directory, including the final slash.
        /// e.g. "path/to/root/".
        /// On Mac, this points to the app's Resource folder.
        /// </summary>
        static string GetBasePath();


        /// <summary>
        /// Helper function that returns the file name of a given path.
        /// </summary>
        /// <param name="path">The path to perform this function with</param>
        /// <returns>The filename (including extension)</returns>
        static string GetFileName(const string &path);


        /// <summary>
        /// Gets the extension of a file from a given path.
        /// </summary>
        /// <param name="path">The path to the file</param>
        /// <returns>The extension, not including the '.', or a blank string if
        /// there is none.</returns>
        static string GetExtension(const string &path);


        /// <summary>
        /// Makes a path appended to the executable's base path.
        /// </summary>
        /// <param name="path">The path to append to the base path.</param>
        /// <returns>The full appended path</returns>
        static string MakePath(const string &path);
    };
}
