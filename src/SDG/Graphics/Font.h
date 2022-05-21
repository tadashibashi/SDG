/*!
 * @file Font.h
 * @namespace SDG
 * @class Font
 * Represents a Font for use by other text rendering functions.
 * Currently supports TTF format.
 */
#pragma once
#include "Texture2D.h"
#include "Color.h"

#include <SDG/FileSys/Path.h>
#include <SDG/Ref.h>
#include <SDG/String.h>

#include <cstdint>

// forward declaration
typedef struct _TTF_Font TTF_Font;

namespace SDG
{
    /// A font class that currently supports loading and rendering .ttf fonts
    /// via SDL2_ttf backend.
    class Font
    {
        class Impl;
    public:
        Font();
        ~Font();


        /// Loads a ttf font
        /// @param filepath path to the ttf font file, including .ttf extension
        /// @param ptSize the point size to set
        /// @return true: TTF Font loaded successfully
        /// @return false: TTF Font failed to load, check error stream for message.
        bool Load(const Path &filepath, int pointSize);

        /// Renders solid text to a Texture2D
        /// @param text - the text to draw
        /// @param color - the color to draw the text with
        /// @param wrapped - whether the text should wrap around a specified length
        /// @param wrapLength - length to wrap text in pixels, only applicable if "wrapped" is true.
        /// @return new Texture2D pointer. It becomes the user's responsibility, so please make sure to free it
        /// when it is no longer needed.
         [[nodiscard]]
         Texture2D *CreateTextSolid(Ref<class Window> target, const String &text, Color color = Color::Black(), bool wrapped = false, uint32_t wrapLength = 0) const;

        /// Renders shaded text to a Texture2D
        /// @param text - the text to draw
        /// @param fgColor - the color to draw the text with
        /// @param bgColor - the color to shade the text with
        /// @param wrapped - whether the text should wrap around a specified length
        /// @param wrapLength - length to wrap text in pixels, only applicable if "wrapped" is true.
        /// @return new Texture2D pointer. It becomes the user's responsibility, so please make sure to free it
        /// when it is no longer needed.
        [[nodiscard]]
        Texture2D *CreateTextShaded(Ref<class Window> target, const String &text, Color fgColor, Color bgColor, bool wrapped = false, uint32_t wrapLength = 0) const;

        /// Renders Blended text to a Texture2D
        /// @param text - the text to draw
        /// @param color - the color to draw the text with
        /// @param wrapped - whether the text should wrap around a specified length
        /// @param wrapLength - length to wrap text in pixels, only applicable if "wrapped" is true.
        /// @return new Texture2D pointer. It becomes the user's responsibility, so please make sure to free it
        /// when it is no longer needed.
        [[nodiscard]]
        Texture2D *CreateTextBlended(Ref<class Window> target, const String &text, Color color, bool wrapped = false, uint32_t wrapLength = 0) const;

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
