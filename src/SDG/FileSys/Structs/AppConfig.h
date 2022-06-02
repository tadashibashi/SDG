//
// Created by Aaron Ishibashi on 4/30/22.
//
#pragma once
#include <SDG/Lib/String.h>

namespace SDG
{
    struct AppConfig
    {
        int width, height;
        bool fullscreen;
        String title, appName, orgName;
    };
}
