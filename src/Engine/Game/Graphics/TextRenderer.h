#pragma once
#include <Engine/Lib/Ref.h>
#include <Engine/Graphics/Font.h>
#include <Engine/Math/Rectangle.h>

namespace SDG
{
    class TextRenderer
    {
    public:
        auto Font() const -> const Ref<class Font> { return font; }
        auto Text() const -> const String &{ return text; }
        auto Scale() const { return scale; }
        auto Position() const { return position; }
        auto Alignment() const { return alignment; }
        auto Color() const { return color; }

        auto Font(Ref<class Font> font) -> TextRenderer &{ this->font = font; return *this; }
        auto Text(const String text) -> TextRenderer &{ this->text = text; return *this; }
        auto Scale(const Vector2 &scale) -> TextRenderer &{ this->scale = scale; return *this; }
        auto Position(const Vector2 &position) -> TextRenderer &{ this->position = position; return *this; }
        auto Alignment(FontAlign alignment) -> TextRenderer &{ this->alignment = alignment; return *this; }
        auto Color(class Color color) -> TextRenderer &{ this->color = color; return *this; }
        
        auto Render(Ref<class RenderTarget> target) -> void;
    private:
        Ref<class Font> font;
        String text;
        Vector2 position, scale;
        FontAlign alignment;
        class Color color;
    };
}