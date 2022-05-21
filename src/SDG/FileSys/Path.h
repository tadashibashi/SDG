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
#include <SDG/Ref.h>
#include <SDG/String.h>

#include <spdlog/fmt/ostr.h>

#include <stack>

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
        Path(const String &pSubpath, BaseDir base = BaseDir::None);

        /// Get the subpath portion, not including base path
        [[nodiscard]] const String &Subpath() const { return subpath; }

        [[nodiscard]] bool Empty() const { return subpath.Empty() && base == BaseDir::None; }

        /// Calculates a hash identifier for the path
        [[nodiscard]] uint64_t Hash() const;

        /// Checks whether the Path has an extension.
        [[nodiscard]] bool HasExtension() const;
        /// Checks whether a file exists at the path.
        [[nodiscard]] bool FileExists() const;
        /// Gets the file extension of the Path if there is one.
        [[nodiscard]] String Extension() const;
        /// Gets the file name (or directory name) if there is one, or a blank string
        /// if not.
        [[nodiscard]] String Filename() const;

        /// Retrieves the Path Base type set in the constructor.
        [[nodiscard]] BaseDir Base() const { return base; }

        /// Gets the full path, subpath appended to the base path, as a string
        [[nodiscard]] String Str() const;

        /// Gets the full path, including the base path, as a string
        explicit operator String() const { return Str(); }

        /// You can add strings to the Path, which is appended to the internal subpath
        Path &operator += (const String &str);

        /// Set the current file system that each Path object will evaluate paths by.
        /// All calls to String() are affected. Therefore, one Path object may
        /// evaluate a different String() once the FileSys has changed.
        /// In this way, multiple FileSys objects are supported, but one should be careful
        /// to return the FileSys to the original expected system by calling PopFileSys() afterward.
        static void PushFileSys(Ref<FileSys> system);

        /// Removes the last FileSys that was pushed.
        static void PopFileSys();

        template <typename Ostream>
        friend Ostream &operator << (Ostream &os, const Path &path)
        {
            os << path.Str().Cstr();
            return os;
        }
    private:
        String subpath;
        BaseDir base;
        static std::stack<Ref<FileSys>> fileSys;
    };

    /// Helper: creates a path stemming from the app personal preference directory (read/write)
    Path PrefPath(const String &subpath = String());
    /// Helper: creates a path stemming from the app's base working directory (read only)
    Path BasePath(const String &subpath = String());
    Path RootPath(const String &subpath = String());

    Path operator + (const Path &path, const String &str);

    /// Path <-> string comparison
    bool operator == (const Path &path, const String &other);
    bool operator != (const Path &path, const String &other);
    bool operator == (const String &other, const Path &path);
    bool operator != (const String &other, const Path &path);
    /// Path <-> Path comparison
    bool operator == (const Path &path1, const Path &path2);
    bool operator != (const Path &path1, const Path &path2);
}

