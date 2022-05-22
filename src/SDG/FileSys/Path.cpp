/// Path implementation file
#include "Path.h"
#include <SDG/Debug/Assert.h>
#include <SDG/FileSys/FileSys.h>
#include <SDG/Platform.h>

#include <SDL_rwops.h>

#include <ostream>

namespace SDG
{
    std::stack<Ref<FileSys>> Path::fileSys;

    void
    Path::PushFileSys(Ref<FileSys> system)
    {
        Path::fileSys.push(system);
    }

    void
    Path::PopFileSys()
    {
        if (!Path::fileSys.empty())
            Path::fileSys.pop();
    }

    Path::Path() : subpath(), base(BaseDir::None)
    {}

    /// Creates a path with the specified base path.
    /// Trims any preceding forward slashes or white-space of subpath
    Path::Path(const String &pSubpath, BaseDir base) : subpath(), base(base)
    {
        // Only operate if there is a subpath to work with
        if (!pSubpath.Empty())
        {
            if (base == BaseDir::None) // keep path unaltered if BaseDir::None
            {
                subpath = pSubpath;
            }
            else                       // trim path, since it will be appended to BaseDir
            {

                size_t pos = 0, size = pSubpath.Length();
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
                String temp;
                while(pos < size && (pSubpath[pos] == '/' || isspace(pSubpath[pos])))
                    ++pos;
                temp = pSubpath.Substr(pos);

                // Trim any tailing '/' or white-space, or '.'
                if (!temp.Empty())
                {
                    pos = temp.Length();
                    while(pos > 0 && (temp[pos-1] == '/' || isspace(temp[pos-1]) || temp[pos-1] == '.'))
                        --pos;

                    if (pos < temp.Length())
                        temp = temp.Substr(0, pos);
                }

                // finished substring ops, commit the result
                subpath = temp;
            }
        }
    }

    String
    Path::Filename() const
    {
        auto pos = subpath.FindLastOf('/');
        return (pos == String::NullPos) ? subpath : subpath.Substr(pos + 1);
    }

    String
    Path::Extension() const
    {
        String filename = Filename();
        auto pos = filename.FindLastOf('.');

        return (pos == String::NullPos || pos == 0) ? String() : filename.Substr(pos + 1);
    }

    bool
    Path::HasExtension() const
    {
        return !Extension().Empty();
    }

    Path &Path::operator+=(const String &str)
    {
        if (str.Empty()) return *this;

        if (str[0] != '/')
            subpath += '/';
        subpath += str;

        return *this;
    }

    String Path::Str() const
    {
        // FileSys must have been set
        SDG_Assert(!fileSys.empty());
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

            case BaseDir::Base: return fileSys.top()->BasePath() + subpath;
            case BaseDir::Pref: return fileSys.top()->PrefPath() + subpath;
        }

        throw std::runtime_error("SDG::Path::base member value not recognized.");
    }

    bool
    Path::FileExists() const
    {
        SDL_RWops *file = SDL_RWFromFile(Str().Cstr(), "r");

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

    uint64_t
    Path::Hash() const
    {
        const uint64_t p = 31;
        const uint64_t m = 1e9 + 9;
        uint64_t hash = ((uint64_t)base + 1)% m;
        uint64_t pPow = p;
        for (const char *c = subpath.Cstr(); *c != '\0' ; ++c)
        {
            hash = (hash + (*c - 'a' + 1) * pPow) % m;
            pPow = (pPow * p) % m;
        }

        return hash;
    }

    Path
    PrefPath(const String &subpath)
    {
        return {subpath, Path::BaseDir::Pref};
    }

    Path
    BasePath(const String &subpath)
    {
        return {subpath, Path::BaseDir::Base};
    }

    Path
    RootPath(const String &subpath)
    {
        return {subpath, Path::BaseDir::Root};
    }
}

SDG::Path
SDG::operator + (const SDG::Path &path, const SDG::String &str)
{
    return SDG::Path(path) += str;
}

bool
SDG::operator == (const SDG::Path &path, const SDG::String &other)
{
    return path.Str() == other;
}

bool
SDG::operator != (const SDG::Path &path, const SDG::String &other)
{
    return path.Str() != other;
}

bool
SDG::operator == (const SDG::String &other, const SDG::Path &path)
{
    return path.Str() == other;
}

bool
SDG::operator != (const SDG::String &other, const SDG::Path &path)
{
    return path.Str() != other;
}

bool
SDG::operator == (const SDG::Path &path1, const SDG::Path &path2)
{
    return path1.Str() == path2.Str();
}

bool
SDG::operator != (const SDG::Path &path1, const SDG::Path &path2)
{
    return !(path1 == path2);
}
