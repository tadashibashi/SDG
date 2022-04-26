#include "Color.h"

namespace SDG
{
    Color::Color() : r(MAX_COLOR_VALUE), g(MAX_COLOR_VALUE), b(MAX_COLOR_VALUE),
        a(MAX_COLOR_VALUE) {}
        
    Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
        : r(r), g(g), b(b), a(a) {}

    Color::Color(Uint8 grayScale, Uint8 alpha)
        : r(grayScale), g(grayScale), b(grayScale), a(alpha) {}

    SDL_Color Color::ToSDL_Color() const
    {
        SDL_Color c;
        c.r = r; c.g = g; c.b = b; c.a = a;
        return c;
    }

    void Color::set(Uint8 r, Uint8 g, Uint8 b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void Color::set(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    // Pre-made Colors
    // ===== REDS ===========
    Color Color::IndianRed(Uint8 alpha) {
        return Color(205, 92, 92, alpha);
    }
    Color Color::LightCoral(Uint8 alpha) {
        return Color(240, 128, 128, alpha);
    }
    Color Color::Salmon(Uint8 alpha) {
        return Color(250, 128, 114, alpha);
    }
    Color Color::DarkSalmon(Uint8 alpha) {
        return Color(233, 150, 122, alpha);
    }
    Color Color::LightSalmon(Uint8 alpha) {
        return Color(255, 160, 122, alpha);
    }
    Color Color::Crimson(Uint8 alpha) {
        return Color(220, 20, 60, alpha);
    }
    Color Color::Red(Uint8 alpha) {
        return Color(255, 0, 0, alpha);
    }
    Color Color::FireBrick(Uint8 alpha) {
        return Color(178, 34, 34, alpha);
    }
    Color Color::DarkRed(Uint8 alpha) {
        return Color(139, 0, 0, alpha);
    }

    // ===== PINKS ===========
    Color Color::Pink(Uint8 alpha) {
        return Color(255, 192, 203, alpha);
    }
    Color Color::LightPink(Uint8 alpha) {
        return Color(255, 182, 193, alpha);
    }
    Color Color::HotPink(Uint8 alpha) {
        return Color(255, 105, 180, alpha);
    }
    Color Color::DeepPink(Uint8 alpha) {
        return Color(255, 20, 147, alpha);
    }
    Color Color::MediumVioletRed(Uint8 alpha) {
        return Color(199, 21, 133, alpha);
    }
    Color Color::PaleVioletRed(Uint8 alpha) {
        return Color(219, 112, 147, alpha);
    }

    // ===== ORANGES ===========
    Color Color::Coral(Uint8 alpha) {
        return Color(255, 127, 80, alpha);
    }
    Color Color::Tomato(Uint8 alpha) {
        return Color(255, 99, 71, alpha);
    }
    Color Color::OrangeRed(Uint8 alpha) {
        return Color(255, 69, 0, alpha);
    }
    Color Color::DarkOrange(Uint8 alpha) {
        return Color(255, 140, 0, alpha);
    }
    Color Color::Orange(Uint8 alpha) {
        return Color(255, 165, 0, alpha);
    }

    // ===== YELLOWS ===========
    Color Color::Gold(Uint8 alpha) {
        return Color(255, 215, 0, alpha);
    }
    Color Color::Yellow(Uint8 alpha) {
        return Color(255, 255, 0, alpha);
    }
    Color Color::LightYellow(Uint8 alpha) {
        return Color(255, 255, 0, alpha);
    }
    Color Color::LemonChiffon(Uint8 alpha) {
        return Color(255, 255, 224, alpha);
    }
    Color Color::LightGoldenrodYellow(Uint8 alpha) {
        return Color(250, 250, 210, alpha);
    }
    Color Color::PapayaWhip(Uint8 alpha) {
        return Color(255, 239, 213, alpha);
    }
    Color Color::Moccasin(Uint8 alpha) {
        return Color(255, 228, 181, alpha);
    }
    Color Color::PeachPuff(Uint8 alpha) {
        return Color(255, 218, 185, alpha);
    }
    Color Color::PaleGoldenrod(Uint8 alpha) {
        return Color(238, 232, 170, alpha);
    }
    Color Color::Khaki(Uint8 alpha) {
        return Color(240, 230, 140, alpha);
    }
    Color Color::DarkKhaki(Uint8 alpha) {
        return Color(189, 183, 107, alpha);
    }

    // ===== PURPLES ===========
    Color Color::Lavender(Uint8 alpha) {
        return Color(230, 230, 250, alpha);
    }
    Color Color::Thistle(Uint8 alpha) {
        return Color(216, 191, 216, alpha);
    }
    Color Color::Plum(Uint8 alpha) {
        return Color(221, 160, 221, alpha);
    }
    Color Color::Violet(Uint8 alpha) {
        return Color(238, 130, 238, alpha);
    }
    Color Color::Orchid(Uint8 alpha) {
        return Color(218, 112, 214, alpha);
    }
    // this color is off
    Color Color::Fuchsia(Uint8 alpha) {
        return Color(255, 0, 255, alpha);
    }
    Color Color::Magenta(Uint8 alpha) {
        return Color(255, 0, 255, alpha);
    }
    Color Color::MediumOrchid(Uint8 alpha) {
        return Color(186, 85, 211, alpha);
    }
    Color Color::MediumPurple(Uint8 alpha) {
        return Color(147, 112, 219, alpha);
    }
    Color Color::BlueViolet(Uint8 alpha) {
        return Color(138, 43, 226, alpha);
    }
    Color Color::DarkViolet(Uint8 alpha) {
        return Color(148, 0, 211, alpha);
    }
    Color Color::DarkOrchid(Uint8 alpha) {
        return Color(153, 50, 204, alpha);
    }
    Color Color::DarkMegenta(Uint8 alpha) {
        return Color(139, 0, 139, alpha);
    }
    Color Color::Purple(Uint8 alpha) {
        return Color(128, 0, 128, alpha);
    }
    Color Color::RebeccaPurple(Uint8 alpha) {
        return Color(102, 51, 153, alpha);
    }
    Color Color::Indigo(Uint8 alpha) {
        return Color(75, 0, 130, alpha);
    }
    Color Color::MediumSlateBlue(Uint8 alpha) {
        return Color(123, 104, 238, alpha);
    }
    Color Color::SlateBlue(Uint8 alpha) {
        return Color(106, 90, 205, alpha);
    }
    Color Color::DarkSlateBlue(Uint8 alpha) {
        return Color(72, 61, 139, alpha);
    }

    // ===== Greens ==========
    Color Color::GreenYellow(Uint8 alpha) {
        return Color(173, 255, 47, alpha);
    }
    Color Color::Chartreuse(Uint8 alpha) {
        return Color(127, 255, 0, alpha);
    }
    Color Color::LawnGreen(Uint8 alpha) {
        return Color(124, 255, 0, alpha);
    }
    Color Color::Lime(Uint8 alpha) {
        return Color(0, 255, 0, alpha);
    }
    Color Color::LimeGreen(Uint8 alpha) {
        return Color(50, 205, 50, alpha);
    }
    Color Color::PaleGreen(Uint8 alpha) {
        return Color(152, 251, 152, alpha);
    }
    Color Color::LightGreen(Uint8 alpha) {
        return Color(144, 238, 144, alpha);
    }
    Color Color::MediumSpringGreen(Uint8 alpha) {
        return Color(0, 250, 154, alpha);
    }
    Color Color::SpringGreen(Uint8 alpha) {
        return Color(0, 255, 127, alpha);
    }
    Color Color::MediumSeaGreen(Uint8 alpha) {
        return Color(60, 179, 113, alpha);
    }
    Color Color::SeaGreen(Uint8 alpha) {
        return Color(46, 139, 87, alpha);
    }
    Color Color::ForestGreen(Uint8 alpha) {
        return Color(34, 139, 34, alpha);
    }
    Color Color::Green(Uint8 alpha) {
        return Color(0, 128, 0, alpha);
    }
    Color Color::DarkGreen(Uint8 alpha) {
        return Color(0, 100, 0, alpha);
    }
    Color Color::YellowGreen(Uint8 alpha) {
        return Color(154, 205, 50, alpha);
    }
    Color Color::OliveDrab(Uint8 alpha) {
        return Color(107, 142, 35, alpha);
    }
    Color Color::Olive(Uint8 alpha) {
        return Color(128, 128, 0, alpha);
    }
    Color Color::DarkOliveGreen(Uint8 alpha) {
        return Color(85, 107, 47, alpha);
    }
    Color Color::MediumAquamarine(Uint8 alpha) {
        return Color(102, 205, 170, alpha);
    }
    Color Color::DarkSeaGreen(Uint8 alpha) {
        return Color(143, 188, 143, alpha);
    }
    Color Color::LightSeaGreen(Uint8 alpha) {
        return Color(32, 178, 170, alpha);
    }
    Color Color::DarkCyan(Uint8 alpha) {
        return Color(0, 139, 139, alpha);
    }
    Color Color::Teal(Uint8 alpha) {
        return Color(0, 128, 128, alpha);
    }
    
    // ===== Blues / Cyans =======
    Color Color::Aqua(Uint8 alpha) {
        return Color(0, 255, 255, alpha);
    }
    Color Color::Cyan(Uint8 alpha) {
        return Color(0, 255, 255, alpha);
    }
    Color Color::LightCyan(Uint8 alpha) {
        return Color(224, 255, 255, alpha);
    }
    Color Color::PaleTurquoise(Uint8 alpha) {
        return Color(175, 238, 238, alpha);
    }
    Color Color::Aquamarine(Uint8 alpha) {
        return Color(127, 255, 212, alpha);
    }
    Color Color::Turquoise(Uint8 alpha) {
        return Color(64, 224, 208, alpha);
    }
    Color Color::MediumTurquoise(Uint8 alpha) {
        return Color(72, 209, 204, alpha);
    }
    Color Color::DarkTurquoise(Uint8 alpha) {
        return Color(0, 206, 209, alpha);
    }
    Color Color::CadetBlue(Uint8 alpha) {
        return Color(95, 158, 160, alpha);
    }
    Color Color::SteelBlue(Uint8 alpha) {
        return Color(70, 130, 180, alpha);
    }
    Color Color::LightSteelBlue(Uint8 alpha) {
        return Color(176, 196, 222, alpha);
    }
    Color Color::PowderBlue(Uint8 alpha) {
        return Color(176, 224, 230, alpha);
    }
    Color Color::LightBlue(Uint8 alpha) {
        return Color(173, 216, 230, alpha);
    }
    Color Color::SkyBlue(Uint8 alpha) {
        return Color(135, 206, 235, alpha);
    }
    Color Color::LightSkyBlue(Uint8 alpha) {
        return Color(135, 206, 250, alpha);
    }
    Color Color::DeepSkyBlue(Uint8 alpha) {
        return Color(0, 191, 255, alpha);
    }
    Color Color::DodgerBlue(Uint8 alpha) {
        return Color(30, 144, 255, alpha);
    }
    Color Color::CornflowerBlue(Uint8 alpha) {
        return Color(100, 149, 237, alpha);
    }
    Color Color::RoyalBlue(Uint8 alpha) {
        return Color(65, 105, 225, alpha);
    }
    Color Color::Blue(Uint8 alpha) {
        return Color(0, 0, 255, alpha);
    }
    Color Color::MediumBlue(Uint8 alpha) {
        return Color(0, 0, 205, alpha);
    }
    Color Color::DarkBlue(Uint8 alpha) {
        return Color(0, 0, 139, alpha);
    }
    Color Color::Navy(Uint8 alpha) {
        return Color(0, 0, 128, alpha);
    }
    Color Color::MidnightBlue(Uint8 alpha) {
        return Color(25, 25, 112, alpha);
    }

    // ===== Browns ===========
    Color Color::Cornsilk(Uint8 alpha) {
        return Color(255, 248, 220, alpha);
    }
    Color Color::BlanchedAlmond(Uint8 alpha) {
        return Color(255, 234, 205, alpha);
    }
    Color Color::Bisque(Uint8 alpha) {
        return Color(255, 228, 196, alpha);
    }
    Color Color::NavajoWhite(Uint8 alpha) {
        return Color(255, 222, 173, alpha);
    }
    Color Color::Wheat(Uint8 alpha) {
        return Color(245, 222, 179, alpha);
    }
    Color Color::BurlyWood(Uint8 alpha) {
        return Color(222, 184, 135, alpha);
    }
    Color Color::Tan(Uint8 alpha) {
        return Color(210, 180, 140, alpha);
    }
    Color Color::RosyBrown(Uint8 alpha) {
        return Color(188, 143, 143, alpha);
    }
    Color Color::SandyBrown(Uint8 alpha) {
        return Color(244, 164, 96, alpha);
    }
    Color Color::Goldenrod(Uint8 alpha) {
        return Color(218, 165, 32, alpha);
    }
    Color Color::DarkGoldenrod(Uint8 alpha) {
        return Color(184, 134, 11, alpha);
    }
    Color Color::Peru(Uint8 alpha) {
        return Color(205, 133, 63, alpha);
    }
    Color Color::Chocolate(Uint8 alpha) {
        return Color(210, 105, 30, alpha);
    }
    Color Color::SaddleBrown(Uint8 alpha) {
        return Color(139, 69, 19, alpha);
    }
    Color Color::Sienna(Uint8 alpha) {
        return Color(160, 82, 45, alpha);
    }
    Color Color::Brown(Uint8 alpha) {
        return Color(165, 42, 42, alpha);
    }
    Color Color::Maroon(Uint8 alpha) {
        return Color(128, 0, 0, alpha);
    }

    // ===== Whites ===========
    Color Color::White(Uint8 alpha) {
        return Color(255, 255, 255, alpha);
    }
    Color Color::Snow(Uint8 alpha) {
        return Color(255, 250, 250, alpha);
    }
    Color Color::Honeydew(Uint8 alpha) {
        return Color(240, 255, 240, alpha);
    }
    Color Color::MintCream(Uint8 alpha) {
        return Color(245, 255, 250, alpha);
    }
    Color Color::Azure(Uint8 alpha) {
        return Color(240, 255, 255, alpha);
    }
    Color Color::AliceBlue(Uint8 alpha) {
        return Color(240, 248, 255, alpha);
    }
    Color Color::GhostWhite(Uint8 alpha) {
        return Color(248, 248, 255, alpha);
    }
    Color Color::WhiteSmoke(Uint8 alpha) {
        return Color(245, 245, 245, alpha);
    }
    Color Color::Seashell(Uint8 alpha) {
        return Color(255, 245, 238, alpha);
    }
    Color Color::Beige(Uint8 alpha) {
        return Color(245, 245, 220, alpha);
    }
    Color Color::OldLace(Uint8 alpha) {
        return Color(253, 245, 230, alpha);
    }
    Color Color::FloralWhite(Uint8 alpha) {
        return Color(255, 250, 240, alpha);
    }
    Color Color::Ivory(Uint8 alpha) {
        return Color(255, 255, 240, alpha);
    }
    Color Color::AntiqueWhite(Uint8 alpha) {
        return Color(250, 235, 215, alpha);
    }
    Color Color::Linen(Uint8 alpha) {
        return Color(250, 240, 230, alpha);
    }
    Color Color::LavenderBlush(Uint8 alpha) {
        return Color(255, 240, 245, alpha);
    }
    Color Color::MistyRose(Uint8 alpha) {
        return Color(255, 228, 225, alpha);
    }

    // ===== GRAYS ===========
    Color Color::Gainsboro(Uint8 alpha) {
        return Color(220, alpha);
    }
    Color Color::LightGray(Uint8 alpha) {
        return Color(211, alpha);
    }
    Color Color::Silver(Uint8 alpha) {
        return Color(192, alpha);
    }
    Color Color::DarkGray(Uint8 alpha) {
        return Color(169, alpha);
    }
    Color Color::Gray(Uint8 alpha) {
        return Color(128, alpha);
    }
    Color Color::DimGray(Uint8 alpha) {
        return Color(105, alpha);
    }
    Color Color::LightSlateGray(Uint8 alpha) {
        return Color(119, 136, 153, alpha);
    }
    Color Color::SlateGray(Uint8 alpha) {
        return Color(112, 128, 144, alpha);
    }
    Color Color::DarkSlateGray(Uint8 alpha) {
        return Color(47, 79, 79, alpha);
    }
    Color Color::Black(Uint8 alpha) {
        return Color(0, 0, 0, alpha);
    }
}
