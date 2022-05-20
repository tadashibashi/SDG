/**
 * @file Color.h
 * @namespace SDG
 * @class Color
 * Color is a struct that contains the values R, G, B, A
 * Each value goes from 0 (no intensity) to COLOR_MAX (Max intensity)
 * This class is passed into Renderer functions to tint a sprite,
 * paint the screen or color a rectangle
 * 
 * Pre-made colors are from: quackit.com/css/css_color_codes.cfm
 * and https://colorcodes.io
 * 
 */
#pragma once
#include <cstdint>

namespace SDG
{
    class Color
    {
    private:
        uint8_t r, g, b, a;
    public:
        static const uint8_t COLOR_MAX = UINT8_MAX;
        Color &Set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = COLOR_MAX);

        [[nodiscard]] uint8_t R() const { return r; }
        [[nodiscard]] uint8_t G() const { return g; }
        [[nodiscard]] uint8_t B() const { return b; }
        [[nodiscard]] uint8_t A() const { return a; }

        Color &R(uint8_t red) { r = red; return *this; }
        Color &G(uint8_t green) { g = green; return *this; }
        Color &B(uint8_t blue) { b = blue; return *this; }
        Color &A(uint8_t alpha) { a = alpha; return *this; }

        // Defaults to White
        constexpr Color() : r(COLOR_MAX), g(COLOR_MAX), b(COLOR_MAX), a(COLOR_MAX) {}
        constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = COLOR_MAX)
            : r(r), g(g), b(b), a(a) {}
        // Makes a grayscale color
        explicit constexpr Color(uint8_t grayScale, uint8_t alpha = COLOR_MAX)
            : r(grayScale), g(grayScale), b(grayScale), a(alpha) {}
        
        // Pre-made Colors with modifiable alpha value
        // ===== REDS ===========
        [[maybe_unused]] static Color Amaranth(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BloodRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BrightRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BrickRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Cerise(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CherryRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color ChristmasRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color ComicBookRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Cranberry(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color EarthyRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color FireTruckRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Heliconia(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightsaberRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Mango(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumDarkRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color NeonRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color OxbloodRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PastelRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RacingRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RedOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RhodamineRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RichRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RoseRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Rosso(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RubyRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RusticRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color ScarletRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Strawberry(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color VarsityRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Watermelon(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color WineRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color IndianRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightCoral(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Salmon(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkSalmon(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightSalmon(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Crimson(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Red(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color FireBrick(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkRed(uint8_t alpha = COLOR_MAX);

        // TODO: Pinks from https://colorcodes.io/pink/
        // ===== PINKS =========;
        [[maybe_unused]] static Color Pink(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightPink(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color HotPink(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DeepPink(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumVioletRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PaleVioletRed(uint8_t alpha = COLOR_MAX);

        // ===== ORANGES =========;
        [[maybe_unused]] static Color Amber(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Apricot(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BrightOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BurntOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color ConstructionOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color GoldfishOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color HalloweenOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color HunterBlazeOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MonarchOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color NeonOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PastelOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Peach(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PumpkinSpiceOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RoadSignOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Sunset(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Tangerine(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color TigerOrange(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Tumeric(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Vermillion(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Coral(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Tomato(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color OrangeRed(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Orange(uint8_t alpha = COLOR_MAX);

        // TODO: Yellows from https://colorcodes.io/yellow/
        // ===== YELLOWS =========;
        [[maybe_unused]] static Color Gold(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Yellow(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightYellow(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LemonChiffon(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightGoldenrodYellow(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PapayaWhip(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Moccasin(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PeachPuff(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PaleGoldenrod(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkKhaki(uint8_t alpha = COLOR_MAX);

        // ===== GOLDS ==========
        [[maybe_unused]] static Color HarvestGold(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PaleGold(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SatinSheenGold(uint8_t alpha = COLOR_MAX);

        // TODO: Purplse from https://colorcodes.io/purple/
        // ===== PURPLES =========;
        [[maybe_unused]] static Color Lavender(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Thistle(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Plum(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Violet(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Orchid(uint8_t alpha = COLOR_MAX);
        // this color is off
        [[maybe_unused]] static Color Fuchsia(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Magenta(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumOrchid(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumPurple(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BlueViolet(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkViolet(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkOrchid(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkMegenta(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Purple(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RebeccaPurple(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Indigo(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumSlateBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SlateBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkSlateBlue(uint8_t alpha = COLOR_MAX);

        // TODO: Greens from https://colorcodes.io/green/
        // ===== Greens ========;
        [[maybe_unused]] static Color GreenYellow(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Chartreuse(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LawnGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Lime(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LimeGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PaleGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumSpringGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SpringGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumSeaGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SeaGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color ForestGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Green(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color YellowGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color OliveDrab(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Olive(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkOliveGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumAquamarine(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkSeaGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightSeaGreen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkCyan(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Teal(uint8_t alpha = COLOR_MAX);

        // ===== Blues / Cyans =====;
        [[maybe_unused]] static Color Aqua(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Azure(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BabyBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BlueScreenOfDeath(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BrightBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BrightNavy(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CarolinaBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CetaceanBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color ChambrayBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CloudBurstBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CobaltBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color ComicBookBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CortanaBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Cyan(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CornflowerBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DazzlingBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color ElectricBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color FrenchBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightsaberBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MalibuBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MarinesBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MintBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color KingBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PaleBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Periwinkle(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PeacockBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PowderBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PoliceBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color NavyBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DenimBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color FluorescentBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color HonoluluBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color IceBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color IndigoBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PacificBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PastelBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color OceanBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color NeonBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MidnightBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color TennisCourtBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SapphireBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RotaryBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RobinEggBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RichBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color ReflexBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RoyalBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RoadSignBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Serenity(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SkyBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SeaBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color TealBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color UmpireBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color UsNavyBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Cerulean(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightCyan(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color PaleTurquoise(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Aquamarine(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Turquoise(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumTurquoise(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkTurquoise(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CadetBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SteelBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightSteelBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightSkyBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DeepSkyBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DodgerBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Blue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MediumBlue(uint8_t alpha = COLOR_MAX);

        // TODO: Browns from https://colorcodes.io/brown/
        // ===== Browns =========;
        [[maybe_unused]] static Color Cornsilk(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BlanchedAlmond(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Bisque(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color NavajoWhite(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Wheat(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color BurlyWood(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Tan(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color RosyBrown(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SandyBrown(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Goldenrod(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkGoldenrod(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Peru(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Chocolate(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SaddleBrown(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Sienna(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Brown(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Maroon(uint8_t alpha = COLOR_MAX);

        // ===== Beiges ==========
        [[maybe_unused]] static Color Cream(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color UnbleachedSilk(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DesertSand(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Khaki(uint8_t alpha = COLOR_MAX);

        // ===== Whites =========;
        [[maybe_unused]] static Color White(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Snow(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Honeydew(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MintCream(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color AliceBlue(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color GhostWhite(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color WhiteSmoke(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Seashell(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Beige(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color OldLace(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color FloralWhite(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Ivory(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color AntiqueWhite(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Linen(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LavenderBlush(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color MistyRose(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color OffWhite(uint8_t alpha = COLOR_MAX);

        // TODO: Grays from https://colorcodes.io/gray/
        // ===== GRAYS =========
        [[maybe_unused]] static Color AshGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Chrome(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color AgreeableGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Aluminum(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Anthracite(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CoolGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color CharcoalGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Gainsboro(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Silver(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Gray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Pewter(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DimGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color LightSlateGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color SlateGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color DarkSlateGray(uint8_t alpha = COLOR_MAX);
        [[maybe_unused]] static Color Black(uint8_t alpha = COLOR_MAX);
    };
}
