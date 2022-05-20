/// Color implementation file
#include "Color.h"
#include <SDL.h>

namespace SDG
{
    Color &
    Color::Set(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
    {
        this->r = red;
        this->g = green;
        this->b = blue;
        this->a = alpha;

        return *this;
    }

    // Pre-made Colors
    // ===== REDS ===========
    Color Color::Amaranth(Uint8 alpha) {
        return Color(244, 54, 76, alpha);
    }
    Color Color::BloodRed(Uint8 alpha) {
        return Color(101, 28, 50, alpha);
    }
    Color Color::BrightRed(Uint8 alpha) {
        return Color(101, 28, 50, alpha);
    }
    Color Color::BrickRed(Uint8 alpha) {
        return Color(203, 65, 84, alpha);
    }
    Color Color::Cerise(Uint8 alpha) {
        return Color(223, 70, 97, alpha);
    }
    Color Color::CherryRed(Uint8 alpha) {
        return Color(205, 0, 26, alpha);
    }
    Color Color::ChristmasRed(Uint8 alpha) {
        return Color(214, 0, 28, alpha);
    }
    Color Color::ComicBookRed(uint8_t alpha) {
        return Color(237, 29, 36, alpha);
    }
    Color Color::Cranberry(Uint8 alpha) {
        return Color(166, 10, 61, alpha);
    }
    Color Color::EarthyRed(Uint8 alpha) {
        return Color(153, 71, 88, alpha);
    }
    Color Color::FireTruckRed(Uint8 alpha) {
        return Color(206, 32, 41, alpha);
    }
    Color Color::Heliconia(Uint8 alpha) {
        return Color(219, 62, 121, alpha);
    }
    Color Color::LightRed(Uint8 alpha) {
        return Color(255, 114, 118, alpha);
    }
    Color Color::LightsaberRed(uint8_t alpha) {
        return Color(235, 33, 46, alpha);
    }
    Color Color::Mango(Uint8 alpha) {
        return Color(183, 94, 74, alpha);
    }
    Color Color::MediumDarkRed(Uint8 alpha) {
        return Color(128, 5, 0, alpha);
    }
    Color Color::NeonRed(Uint8 alpha) {
        return Color(210, 39, 48, alpha);
    }
    Color Color::OxbloodRed(Uint8 alpha) {
        return Color(112, 57, 63, alpha);
    }
    Color Color::PastelRed(Uint8 alpha) {
        return Color(255, 109, 106, alpha);
    }
    Color Color::RacingRed(Uint8 alpha) {
        return Color(189, 22, 44, alpha);
    }
    Color Color::RedOrange(Uint8 alpha) {
        return Color(252, 76, 2, alpha);
    }
    Color Color::RhodamineRed(Uint8 alpha) {
        return Color(225, 0, 152, alpha);
    }
    Color Color::RichRed(Uint8 alpha) {
        return Color(161, 0, 14, alpha);
    }
    Color Color::RoseRed(Uint8 alpha) {
        return Color(255, 3, 62, alpha);
    }
    Color Color::Rosso(Uint8 alpha) {
        return Color(225, 6, 0, alpha);
    }
    Color Color::RubyRed(Uint8 alpha) {
        return Color(228, 0, 70, alpha);
    }
    Color Color::RusticRed(Uint8 alpha) {
        return Color(84, 11, 12, alpha);
    }
    Color Color::ScarletRed(Uint8 alpha) {
        return Color(187, 0, 0, alpha);
    }
    Color Color::Strawberry(Uint8 alpha) {
        return Color(197, 70, 68, alpha);
    }
    Color Color::VarsityRed(Uint8 alpha) {
        return Color(206, 17, 65, alpha);
    }
    Color Color::Watermelon(Uint8 alpha) {
        return Color(198, 58, 79, alpha);
    }
    Color Color::WineRed(Uint8 alpha) {
        return Color(155, 34, 66, alpha);
    }
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
    Color Color::Amber(Uint8 alpha) {
        return Color(255, 198, 0, alpha);
    }
    Color Color::Apricot(Uint8 alpha) {
        return Color(255, 182, 115, alpha);
    }
    Color Color::BrightOrange(Uint8 alpha) {
        return Color(255, 168, 0, alpha);
    }
    Color Color::BurntOrange(Uint8 alpha) {
        return Color(203, 96, 21, alpha);
    }
    Color Color::ConstructionOrange(uint8_t alpha) {
        return Color(254, 80, 0, alpha);
    }
    Color Color::DarkOrange(Uint8 alpha) {
        return Color(220, 88, 42, alpha);
    }
    Color Color::GoldfishOrange(Uint8 alpha) {
        return Color(255, 153, 19, alpha);
    }
    Color Color::HalloweenOrange(Uint8 alpha) {
        return Color(252, 76, 2, alpha);
    }
    Color Color::HunterBlazeOrange(Uint8 alpha) {
        return Color(255, 130, 0, alpha);
    }
    Color Color::LightOrange(Uint8 alpha) {
        return Color(252, 210, 153, alpha);
    }
    Color Color::MonarchOrange(Uint8 alpha) {
        return Color(226, 82, 42, alpha);
    }
    Color Color::NeonOrange(Uint8 alpha) {
        return Color(255, 173, 0, alpha);
    }
    Color Color::PastelOrange(Uint8 alpha) {
        return Color(239, 190, 125, alpha);
    }
    Color Color::Peach(Uint8 alpha) {
        return Color(255, 203, 164, alpha);
    }
    Color Color::PumpkinSpiceOrange(Uint8 alpha) {
        return Color(215, 107, 0, alpha);
    }
    Color Color::RoadSignOrange(Uint8 alpha) {
        return Color(252, 143, 50, alpha);
    }
    Color Color::Sunset(Uint8 alpha) {
        return Color(250, 198, 104, alpha);
    }
    Color Color::TigerOrange(Uint8 alpha) {
        return Color(249, 101, 21, alpha);
    }
    Color Color::Tangerine(Uint8 alpha) {
        return Color(237, 139, 0, alpha);
    }
    Color Color::Tumeric(Uint8 alpha) {
        return Color(255, 133, 15, alpha);
    }
    Color Color::Vermillion(Uint8 alpha) {
        return Color(221, 50, 36, alpha);
    }
    Color Color::Coral(Uint8 alpha) {
        return Color(255, 127, 80, alpha);
    }
    Color Color::Tomato(Uint8 alpha) {
        return Color(255, 99, 71, alpha);
    }
    Color Color::OrangeRed(Uint8 alpha) {
        return Color(255, 69, 0, alpha);
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
    Color Color::DarkKhaki(Uint8 alpha) {
        return Color(189, 183, 107, alpha);
    }

    // ===== GOLDS =============
    Color Color::HarvestGold(uint8_t alpha) {
        return Color(218, 145, 0, alpha);
    }
    Color Color::PaleGold(Uint8 alpha) {
        return Color(230, 190, 138, alpha);
    }
    Color Color::SatinSheenGold(Uint8 alpha) {
        return Color(203, 161, 53, alpha);
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
    [[maybe_unused]] Color Color::GreenYellow(Uint8 alpha) {
        return Color(173, 255, 47, alpha);
    }

    [[maybe_unused]] Color Color::Chartreuse(Uint8 alpha) {
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
        return Color(5, 195, 221, alpha);
    }
    Color Color::Azure(Uint8 alpha) {
        return Color(0, 138, 216, alpha);
    }
    Color Color::BabyBlue(Uint8 alpha) {
        return Color(155, 211, 221, alpha);
    }
    Color Color::BlueScreenOfDeath(Uint8 alpha) {
        return Color(8, 39, 245, alpha);
    }
    Color Color::BrightBlue(Uint8 alpha) {
        return Color(0, 78, 255, alpha);
    }
    Color Color::BrightNavy(Uint8 alpha) {
        return Color(75, 104, 184, alpha);
    }
    Color Color::CarolinaBlue(Uint8 alpha) {
        return Color(153, 186, 221, alpha);
    }
    Color Color::CetaceanBlue(Uint8 alpha) {
        return Color(0, 20, 75, alpha);
    }
    Color Color::ChambrayBlue(Uint8 alpha) {
        return Color(60, 82, 145, alpha);
    }
    Color Color::CloudBurstBlue(Uint8 alpha) {
        return Color(33, 46, 82, alpha);
    }
    Color Color::CobaltBlue(Uint8 alpha) {
        return Color(0, 80, 181, alpha);
    }
    Color Color::ComicBookBlue(Uint8 alpha) {
        return Color(0, 174, 239, alpha);
    }
    Color Color::CortanaBlue(Uint8 alpha) {
        return Color(0, 163, 225, alpha);
    }
    Color Color::Cyan(Uint8 alpha) {
        return Color(0, 188, 227, alpha);
    }
    Color Color::CornflowerBlue(Uint8 alpha) {
        return Color(130, 163, 255, alpha);
    }
    Color Color::DarkBlue(Uint8 alpha) {
        return Color(3, 37, 126, alpha);
    }
    Color Color::DazzlingBlue(Uint8 alpha) {
        return Color(46, 77, 167, alpha);
    }
    Color Color::ElectricBlue(Uint8 alpha) {
        return Color(89, 203, 232, alpha);
    }
    Color Color::FrenchBlue(Uint8 alpha) {
        return Color(0, 110, 179, alpha);
    }
    Color Color::LightsaberBlue(Uint8 alpha) {
        return Color(46, 103, 248, alpha);
    }
    Color Color::MalibuBlue(Uint8 alpha) {
        return Color(91, 126, 222, alpha);
    }
    Color Color::MarinesBlue(Uint8 alpha) {
        return Color(0, 68, 129, alpha);
    }
    Color Color::MintBlue(Uint8 alpha) {
        return Color(66, 158, 157, alpha);
    }
    Color Color::KingBlue(Uint8 alpha) {
        return Color(65, 105, 225, alpha);
    }
    Color Color::PaleBlue(Uint8 alpha) {
        return Color(175, 238, 238, alpha);
    }
    Color Color::PeacockBlue(Uint8 alpha) {
        return Color(0, 164, 180, alpha);
    }
    Color Color::PowderBlue(Uint8 alpha) {
        return Color(176, 224, 230, alpha);
    }
    Color Color::PoliceBlue(Uint8 alpha) {
        return Color(19, 93, 216, alpha);
    }
    Color Color::LightBlue(Uint8 alpha) {
        return Color(164, 219, 232, alpha);
    }
    Color Color::NavyBlue(Uint8 alpha) {
        return Color(32, 42, 68, alpha);
    }
    Color Color::DenimBlue(Uint8 alpha) {
        return Color(21, 96, 189, alpha);
    }
    Color Color::FluorescentBlue(Uint8 alpha) {
        return Color(172, 55, 238, alpha);
    }
    Color Color::HonoluluBlue(Uint8 alpha) {
        return Color(0, 118, 182, alpha);
    }
    Color Color::IceBlue(Uint8 alpha) {
        return Color(200, 233, 233, alpha);
    }
    Color Color::IndigoBlue(Uint8 alpha) {
        return Color(75, 0, 130, alpha);
    }
    Color Color::PacificBlue(Uint8 alpha) {
        return Color(5,  169, 199, alpha);
    }
    Color Color::PastelBlue(Uint8 alpha) {
        return Color(139, 211, 230, alpha);
    }
    Color Color::OceanBlue(Uint8 alpha) {
        return Color(0, 94, 184, alpha);
    }
    Color Color::Periwinkle(Uint8 alpha) {
        return Color(124, 131, 188, alpha);
    }
    Color Color::NeonBlue(Uint8 alpha) {
        return Color(77, 77, 255, alpha);
    }
    Color Color::MidnightBlue(Uint8 alpha) {
        return Color(100, 71, 0, alpha);
    }
    Color Color::TennisCourtBlue(Uint8 alpha) {
        return Color(30, 143, 213, alpha);
    }
    Color Color::SapphireBlue(Uint8 alpha) {
        return Color(15, 82, 186, alpha);
    }
    Color Color::RotaryBlue(Uint8 alpha) {
        return Color(0, 51, 153, alpha);
    }
    Color Color::RobinEggBlue(Uint8 alpha) {
        return Color(31, 206, 203, alpha);
    }
    Color Color::RichBlue(Uint8 alpha) {
        return Color(8, 146, 208, alpha);
    }
    Color Color::ReflexBlue(Uint8 alpha) {
        return Color(51, 51, 153, alpha);
    }
    Color Color::RoyalBlue(Uint8 alpha) {
        return Color(85, 118, 209, alpha);
    }
    Color Color::RoadSignBlue(uint8_t alpha) {
        return Color(15, 57, 139, alpha);
    }
    Color Color::SkyBlue(Uint8 alpha) {
        return Color(0, 181, 226, alpha);
    }
    Color Color::SeaBlue(Uint8 alpha) {
        return Color(0, 105, 148, alpha);
    }
    Color Color::Serenity(Uint8 alpha) {
        return Color(177, 201, 232, alpha);
    }
    Color Color::TealBlue(Uint8 alpha) {
        return Color(0, 124, 128, alpha);
    }
    Color Color::UmpireBlue(Uint8 alpha) {
        return Color(123, 178, 221, alpha);
    }
    Color Color::UsNavyBlue(Uint8 alpha) {
        return Color(0, 47, 108, alpha);
    }




    Color Color::Cerulean(uint8_t alpha) {
        return Color(0, 143, 190, alpha);
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
    Color Color::LightSkyBlue(Uint8 alpha) {
        return Color(135, 206, 250, alpha);
    }
    Color Color::DeepSkyBlue(Uint8 alpha) {
        return Color(0, 191, 255, alpha);
    }
    Color Color::DodgerBlue(Uint8 alpha) {
        return Color(30, 144, 255, alpha);
    }
    Color Color::Blue(Uint8 alpha) {
        return Color(0, 0, 255, alpha);
    }
    Color Color::MediumBlue(Uint8 alpha) {
        return Color(0, 0, 205, alpha);
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

    // == Beiges ===========================
    Color Color::Cream(Uint8 alpha) {
        return Color(240, 235, 210, alpha);
    }
    Color Color::UnbleachedSilk(Uint8 alpha) {
        return Color(229, 158, 109, alpha);
    }
    Color Color::DesertSand(Uint8 alpha) {
        return Color(227, 212, 173, alpha);
    }
    Color Color::Khaki(Uint8 alpha) {
        return Color(211, 188, 141, alpha);
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
    Color Color::OffWhite(Uint8 alpha) {
        return Color(242, 233, 234, alpha);
    }

    // TODO: Grays from https://colorcodes.io/gray/
    // ===== GRAYS ===========
    Color Color::AshGray(uint8_t alpha) {
        return Color(178, 190, 181, alpha);
    }
    Color Color::Chrome(uint8_t alpha) {
        return Color(219, 226, 233, alpha);
    }
    Color Color::AgreeableGray(uint8_t alpha) {
        return Color(209, 203, 193, alpha);
    }
    Color Color::Aluminum(uint8_t alpha) {
        return Color(136, 139, 141, alpha);
    }
    Color Color::Anthracite(uint8_t alpha) {
        return Color(57, 61, 71, alpha);
    }
    Color Color::CoolGray(uint8_t alpha) {
        return Color(140, 146, 172, alpha);
    }
    Color Color::CharcoalGray(uint8_t alpha) {
        return Color(54, 69, 79, alpha);
    }
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
    Color Color::Pewter(uint8_t alpha) {
        return Color(96, 98, 99, alpha);
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
