#pragma once

namespace SDG
{
    class Tilemap
    {
        struct Impl;
    public:
        Tilemap();
        Tilemap(const Tilemap &tiles);
        Tilemap &operator= (const Tilemap &tiles);
        Tilemap(Tilemap &&tiles) noexcept;
        Tilemap &operator= (Tilemap &&tiles) noexcept;
        ~Tilemap();

        void Close();
    private:
        Impl *impl;
    };
}