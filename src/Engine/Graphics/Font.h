/*
Some helpful definitions from StackOverflow:
https://stackoverflow.com/questions/27631736/meaning-of-top-ascent-baseline-descent-bottom-and-leading-in-androids-font

Top - The maximum distance above the baseline for the tallest glyph in the font at a given text size.
Ascent - The recommended distance above the baseline for singled spaced text.
Descent - The recommended distance below the baseline for singled spaced text.
Bottom - The maximum distance below the baseline for the lowest glyph in the font at a given text size.
Leading - The recommended additional space to add between lines of text.

Note that the Baseline is what the first four are measured from. It is line which forms the base that the
text sits on, even though some characters (like g, y, j, etc.) might have parts that go below the line.
It is comparable to the lines you write on in a lined notebook.
*/
#pragma once
#include <Engine/Lib/Unique.h>
#include <Engine/Filesys/Path.h>
#include <Engine/Graphics/Color.h>
#include <Engine/Lib/Enum.h>

#include <Engine/Math/Rectangle.h>
#include <Engine/Math/Vector2.h>

#include <Engine/Lib/Private/Fmt.h>

#include <cstdint>
#include <utility>

namespace SDG
{

    EnumFlag (FontStyle, int,
        Normal = 0x00,
        Bold = 0x01,
        Italic = 0x02,
        Underline = 0x04,
        Strikethrough = 0x08
    );

    enum class FontAlign
    {
        Left,
        Center,
        Right
    };
    

    enum class FontFilter
    {
        Linear,
        Nearest
    };

    
    class Font
    {
        struct Impl;
    public:
        Font();
        Font(class Window *context, const Path &filepath, uint32_t pointSize, 
            FontStyle style = FontStyle::Normal);
        ~Font();

    public:
        // ========== Loading =================================================

        bool Load(class Window *context, const Path &filepath, 
            uint32_t pointSize, FontStyle style);
        bool IsLoaded() const;
        void Close();

        // ========== Drawing =================================================
        template <typename...Args>
        void Draw(class RenderTarget *target, Vector2 position, Vector2 scale,
            FontAlign alignment, Color color, const char *format, Args &&...args)
        {
            auto out = std::string();
            auto str = fmt::vformat_to(std::back_inserter(out), std::string_view(format), fmt::make_format_args(args...));
            DrawImpl(target, position, scale, alignment, color, out.c_str());
        }

        // ========== Settings ================================================

        /// Get the horizontal pixel spacing between letters
        int Spacing() const;

        /// Set the horizontal pixel spacing between letters
        Font &Spacing(int spacing);

        /// Get the line spacing (in pixels)
        int LineSpacing() const;

        /// Set the line spacing (in pixels)
        Font &LineSpacing(int spacing);

        int MaxWidth() const;

        Font &Baseline(uint16_t baseline);

        uint16_t Baseline() const;

        Font &FilterMode(FontFilter mode);

        FontFilter FilterMode() const;

        uint16_t Ascent() const;
        uint16_t Ascent(const char *formatted, ...);
        uint16_t Ascent(char c);
        int Descent() const;
        int Descent(const char *formatted, ...);
        int Descent(char c);

        template <typename...Args>
        FRectangle CheckBounds(Vector2 position, const char *format, Args &&...args) const
        {
            auto str = fmt::format(format, std::forward<Args>(args)...);
            CheckBoundsImpl(position, str.c_str());
        }

        template <typename...Args>
        uint16_t CheckColumnHeight(uint16_t width, const char *format, Args &&...args) const
        {
            auto str = fmt::format(format, std::forward<Args>(args)...);
            CheckColumnHeightImpl(width, str.c_str());
        }

    private:
        void DrawImpl(RenderTarget *target, Vector2 position, Vector2 scale,
            FontAlign alignment, Color color, const char *text);
        uint16_t CheckColumnHeightImpl(uint16_t width, const char *text) const;
        FRectangle CheckBoundsImpl(Vector2 position, const char *text) const;
        Impl *impl;
    };
}
