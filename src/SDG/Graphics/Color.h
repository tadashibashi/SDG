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
 * and https://colorcodes.io
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
        constexpr Color()
            : r(MAX_COLOR_VALUE), g(MAX_COLOR_VALUE), b(MAX_COLOR_VALUE),
                   a(MAX_COLOR_VALUE) {}
        // Constructor for making a custom color
        constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = MAX_COLOR_VALUE)
            : r(r), g(g), b(b), a(a) {}
        // Constructor for making grayscale colors
        explicit constexpr Color(uint8_t grayScale, uint8_t alpha = MAX_COLOR_VALUE)
            : r(grayScale), g(grayScale), b(grayScale), a(alpha) {}

        void set(uint8_t r, uint8_t g, uint8_t b);
        void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        
        // Pre-made Colors with modifiable alpha value
        // ===== REDS ===========
        static Color Amaranth(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BloodRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BrightRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BrickRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Cerise(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CherryRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color ChristmasRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color ComicBookRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Cranberry(uint8_t alpha = MAX_COLOR_VALUE);
        static Color EarthyRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color FireTruckRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Heliconia(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightsaberRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Mango(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumDarkRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color NeonRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color OxbloodRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PastelRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RacingRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RedOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RhodamineRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RichRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RoseRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Rosso(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RubyRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RusticRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color ScarletRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Strawberry(uint8_t alpha = MAX_COLOR_VALUE);
        static Color VarsityRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Watermelon(uint8_t alpha = MAX_COLOR_VALUE);
        static Color WineRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color IndianRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightCoral(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Salmon(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkSalmon(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightSalmon(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Crimson(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Red(uint8_t alpha = MAX_COLOR_VALUE);
        static Color FireBrick(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkRed(uint8_t alpha = MAX_COLOR_VALUE);

        // TODO: Pinks from https://colorcodes.io/pink/
        // ===== PINKS =========;
        static Color Pink(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightPink(uint8_t alpha = MAX_COLOR_VALUE);
        static Color HotPink(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DeepPink(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumVioletRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PaleVioletRed(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== ORANGES =========;
        static Color Amber(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Apricot(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BrightOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BurntOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color ConstructionOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color GoldfishOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color HalloweenOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color HunterBlazeOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MonarchOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color NeonOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PastelOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Peach(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PumpkinSpiceOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RoadSignOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Sunset(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Tangerine(uint8_t alpha = MAX_COLOR_VALUE);
        static Color TigerOrange(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Tumeric(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Vermillion(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Coral(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Tomato(uint8_t alpha = MAX_COLOR_VALUE);
        static Color OrangeRed(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Orange(uint8_t alpha = MAX_COLOR_VALUE);

        // TODO: Yellows from https://colorcodes.io/yellow/
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
        static Color DarkKhaki(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== GOLDS ==========
        static Color HarvestGold(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PaleGold(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SatinSheenGold(uint8_t alpha = MAX_COLOR_VALUE);

        // TODO: Purplse from https://colorcodes.io/purple/
        // ===== PURPLES =========;
        static Color Lavender(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Thistle(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Plum(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Violet(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Orchid(uint8_t alpha = MAX_COLOR_VALUE);
        // this color is off
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

        // TODO: Greens from https://colorcodes.io/green/
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
        static Color Azure(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BabyBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BlueScreenOfDeath(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BrightBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color BrightNavy(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CarolinaBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CetaceanBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color ChambrayBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CloudBurstBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CobaltBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color ComicBookBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CortanaBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Cyan(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CornflowerBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DazzlingBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color ElectricBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color FrenchBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightsaberBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MalibuBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MarinesBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MintBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color KingBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PaleBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Periwinkle(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PeacockBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PowderBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PoliceBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color NavyBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DenimBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color FluorescentBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color HonoluluBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color IceBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color IndigoBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PacificBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PastelBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color OceanBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color NeonBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MidnightBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color TennisCourtBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SapphireBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RotaryBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RobinEggBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RichBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color ReflexBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RoyalBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color RoadSignBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Serenity(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SkyBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SeaBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color TealBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color UmpireBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color UsNavyBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Cerulean(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightCyan(uint8_t alpha = MAX_COLOR_VALUE);
        static Color PaleTurquoise(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Aquamarine(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Turquoise(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumTurquoise(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkTurquoise(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CadetBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SteelBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightSteelBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightSkyBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DeepSkyBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DodgerBlue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Blue(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MediumBlue(uint8_t alpha = MAX_COLOR_VALUE);

        // TODO: Browns from https://colorcodes.io/brown/
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

        // ===== Beiges ==========
        static Color Cream(uint8_t alpha = MAX_COLOR_VALUE);
        static Color UnbleachedSilk(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DesertSand(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Khaki(uint8_t alpha = MAX_COLOR_VALUE);

        // ===== Whites =========;
        static Color White(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Snow(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Honeydew(uint8_t alpha = MAX_COLOR_VALUE);
        static Color MintCream(uint8_t alpha = MAX_COLOR_VALUE);
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
        static Color OffWhite(uint8_t alpha = MAX_COLOR_VALUE);

        // TODO: Grays from https://colorcodes.io/gray/
        // ===== GRAYS =========
        static Color AshGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Chrome(uint8_t alpha = MAX_COLOR_VALUE);
        static Color AgreeableGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Aluminum(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Anthracite(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CoolGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color CharcoalGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Gainsboro(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Silver(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Gray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Pewter(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DimGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color LightSlateGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color SlateGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color DarkSlateGray(uint8_t alpha = MAX_COLOR_VALUE);
        static Color Black(uint8_t alpha = MAX_COLOR_VALUE);
    };
}
