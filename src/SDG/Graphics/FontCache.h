#pragma once
#include <SDG/FileSys/Path.h>
#include <SDG/Graphics/Texture.h>

#include <map>

namespace SDG
{
    enum class FontStyle : uint32_t {
        Solid = 1u,
        Shaded = 1u << 1u,
        Blended = 1u << 2u
    };

    enum class TextAlignX {
        Left,
        Center,
        Right
    };

    enum class TextAlignY {
        Top,
        Center,
        Bottom
    };

    /// Stores common characters and glyphs, and renders them
    class FontCache
    {
        bool Load(const Path &path, uint32_t fontStyleFlags = FontStyle::Blended);

        void RenderSolid(Ref<class RenderTarget>, const String &text, Vector2 position, Vector2 scale, float angle, float depth, Color color, uint32_t wrapLength = 0);
        void RenderShaded(Ref<class RenderTarget>, const String &text, Vector2 position, Vector2 scale, float angle, float depth, Color fgColor, Color bgColor, uint32_t wrapLength = 0);
        void RenderBlended(Ref<class RenderTarget>, const String &text, Vector2 position, Vector2 scale, float angle, float depth, Color color, uint32_t wrapLength = 0);
    private:
        std::map<char, Texture> textures;
        class TrueTypeFont *font;
    };
}
