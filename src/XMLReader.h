//
// Created by Aaron Ishibashi on 4/15/22.
//
#pragma once
#include <string>

namespace SDG
{
    class XMLReader {
    public:
        static bool ParseGameConfig(const std::string &path, std::string *title, int *width, int *height, bool *fullscreen);
    };
}
