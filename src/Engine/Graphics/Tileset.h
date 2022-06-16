#pragma once

namespace SDG
{
    class Tileset
    {
        struct Impl;
    public:
        Tileset();
        ~Tileset();
    private:
        Impl *impl;
    };
}
