/*
 * Font.h
 * SDG_Engine
 *
 * Represents a Font for use by other text rendering functions
 *
 */
#pragma once
#include <SDG/Ref.h>
#include <string>
#include "Texture2D.h"
#include "Color.h"
#include <cstdint>

typedef struct _TTF_Font TTF_Font;

namespace SDG
{
    class Font
    {
        class Impl;
    public:
        Font();
        ~Font();
        // === Getters ===

        [[nodiscard]]
        bool IsLoaded() const;

        /// Gets the filepath this Font was loaded from.
        [[nodiscard]]
        std::string Filepath() const;

        /// Gets a const reference to the internal TTF_Font
        [[nodiscard]]
        CRef<TTF_Font> InnerFont() const;

        [[nodiscard]]
        int PointSize() const;

        /*!
         * Loads a ttf font
         * @param filepath path to the ttf font file, including .ttf extension
         * @param ptSize the point size to set
         * @return true: TTF Font loaded successfully
         * @return false: TTF Font failed to load, check error stream for message.
         */
        bool Load(const std::string &filepath, int pointSize);

         /*!
          * Renders solid text to a Texture2D
          * @param text - the text to draw
          * @param color - the color to draw the text with
          * @param wrapped - whether the text should wrap around a specified length
          * @param wrapLength - length to wrap text in pixels, only applicable if "wrapped" is true.
          * @return new Texture2D pointer. It becomes the user's responsibility, so please make sure to free it
          * when it is no longer needed.
          */
         [[nodiscard]]
         Texture2D *RenderTextSolid(const std::string &text, Color color = Color::Black(), bool wrapped = false, uint32_t wrapLength = 0) const;

        /*!
         * Renders shaded text to a Texture2D
         * @param text - the text to draw
         * @param fgColor - the color to draw the text with
         * @param bgColor - the color to shade the text with
         * @param wrapped - whether the text should wrap around a specified length
         * @param wrapLength - length to wrap text in pixels, only applicable if "wrapped" is true.
         * @return new Texture2D pointer. It becomes the user's responsibility, so please make sure to free it
         * when it is no longer needed.
         */
        [[nodiscard]]
        Texture2D *RenderTextShaded(const std::string &text, Color fgColor, Color bgColor, bool wrapped = false, uint32_t wrapLength = 0) const;

        /*!
         * Renders Blended text to a Texture2D
         * @param text - the text to draw
         * @param color - the color to draw the text with
         * @param wrapped - whether the text should wrap around a specified length
         * @param wrapLength - length to wrap text in pixels, only applicable if "wrapped" is true.
         * @return new Texture2D pointer. It becomes the user's responsibility, so please make sure to free it
         * when it is no longer needed.
         */
        [[nodiscard]]
        Texture2D *RenderTextBlended(const std::string &text, Color color, bool wrapped = false, uint32_t wrapLength = 0) const;

        /*!
         * Unloads the font, cleaning this object for reuse.
         * Safe to call on an unloaded Font, and automatically called during object destruction.
         */
        void Close();

        /*!
         * Bool evaluation returns whether there is a font loaded.
         */
        [[nodiscard]]
        operator bool();

    private:
        Impl *impl;
    };
}
