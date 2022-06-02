/*!
 * @file TrueTypeFont.h
 * @namespace SDG
 * @class Font
 * Represents a True Type Font (.ttf) for use by other text rendering functions.
 * If other font types become supported, this class will eventually inherit
 * from a base abstract Font class.
 *
 */
#pragma once
#include "Color.h"
#include "Texture.h"

#include <SDG/FileSys/Path.h>
#include <SDG/Lib/Ref.h>
#include <SDG/Lib/String.h>

#include <cstdint>

// forward declaration
typedef struct _TTF_Font TTF_Font;

namespace SDG
{
    /// A font class that currently supports loading and rendering .ttf fonts
    /// via SDL2_ttf backend.
    class TrueTypeFont
    {
        class Impl;
    public:
        TrueTypeFont();
        ~TrueTypeFont();

        /// Loads a ttf font
        /// @param filepath path to the ttf font file, including .ttf extension
        /// @param ptSize the point size to set
        /// @return true: TTF Font loaded successfully
        /// @return false: TTF Font failed to load, check error stream for message.
        bool Load(const Path &filepath, int pointSize);

        /// Renders solid text to a Texture
        /// @param text - the text to draw
        /// @param color - the color to draw the text with
        /// @param wrapped - whether the text should wrap around a specified length
        /// @param wrapLength - length to wrap text in pixels, only applicable if "wrapped" is true.
        /// @return new Texture pointer. It becomes the user's responsibility, so please make sure to free it
        /// when it is no longer needed.
         [[nodiscard]]
         Texture *CreateTextSolid(Ref<class Window> target, const String &text, Color color = Color::Black(), uint32_t wrapLength = 0) const;

        /// Renders shaded text to a Texture
        /// @param text - the text to draw
        /// @param fgColor - the color to draw the text with
        /// @param bgColor - the color to shade the text with
        /// @param wrapped - whether the text should wrap around a specified length
        /// @param wrapLength - length to wrap text in pixels, only applicable if "wrapped" is true.
        /// @return new Texture pointer. It becomes the user's responsibility, so please make sure to free it
        /// when it is no longer needed.
        [[nodiscard]]
        Texture *CreateTextShaded(Ref<class Window> target, const String &text, Color fgColor, Color bgColor, uint32_t wrapLength = 0) const;

        /// Renders Blended text to a Texture
        /// @param text - the text to draw
        /// @param color - the color to draw the text with
        /// @param wrapped - whether the text should wrap around a specified length
        /// @param wrapLength - length to wrap text in pixels, only applicable if "wrapped" is true.
        /// @return new Texture pointer. It becomes the user's responsibility, so please make sure to free it
        /// when it is no longer needed.
        [[nodiscard]]
        Texture *CreateTextBlended(Ref<class Window> target, const String &text, Color color, uint32_t wrapLength = 0) const;

        /// Unloads the font, cleaning this object for reuse.
        /// Safe to call on an unloaded Font, and automatically called during object destruction.
        void Close();

        // === Getters ===
        /// Checks whether the font was loaded.
        [[nodiscard]]
        bool IsLoaded() const;

        /// Gets the filepath this Font was loaded from.
        [[nodiscard]]
        const Path &Filepath() const;

        /// Gets a const reference to the internal TTF_Font
        [[nodiscard]]
        CRef<TTF_Font> InnerFont() const;

        /// Gets the font's point size.
        [[nodiscard]]
        int PointSize() const;

        /// Automatic evaluation returns whether there is a font loaded.
        [[nodiscard]]
        operator bool();

    private:
        Impl *impl;
    };
}
