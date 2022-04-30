//
// Created by Aaron Ishibashi on 4/30/22.
//
#pragma once
#include <string>
#include <SDG/FileSys/FileSys.h>
#include <utility>

namespace SDG
{
    struct FileInfo
    {
    public:
        FileInfo() : path(), base(), isEncrypted() {}
        FileInfo(std::string path, FileSys::Base base, bool isEncrypted)
        : path(std::move(path)), base(base), isEncrypted(isEncrypted) {}

        [[nodiscard]] std::string Path() const
        {
            return FileSys::MakePath(path, base);
        }

        [[nodiscard]] bool IsEncrypted() const
        {
            return isEncrypted;
        }

        bool operator== (const FileInfo &other)
        {
            return isEncrypted == other.isEncrypted
            && base == other.base
            && path == other.path;
        }

        bool operator!= (const FileInfo &other)
        {
            return !(*this == other);
        }

    private:
        std::string path;
        FileSys::Base base;
        bool isEncrypted;
    };
}

