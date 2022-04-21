//
// Created by Aaron Ishibashi on 4/15/22.
//
#pragma once
#include <string>
using std::string;

namespace SDG
{
    class XMLReader {
    public:
        static bool ParseGameConfig(const string &path, string *appName,
                string *appOrg, string *title, int *width, int *height, bool *fullscreen);
    };
}
