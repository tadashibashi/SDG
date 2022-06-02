//
// Created by Aaron Ishibashi on 4/15/22.
//
#pragma once
#include <SDG/FileSys/Structs/AppConfig.h>
#include "Path.h"

using std::string;

namespace SDG
{
    class XMLReader {
    public:
        static bool ParseGameConfig(const SDG::Path &path, AppConfig *config);
    };
}
