/**
 * Color.h
 * Author: Aaron Ishibashi
 * 
 * Color is a struct that contains the values r, g, b, a
 * Each value goes from 0 (no intensity) to MAX_COLOR_VALUE (Max intensity)
 * This struct is passed into Renderer functions to tint a sprite,
 * paint the screen or color a rectangle
 * 
 * Pre-made colors are from: quackit.com/css/css_color_codes.cfm
 * 
 */
#pragma once
#include <cstdint>

const uint8_t MAX_COLOR_VALUE = UINT8_MAX;

namespace SDG
{
    struct Color
    {
    public:
        uint8_t r, g, b, a;
        
        // Defaults to White
        Color();
        // Constructor for making a custom color
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = MAX_COLOR_VALUE);
        // Constructor for making grayscale colors
        explicit Color(uint8_t grayScale, uint8_t alpha = MAX_COLOR_VALUE);

        void set(uint8_t r, uint8_t g, uint8_t b);
        void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        
        // Pre-made Colors
        // ===== REDS ===========
        static Color IndianRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightCoral(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Salmon(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkSalmon(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightSalmon(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Crimson(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Red(uint8_t alpha = MAX_COLOR_VALUE);
        static Color FireBrick(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkRed(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== PINKS =========;
        static Color Pink(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightPink(uint8_t alpha = MAX_COLOR_VALUE);
        static Color HotPink(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DeepPink(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumVioletRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PaleVioletRed(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== ORANGES =========;
        static Color Coral(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Tomato(uint8_t alpha = MAX_COLOR_VALUE);
        static Color OrangeRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Orange(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== YELLOWS =========;
        static Color Gold(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Yellow(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightYellow(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LemonChiffon(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightGoldenrodYellow(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PapayaWhip(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Moccasin(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PeachPuff(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PaleGoldenrod(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Khaki(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkKhaki(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== PURPLES =========;
        static Color Lavender(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Thistle(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Plum(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Violet(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Orchid(uint8_t alpha = MAX_COLOR_VALUE);
        // this color is o;
        static Color Fuchsia(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Magenta(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumOrchid(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumPurple(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BlueViolet(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkViolet(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkOrchid(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkMegenta(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Purple(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RebeccaPurple(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Indigo(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumSlateBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SlateBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkSlateBlue(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== Greens ========;
        static Color GreenYellow(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Chartreuse(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LawnGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Lime(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LimeGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PaleGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumSpringGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SpringGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumSeaGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SeaGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color ForestGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Green(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color YellowGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color OliveDrab(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Olive(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkOliveGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumAquamarine(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkSeaGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightSeaGreen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkCyan(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Teal(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== Blues / Cyans =====;
        static Color Aqua(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Cyan(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightCyan(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PaleTurquoise(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Aquamarine(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Turquoise(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumTurquoise(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkTurquoise(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CadetBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SteelBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightSteelBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PowderBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SkyBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightSkyBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DeepSkyBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DodgerBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CornflowerBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RoyalBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Blue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Navy(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MidnightBlue(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== Browns =========;
        static Color Cornsilk(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BlanchedAlmond(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Bisque(uint8_t alpha = MAX_COLOR_VALUE);
        static Color NavajoWhite(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Wheat(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BurlyWood(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Tan(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RosyBrown(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SandyBrown(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Goldenrod(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkGoldenrod(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Peru(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Chocolate(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SaddleBrown(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Sienna(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Brown(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Maroon(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== Whites =========;
        static Color White(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Snow(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Honeydew(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MintCream(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Azure(uint8_t alpha = MAX_COLOR_VALUE);
        static Color AliceBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color GhostWhite(uint8_t alpha = MAX_COLOR_VALUE);
        static Color WhiteSmoke(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Seashell(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Beige(uint8_t alpha = MAX_COLOR_VALUE);
        static Color OldLace(uint8_t alpha = MAX_COLOR_VALUE);
        static Color FloralWhite(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Ivory(uint8_t alpha = MAX_COLOR_VALUE);
        static Color AntiqueWhite(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Linen(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LavenderBlush(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MistyRose(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== GRAYS =========
        static Color Gainsboro(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Silver(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Gray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DimGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightSlateGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SlateGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkSlateGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Black(uint8_t alpha = MAX_COLOR_VALUE);

    };
}
