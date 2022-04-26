#pragma once

#include <SDG/Graphics/Texture2D.h>

namespace SDG
{
    class SpriteBatch
    {
        struct BatchCall
        {
            Texture2D *texture;

        };
    public:
        SpriteBatch();
        ~SpriteBatch();

        // no copying
        SpriteBatch(const SpriteBatch &) = delete;
        SpriteBatch &operator=(const SpriteBatch &) = delete;

    };
}
