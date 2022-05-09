//
// Created by Aaron Ishibashi on 5/8/22.
//
#include "Path.h"
#include <SDG/FileSys/FileSys.h>

namespace SDG
{
    Path::Path() : subpath(), base(Base::None)
    {}

    /// Creates a path with the specified base path.
    /// Trims any preceding forward slashes or white-space of subpath
    Path::Path(const string &pSubpath, Base base) : subpath(), base(base)
    {
        // Only operate if there is a subpath to work with
        if (!pSubpath.empty())
        {
            // Trim any white space or '/' in beginning of path
            size_t pos = 0, size = pSubpath.size();
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
    Path::HasExtension(std::string *outExt) const
    {
        std::string ext = Extension();
        if (outExt)
            *outExt = ext;

        return !ext.empty();
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
            case Base::None: return "/" + subpath;
            case Base::Root: return FileSys::RootPath() + subpath;
            case Base::Title: return FileSys::TitleContainer() + subpath;
        }
    }

    Path
    TitlePath(const std::string &subpath)
    {
        return Path(subpath, Path::Base::Title);
    }

    Path
    RootPath(const std::string &subpath)
    {
        return Path(subpath, Path::Base::Root);
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
