//
// Created by Aaron Ishibashi on 5/8/22.
//
#include "Path.h"
#include <SDG/FileSys/FileSys.h>

namespace SDG
{
    Path::Path() : subpath(), base(Base::None)
    {

    }

    Path::Path(const string &path, Base base) : subpath(), base(base)
    {
        // ignore any white space or '/' in beginning of path
        if (!path.empty())
        {
            size_t pos = 0, size = path.size();
            while(pos < size && (path[pos] == '/' || isspace(path[pos])))
                ++pos;
            subpath = path.substr(pos);
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
        subpath += str;
        return *this;
    }

    std::string Path::String() const
    {
        switch(base)
        {
            case Base::None: return subpath;
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

SDG::Path operator+(const SDG::Path &path, const string &str)
{
    return SDG::Path(path) += str;
}

std::string operator+(const string &str, const SDG::Path &path)
{
    return str + path.String();
}

std::ostream &operator<<(std::ostream &os, const SDG::Path &path)
{
    os << path.String();
    return os;
}