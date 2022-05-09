#pragma once
#include <string>
#include <SDG/FileSys/FileSys.h>
#include <iosfwd>

namespace SDG
{
    /*!
     * Wrapper around a string, representing a full filepath.
     * User can specify path base to root from. More info in enum class Path::Base.
     */
    class Path
    {
    public:
        /// An identifier representing the path to base the Path's subpath from.
        enum class Base {
            /// No base path, user must specify the full filepath
            None,
            /// User specifies subpath relative from the App's root executable directory.
            /// This directory is intended as read-only, although some platforms allow writing.
            /// Content such as audio and images are usually stored here.
            Root,
            /// User specifies subpath relative from the App's title directory.
            /// This directory is granted to the App for reading and writing files,
            /// intended for save data, user preferences, etc.
            Title
        };

        /// Creates an empty path
        Path();
        Path(const std::string &pSubpath, Base base = Base::None);

        /// Get the subpath portion, not including base path
        std::string SubPath() const { return subpath; }

        /// Checks whether the Path has an extension.
        /// Optionally retrieve the extension by passing string ptr.
        bool HasExtension(std::string *outExt = nullptr) const;
        std::string Extension() const;
        std::string Filename() const;

        /// Retrieves the Path Base type set in the constructor.
        Base BaseID() const { return base; }

        /// Gets the full path, including the base path, as a string
        std::string String() const;

        /// Gets the full path, including the base path, as a string
        explicit operator std::string() const { return String(); }

        /// You can add strings to the Path, which is appended to the internal subpath
        Path &operator += (const std::string &str);
    private:
        std::string subpath;
        Base base;
    };

    /// Helper to create a path stemming from the app title's container
    Path TitlePath(const std::string &subpath = std::string());
    /// Helper to create a path stemming from the app's root
    Path RootPath(const std::string &subpath = std::string());
}

SDG::Path operator + (const SDG::Path &path, const std::string &str);
std::ostream &operator <<(std::ostream &os, const SDG::Path &path);

/// Compares full Path with a standard string
inline bool operator == (const SDG::Path &path, const std::string &other) { return path.String() == other; }
inline bool operator != (const SDG::Path &path, const std::string &other) { return path.String() != other; }
inline bool operator == (const std::string &other, const SDG::Path &path) { return path.String() == other; }
inline bool operator != (const std::string &other, const SDG::Path &path) { return path.String() != other; }
inline bool operator == (const SDG::Path &path1, const SDG::Path &path2)
    { return path1.String() == path2.String(); }
inline bool operator != (const SDG::Path &path1, const SDG::Path &path2) { return !(path1 == path2); }
