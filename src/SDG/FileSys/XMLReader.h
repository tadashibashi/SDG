//
// Created by Aaron Ishibashi on 4/15/22.
//
#pragma once
#include <string>
#include <SDG/FileSys/Structs/GameConfig.h>

using std::string;

namespace SDG
{
    class XMLReader {
    public:
        static bool ParseGameConfig(const string &path, GameConfig *config);
    };
}
