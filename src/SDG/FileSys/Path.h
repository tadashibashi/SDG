/*!
 * @file    Path.h – SDG_Engine
 * @author  Aaron Ishibashi
 *
 * @class   Path
 * @description Wrapper around a string, with helper functions to designate filepaths.
 * User can specify path base to stem from. (More info on base paths in enum class Path::Base).
 *
 */
#pragma once
#include <iosfwd>
#include <string>
#include <SDG/Ref.h>

namespace SDG
{
    class FileSys;

     /// Wrapper around a string, representing a full filepath.
     /// User can specify path base to stem from. More info in enum class Path::Base.
    class Path
    {
    public:
        /// An identifier representing the path to base the Path's subpath from.
        enum class BaseDir {
            /// No base directory to stem from. What you see is what you get.
            None,
            /// Stems from OS root. On Mac/Linux it's "/", while on Windows it's "C:\\"
            Root,
            /// User specifies subpath relative from the App executable's base working directory.
            /// This directory is intended as read-only, although some platforms allow writing.
            /// Content such as audio and images are usually stored here.
            Base,
            /// User specifies subpath relative from the App's personal preference directory.
            /// This directory is granted to the App for reading and writing files,
            /// intended for save data, user preferences, etc.
            Pref
        };

        /// Creates an empty path with no base directory
        Path();

        /// Creates a path with specified base directory and subpath
        /// @param pSubpath the subpath, which will append to the base directory
        /// @param base the base directory from which the subpath will root from
        Path(const std::string &pSubpath, BaseDir base = BaseDir::None);

        /// Get the subpath portion, not including base path
        [[nodiscard]] const std::string &Subpath() const { return subpath; }

        /// Checks whether the Path has an extension.
        [[nodiscard]] bool HasExtension() const;
        /// Checks whether a file exists at the path.
        [[nodiscard]] bool FileExists() const;
        /// Gets the file extension of the Path if there is one.
        [[nodiscard]] std::string Extension() const;
        /// Gets the file name (or directory name) if there is one, or a blank string
        /// if not.
        [[nodiscard]] std::string Filename() const;

        /// Retrieves the Path Base type set in the constructor.
        [[nodiscard]] BaseDir Base() const { return base; }

        /// Gets the full path, subpath appended to the base path, as a string
        [[nodiscard]] std::string String() const;

        /// Gets the full path, including the base path, as a string
        explicit operator std::string() const { return String(); }

        /// You can add strings to the Path, which is appended to the internal subpath
        Path &operator += (const std::string &str);

        static void SetFileSys(Ref<FileSys> system);
    private:
        std::string subpath;
        BaseDir base;
        static Ref<FileSys> fileSys;
    };

    /// Helper: creates a path stemming from the app personal preference directory (read/write)
    Path PrefPath(const std::string &subpath = std::string());
    /// Helper: creates a path stemming from the app's base working directory (read only)
    Path BasePath(const std::string &subpath = std::string());
    Path RootPath(const std::string &subpath = std::string());
}

SDG::Path operator + (const SDG::Path &path, const std::string &str);
std::ostream &operator << (std::ostream &os, const SDG::Path &path);

/// Path <-> string comparison
bool operator == (const SDG::Path &path, const std::string &other);
bool operator != (const SDG::Path &path, const std::string &other);
bool operator == (const std::string &other, const SDG::Path &path);
bool operator != (const std::string &other, const SDG::Path &path);
/// Path <-> Path comparison
bool operator == (const SDG::Path &path1, const SDG::Path &path2);
bool operator != (const SDG::Path &path1, const SDG::Path &path2);
