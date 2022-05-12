//
// Created by Aaron Ishibashi on 5/8/22.
//
#include "Path.h"
#include <SDG/FileSys/FileSys.h>
#include <SDG/Platform.h>
#include <SDL_rwops.h>
#include <ostream>

namespace SDG
{
    Path::Path() : subpath(), base(BaseDir::None)
    {}

    /// Creates a path with the specified base path.
    /// Trims any preceding forward slashes or white-space of subpath
    Path::Path(const string &pSubpath, BaseDir base) : subpath(), base(base)
    {
        // Only operate if there is a subpath to work with
        if (!pSubpath.empty())
        {
            if (base == BaseDir::None) // keep path unaltered if BaseDir::None
            {
                subpath = pSubpath;
            }
            else                       // trim path, since it will be appended to BaseDir
            {

                size_t pos = 0, size = pSubpath.size();
#if SDG_TARGET_WINDOWS
                // If Windows, trim letter named drive prefix
                if (base == BaseDir::Root)
                {
                    if (size > 2 && pSubpath[0] == 'C' && pSubpath[1] == ':' && pSubpath[2] == '\\')
                    {
                        pos = 3;
                    }
                }
#endif
                // Trim any white space or '/' in beginning of path
                std::string temp;
                while(pos < size && (pSubpath[pos] == '/' || isspace(pSubpath[pos])))
                    ++pos;
                temp = pSubpath.substr(pos);

                // Trim any tailing '/' or white-space, or '.'
                if (!temp.empty())
                {
                    pos = temp.length();
                    while(pos > 0 && (temp[pos-1] == '/' || isspace(temp[pos-1]) || temp[pos-1] == '.'))
                        --pos;

                    if (pos < temp.length())
                        temp = temp.substr(0, pos);
                }

                // finished substring ops, commit the result
                subpath = temp;
            }
        }
    }

    std::string Path::Filename() const
    {
        auto pos = subpath.find_last_of('/');
        return (pos == string::npos) ? subpath : subpath.substr(pos + 1);
    }

    std::string
    Path::Extension() const
    {
        string filename = Filename();
        auto pos = filename.find_last_of('.');

        return (pos == string::npos || pos == 0) ? string() : filename.substr(pos + 1);
    }

    bool
    Path::HasExtension() const
    {
        return !Extension().empty();
    }

    Path &Path::operator+=(const string &str)
    {
        if (str.empty()) return *this;

        if (str[0] != '/')
            subpath += '/';
        subpath += str;

        return *this;
    }

    std::string Path::String() const
    {
        switch(base)
        {
            case BaseDir::None: return subpath;
            case BaseDir::Root: return
#if SDG_TARGET_WINDOWS
            "C:\\" +
#else
            "/" +
#endif
            subpath;

            case BaseDir::Base: return FileSys::RootPath() + subpath;
            case BaseDir::Pref: return FileSys::TitleContainer() + subpath;
        }

        throw std::runtime_error("SDG::Path::base member value not recognized.");
    }

    bool
    Path::FileExists() const
    {
        SDL_RWops *file = SDL_RWFromFile(String().c_str(), "r");

        if (file)
        {
            SDL_RWclose(file);
            return true;
        }
        else
        {
            return false;
        }
    }

    Path
    PrefPath(const std::string &subpath)
    {
        return {subpath, Path::BaseDir::Pref};
    }

    Path
    BasePath(const std::string &subpath)
    {
        return {subpath, Path::BaseDir::Base};
    }

    Path
    RootPath(const std::string &subpath)
    {
        return {subpath, Path::BaseDir::Root};
    }
}

SDG::Path
operator+(const SDG::Path &path, const string &str)
{
    return SDG::Path(path) += str;
}

std::ostream &
operator<<(std::ostream &os, const SDG::Path &path)
{
    os << path.String();
    return os;
}

bool
operator==(const SDG::Path &path, const std::string &other)
{
    return path.String() == other;
}

bool
operator != (const SDG::Path &path, const std::string &other)
{
    return path.String() != other;
}

bool
operator == (const std::string &other, const SDG::Path &path)
{
    return path.String() == other;
}

bool
operator != (const std::string &other, const SDG::Path &path)
{
    return path.String() != other;
}

bool
operator == (const SDG::Path &path1, const SDG::Path &path2)
{
    return path1.String() == path2.String();
}

bool
operator != (const SDG::Path &path1, const SDG::Path &path2)
{
    return !(path1 == path2);
}
