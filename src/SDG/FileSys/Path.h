#pragma once
#include <string>
#include <SDG/FileSys/FileSys.h>
#include <iosfwd>

namespace SDG
{
     /// Wrapper around a string, representing a full filepath.
     /// User can specify path base to stem from. More info in enum class Path::Base.
    class Path
    {
    public:
        /// An identifier representing the path to base the Path's subpath from.
        enum class BaseDir {
            /// No base path, stems from OS root. User must specify the full filepath.
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

        /// Creates an empty path
        Path();
        Path(const std::string &pSubpath, BaseDir base = BaseDir::Root);

        /// Get the subpath portion, not including base path
        std::string Subpath() const { return subpath; }

        /// Checks whether the Path has an extension.
        /// Optionally retrieve the extension by passing string ptr.
        bool HasExtension(std::string *outExt = nullptr) const;
        std::string Extension() const;
        std::string Filename() const;

        /// Retrieves the Path Base type set in the constructor.
        BaseDir Base() const { return base; }

        /// Gets the full path, including the base path, as a string
        std::string String() const;

        /// Gets the full path, including the base path, as a string
        explicit operator std::string() const { return String(); }

        /// You can add strings to the Path, which is appended to the internal subpath
        Path &operator += (const std::string &str);
    private:
        std::string subpath;
        BaseDir base;
    };

    /// Helper: creates a path stemming from the app personal preference directory (read/write)
    Path PrefPath(const std::string &subpath = std::string());
    /// Helper: creates a path stemming from the app's base working directory (read only)
    Path BasePath(const std::string &subpath = std::string());
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
