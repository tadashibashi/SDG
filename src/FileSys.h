//
// Created by Aaron Ishibashi on 4/15/22.
//

#pragma once
#include <string>
using std::string;

namespace SDG
{
    class FileSys {
    public:
        static string GetBasePath();
        static string GetFileName(const string &path);
        static string GetExtension(const string &path);
        static string MakePath(const string &path);
    };
}

