//
// Created by Aaron Ishibashi on 4/30/22.
//
#include <string>

namespace SDG
{
    struct GameConfig
    {
        int width, height;
        bool fullscreen;
        std::string appName, appOrg, title;
    };
}
