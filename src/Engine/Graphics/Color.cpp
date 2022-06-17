/// Color implementation file
#include "Color.h"
#include <SDL.h>
#include <Engine/Exceptions/InvalidArgumentException.h>

namespace SDG
{
    Color Color::FromString(const String &str, Format format, uint8_t base)
    {
        return FromNumber(str.ToNumber<uint64_t>(base), format, base);
    }

    Color Color::FromString(const StringView &str, Format format, uint8_t base)
    {
        return FromNumber(str.ToNumber<uint64_t>(base), format, base);
    }

    Color Color::FromNumber(uint64_t num, Format format, uint8_t base)
    {
        Color color;
        unsigned currentVal;
        for (int i = 0; i < 4; ++i)
        {
            switch (format)
            {
            case Format::RGBA8888:
                currentVal = num % (UINT8_MAX + 1);
                switch (i)
                {
                case 0: color.A(currentVal); break;
                case 1: color.B(currentVal); break;
                case 2: color.G(currentVal); break;
                case 3: color.R(currentVal); break;
                }

                num /= UINT8_MAX + 1;
                break;

            case Format::ARGB8888:
                currentVal = num % (UINT8_MAX + 1);
                switch (i)
                {
                case 0: color.B(currentVal); break;
                case 1: color.G(currentVal); break;
                case 2: color.R(currentVal); break;
                case 3: color.A(currentVal); break;
                }

                num /= UINT8_MAX + 1;
                break;
                
            case Format::RGB888:
                currentVal = num % (UINT8_MAX + 1);
                switch (i)
                {
                case 0: color.B(currentVal); break;
                case 1: color.G(currentVal); break;
                case 2: color.R(currentVal); break;
                case 3: color.A(UINT8_MAX); break;
                }
                break;
                num /= UINT8_MAX + 1;
            default:
                throw InvalidArgumentException(__func__, "format");
            }

            
        }

        return color;
    }

    Color &
    Color::Set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;

        return *this;
    }

    auto Color::operator==(const Color &other) const -> bool
    {
        return r == other.r && g == other.g &&
            b == other.b && a == other.a;
    }

    auto Color::operator!=(const Color &other) const -> bool
    {
        return !operator==(other);
    }

    // Pre-made Colors
    // ===== REDS ===========
    Color Color::Amaranth(uint8_t alpha) noexcept      { return { 244, 54, 76, alpha}; }
    Color Color::BloodRed(uint8_t alpha) noexcept      { return { 101, 28, 50, alpha}; }
    Color Color::BrightRed(uint8_t alpha) noexcept     { return { 101, 28, 50, alpha}; }
    Color Color::BrickRed(uint8_t alpha) noexcept      { return { 203, 65, 84, alpha}; }
    Color Color::Cerise(uint8_t alpha) noexcept        { return { 223, 70, 97, alpha }; }
    Color Color::CherryRed(uint8_t alpha) noexcept     { return { 205, 0, 26, alpha }; }
    Color Color::ChristmasRed(uint8_t alpha) noexcept  { return { 214, 0, 28, alpha }; }
    Color Color::ComicBookRed(uint8_t alpha) noexcept  { return { 237, 29, 36, alpha }; }
    Color Color::Cranberry(uint8_t alpha) noexcept     { return { 166, 10, 61, alpha }; }
    Color Color::EarthyRed(uint8_t alpha) noexcept     { return { 153, 71, 88, alpha }; }
    Color Color::FireTruckRed(uint8_t alpha) noexcept  { return { 206, 32, 41, alpha }; }
    Color Color::Heliconia(uint8_t alpha) noexcept     { return { 219, 62, 121, alpha }; }
    Color Color::LightRed(uint8_t alpha) noexcept      { return { 255, 114, 118, alpha }; }
    Color Color::LightsaberRed(uint8_t alpha) noexcept { return { 235, 33, 46, alpha }; }
    Color Color::Mango(uint8_t alpha) noexcept         { return { 183, 94, 74, alpha }; }
    Color Color::MediumDarkRed(uint8_t alpha) noexcept { return { 128, 5, 0, alpha }; }
    Color Color::NeonRed(uint8_t alpha) noexcept       { return { 210, 39, 48, alpha }; }
    Color Color::OxbloodRed(uint8_t alpha) noexcept    { return { 112, 57, 63, alpha }; }
    Color Color::PastelRed(uint8_t alpha) noexcept     { return { 255, 109, 106, alpha }; }
    Color Color::RacingRed(uint8_t alpha) noexcept     { return { 189, 22, 44, alpha }; }
    Color Color::RedOrange(uint8_t alpha) noexcept     { return { 252, 76, 2, alpha }; }
    Color Color::RhodamineRed(uint8_t alpha) noexcept  { return { 225, 0, 152, alpha }; }
    Color Color::RichRed(uint8_t alpha) noexcept       { return { 161, 0, 14, alpha }; }
    Color Color::RoseRed(uint8_t alpha) noexcept       { return { 255, 3, 62, alpha }; }
    Color Color::Rosso(uint8_t alpha) noexcept         { return { 225, 6, 0, alpha }; }
    Color Color::RubyRed(uint8_t alpha) noexcept       { return { 228, 0, 70, alpha }; }
    Color Color::RusticRed(uint8_t alpha) noexcept     { return { 84, 11, 12, alpha }; }
    Color Color::ScarletRed(uint8_t alpha) noexcept    { return { 187, 0, 0, alpha }; }
    Color Color::Strawberry(uint8_t alpha) noexcept    { return { 197, 70, 68, alpha }; }
    Color Color::VarsityRed(uint8_t alpha) noexcept    { return { 206, 17, 65, alpha }; }
    Color Color::Watermelon(uint8_t alpha) noexcept    { return { 198, 58, 79, alpha }; }
    Color Color::WineRed(uint8_t alpha) noexcept       { return { 155, 34, 66, alpha }; }
    Color Color::IndianRed(uint8_t alpha) noexcept     { return { 205, 92, 92, alpha }; }
    Color Color::LightCoral(uint8_t alpha) noexcept    { return { 240, 128, 128, alpha }; }
    Color Color::Salmon(uint8_t alpha) noexcept        { return { 250, 128, 114, alpha }; }
    Color Color::DarkSalmon(uint8_t alpha) noexcept    { return { 233, 150, 122, alpha }; }
    Color Color::LightSalmon(uint8_t alpha) noexcept   { return { 255, 160, 122, alpha }; }
    Color Color::Crimson(uint8_t alpha) noexcept       { return { 220, 20, 60, alpha }; }
    Color Color::Red(uint8_t alpha) noexcept           { return { 255, 0, 0, alpha }; }
    Color Color::FireBrick(uint8_t alpha) noexcept     { return { 178, 34, 34, alpha }; }
    Color Color::DarkRed(uint8_t alpha) noexcept       { return { 139, 0, 0, alpha }; }

    // ===== PINKS ===========
    Color Color::Pink(uint8_t alpha) noexcept              { return { 255, 192, 203, alpha }; }
    Color Color::BabyPink(uint8_t alpha) noexcept          { return { 242, 172, 185, alpha }; }
    Color Color::BlushPink(uint8_t alpha) noexcept         { return { 222, 93, 131, alpha }; }
    Color Color::BrightPink(uint8_t alpha) noexcept        { return { 255, 0, 127, alpha }; }
    Color Color::BubblegumPink(uint8_t alpha) noexcept     { return { 255, 193, 204, alpha }; }
    Color Color::CarnationPink(uint8_t alpha) noexcept     { return { 255, 166, 201, alpha }; }
    Color Color::ChampagnePink(uint8_t alpha) noexcept     { return { 246, 225, 211, alpha }; }
    Color Color::CherryBlossomPink(uint8_t alpha) noexcept { return { 255, 183, 197, alpha }; }
    Color Color::CoralPink(uint8_t alpha) noexcept         { return { 242, 130, 127, alpha }; }
    Color Color::CottonCandyPink(uint8_t alpha) noexcept   { return { 255, 188, 217, alpha }; }
    Color Color::DarkPink(uint8_t alpha) noexcept          { return { 231, 84, 128, alpha }; }
    Color Color::DeepPink(uint8_t alpha) noexcept          { return { 214, 37, 152, alpha }; }
    Color Color::DustyRosePink(uint8_t alpha) noexcept     { return { 183, 123, 130, alpha }; }
    Color Color::FlamingoPink(uint8_t alpha) noexcept      { return { 252, 142, 172, alpha }; }
    Color Color::FlowerPink(uint8_t alpha) noexcept        { return { 227, 91, 137, alpha }; }
    Color Color::FourescentPink(uint8_t alpha) noexcept    { return { 255, 105, 180, alpha}; }
    Color Color::Fuchsia(uint8_t alpha) noexcept           { return { 217, 2, 125, alpha }; }
    Color Color::GoldPink(uint8_t alpha) noexcept          { return { 230, 199, 194, alpha }; }
    Color Color::GrapefruitPink(uint8_t alpha) noexcept    { return { 224, 112, 124, alpha }; }
    Color Color::HighlighterPink(uint8_t alpha) noexcept   { return { 255, 20, 147, alpha }; }
    Color Color::KnockoutPink(uint8_t alpha) noexcept      { return { 255, 62, 165, alpha }; }
    Color Color::LightBlush(uint8_t alpha) noexcept        { return { 241, 171, 185, alpha }; }
    Color Color::LipPink(uint8_t alpha) noexcept           { return { 219, 172, 152, alpha }; }
    Color Color::LightPink(uint8_t alpha) noexcept         { return { 245, 218, 223, alpha }; }
    Color Color::Magenta(uint8_t alpha) noexcept           { return { 217, 1, 122, alpha }; }
    Color Color::Melon(uint8_t alpha) noexcept             { return { 247, 188, 172, alpha }; }
    Color Color::Milano(uint8_t alpha) noexcept            { return { 217, 93, 103, alpha }; }
    Color Color::MillenialPink(uint8_t alpha) noexcept     { return { 255, 209, 220, alpha }; }
    Color Color::Mulberry(uint8_t alpha) noexcept          { return { 207, 87, 138, alpha }; }
    Color Color::NeonPink(uint8_t alpha) noexcept          { return { 251, 72, 196, alpha }; }
    Color Color::SkinPink(uint8_t alpha) noexcept          { return { 221, 192, 180, alpha }; }
    Color Color::PalePink(uint8_t alpha) noexcept          { return { 242, 212, 215, alpha }; }
    Color Color::PassionPink(uint8_t alpha) noexcept       { return { 206, 116, 167, alpha }; }
    Color Color::PastelPink(uint8_t alpha) noexcept        { return { 233, 205, 208, alpha }; }
    Color Color::PearlPink(uint8_t alpha) noexcept         { return { 231, 172, 207, alpha }; }
    Color Color::RosyPink(uint8_t alpha) noexcept          { return { 255, 102, 204, alpha }; }
    Color Color::SalmonPink(uint8_t alpha) noexcept        { return { 255, 134, 116, alpha }; }
    Color Color::SilveryPink(uint8_t alpha) noexcept       { return { 220, 181, 180, alpha }; }
    Color Color::SoftPink(uint8_t alpha) noexcept          { return { 255, 184, 191, alpha }; }
    Color Color::SweetPink(uint8_t alpha) noexcept         { return { 238, 145, 141, alpha }; }
    Color Color::ValentinePink(uint8_t alpha) noexcept     { return { 230, 166, 190, alpha }; }
    Color Color::VibrantPink(uint8_t alpha) noexcept       { return { 254, 1, 154, alpha }; }
    Color Color::HotPink(uint8_t alpha) noexcept           { return { 255, 105, 180, alpha }; }
    Color Color::MediumVioletRed(uint8_t alpha) noexcept   { return { 199, 21, 133, alpha }; }
    Color Color::PaleVioletRed(uint8_t alpha) noexcept     { return { 219, 112, 147, alpha }; }

    // ===== ORANGES ===========
    Color Color::Amber(uint8_t alpha) noexcept { return Color(255, 198, 0, alpha); }
    Color Color::Apricot(uint8_t alpha) noexcept { return Color(255, 182, 115, alpha); }
    Color Color::BrightOrange(uint8_t alpha) noexcept { return Color(255, 168, 0, alpha); }
    Color Color::BurntOrange(uint8_t alpha) noexcept { return Color(203, 96, 21, alpha); }
    Color Color::ConstructionOrange(uint8_t alpha) noexcept { return Color(254, 80, 0, alpha); }
    Color Color::DarkOrange(uint8_t alpha) noexcept { return Color(220, 88, 42, alpha); }
    Color Color::GoldfishOrange(uint8_t alpha) noexcept { return Color(255, 153, 19, alpha); }
    Color Color::HalloweenOrange(uint8_t alpha) noexcept { return Color(252, 76, 2, alpha); }
    Color Color::HunterBlazeOrange(uint8_t alpha) noexcept { return Color(255, 130, 0, alpha); }
    Color Color::LightOrange(uint8_t alpha) noexcept { return Color(252, 210, 153, alpha); }
    Color Color::MonarchOrange(uint8_t alpha) noexcept { return Color(226, 82, 42, alpha); }
    Color Color::NeonOrange(uint8_t alpha) noexcept { return Color(255, 173, 0, alpha); }
    Color Color::PastelOrange(uint8_t alpha) noexcept { return Color(239, 190, 125, alpha); }
    Color Color::Peach(uint8_t alpha) noexcept { return Color(255, 203, 164, alpha); }
    Color Color::PumpkinSpiceOrange(uint8_t alpha) noexcept { return Color(215, 107, 0, alpha); }
    Color Color::RoadSignOrange(uint8_t alpha) noexcept { return Color(252, 143, 50, alpha); }
    Color Color::Sunset(uint8_t alpha) noexcept { return Color(250, 198, 104, alpha); }
    Color Color::TigerOrange(uint8_t alpha) noexcept { return Color(249, 101, 21, alpha); }
    Color Color::Tangerine(uint8_t alpha) noexcept { return Color(237, 139, 0, alpha); }
    Color Color::Tumeric(uint8_t alpha) noexcept { return Color(255, 133, 15, alpha); }
    Color Color::Vermillion(uint8_t alpha) noexcept { return Color(221, 50, 36, alpha); }
    Color Color::Coral(uint8_t alpha) noexcept { return Color(255, 127, 80, alpha); }
    Color Color::Tomato(uint8_t alpha) noexcept { return Color(255, 99, 71, alpha); }
    Color Color::OrangeRed(uint8_t alpha) noexcept { return Color(255, 69, 0, alpha); }
    Color Color::Orange(uint8_t alpha) noexcept { return Color(255, 165, 0, alpha); }

    // ===== YELLOWS ===========
    Color Color::Gold(uint8_t alpha) noexcept { return Color(255, 215, 0, alpha); }
    Color Color::Yellow(uint8_t alpha) noexcept { return Color(255, 255, 0, alpha); }
    Color Color::LightYellow(uint8_t alpha) noexcept { return Color(255, 255, 0, alpha); }
    Color Color::LemonChiffon(uint8_t alpha) noexcept { return Color(255, 255, 224, alpha); }
    Color Color::LightGoldenrodYellow(uint8_t alpha) noexcept { return Color(250, 250, 210, alpha); }
    Color Color::PapayaWhip(uint8_t alpha) noexcept { return Color(255, 239, 213, alpha); }
    Color Color::Moccasin(uint8_t alpha) noexcept { return Color(255, 228, 181, alpha); }
    Color Color::PeachPuff(uint8_t alpha) noexcept { return Color(255, 218, 185, alpha); }
    Color Color::PaleGoldenrod(uint8_t alpha) noexcept { return Color(238, 232, 170, alpha); }
    Color Color::DarkKhaki(uint8_t alpha) noexcept { return Color(189, 183, 107, alpha); }

    // ===== GOLDS =============
    Color Color::HarvestGold(uint8_t alpha) noexcept { return Color(218, 145, 0, alpha); }
    Color Color::PaleGold(uint8_t alpha) noexcept { return Color(230, 190, 138, alpha); }
    Color Color::SatinSheenGold(uint8_t alpha) noexcept { return Color(203, 161, 53, alpha); }

    // ===== PURPLES ===========
     
    Color Color::Lavender(uint8_t alpha) noexcept { return Color(230, 230, 250, alpha); }
    Color Color::Thistle(uint8_t alpha) noexcept { return Color(216, 191, 216, alpha); }
    Color Color::Plum(uint8_t alpha) noexcept { return Color(221, 160, 221, alpha); }
    Color Color::Violet(uint8_t alpha) noexcept { return Color(238, 130, 238, alpha); }
    Color Color::Orchid(uint8_t alpha) noexcept { return Color(218, 112, 214, alpha); }
    Color Color::MediumOrchid(uint8_t alpha) noexcept { return Color(186, 85, 211, alpha); }
    Color Color::MediumPurple(uint8_t alpha) noexcept { return Color(147, 112, 219, alpha); }
    Color Color::BlueViolet(uint8_t alpha) noexcept { return Color(138, 43, 226, alpha); }
    Color Color::DarkViolet(uint8_t alpha) noexcept { return Color(148, 0, 211, alpha); }
    Color Color::DarkOrchid(uint8_t alpha) noexcept { return Color(153, 50, 204, alpha); }
    Color Color::DarkMegenta(uint8_t alpha) noexcept { return Color(139, 0, 139, alpha); }
    Color Color::Purple(uint8_t alpha) noexcept { return Color(128, 0, 128, alpha); }
    Color Color::RebeccaPurple(uint8_t alpha) noexcept { return Color(102, 51, 153, alpha); }
    Color Color::Indigo(uint8_t alpha) noexcept { return Color(75, 0, 130, alpha); }
    Color Color::MediumSlateBlue(uint8_t alpha) noexcept { return Color(123, 104, 238, alpha); }
    Color Color::SlateBlue(uint8_t alpha) noexcept { return Color(106, 90, 205, alpha); }
    Color Color::DarkSlateBlue(uint8_t alpha) noexcept { return Color(72, 61, 139, alpha); }

    // ===== Greens ==========

    Color Color::GreenYellow(uint8_t alpha) noexcept { return Color(173, 255, 47, alpha); }
    Color Color::Chartreuse(uint8_t alpha) noexcept { return Color(127, 255, 0, alpha); }
    Color Color::LawnGreen(uint8_t alpha) noexcept { return Color(124, 255, 0, alpha); }
    Color Color::Lime(uint8_t alpha) noexcept { return Color(0, 255, 0, alpha); }
    Color Color::LimeGreen(uint8_t alpha) noexcept { return Color(50, 205, 50, alpha); }
    Color Color::PaleGreen(uint8_t alpha) noexcept { return Color(152, 251, 152, alpha); }
    Color Color::LightGreen(uint8_t alpha) noexcept { return Color(144, 238, 144, alpha); }
    Color Color::MediumSpringGreen(uint8_t alpha) noexcept { return Color(0, 250, 154, alpha); }
    Color Color::SpringGreen(uint8_t alpha) noexcept { return Color(0, 255, 127, alpha); }
    Color Color::MediumSeaGreen(uint8_t alpha) noexcept { return Color(60, 179, 113, alpha); }
    Color Color::SeaGreen(uint8_t alpha) noexcept { return Color(46, 139, 87, alpha); }
    Color Color::ForestGreen(uint8_t alpha) noexcept { return Color(34, 139, 34, alpha); }
    Color Color::Green(uint8_t alpha) noexcept { return Color(0, 128, 0, alpha); }
    Color Color::DarkGreen(uint8_t alpha) noexcept { return Color(0, 100, 0, alpha); }
    Color Color::YellowGreen(uint8_t alpha) noexcept { return Color(154, 205, 50, alpha); }
    Color Color::OliveDrab(uint8_t alpha) noexcept { return Color(107, 142, 35, alpha); }
    Color Color::Olive(uint8_t alpha) noexcept { return Color(128, 128, 0, alpha); }
    Color Color::DarkOliveGreen(uint8_t alpha) noexcept { return Color(85, 107, 47, alpha); }
    Color Color::MediumAquamarine(uint8_t alpha) noexcept { return Color(102, 205, 170, alpha); }
    Color Color::DarkSeaGreen(uint8_t alpha) noexcept { return Color(143, 188, 143, alpha); }
    Color Color::LightSeaGreen(uint8_t alpha) noexcept { return Color(32, 178, 170, alpha); }
    Color Color::DarkCyan(uint8_t alpha) noexcept { return Color(0, 139, 139, alpha); }
    Color Color::Teal(uint8_t alpha) noexcept { return Color(0, 128, 128, alpha); }

    // ===== Blues / Cyans =======

    Color Color::Aqua(uint8_t alpha) noexcept { return Color(5, 195, 221, alpha); }
    Color Color::Azure(uint8_t alpha) noexcept { return Color(0, 138, 216, alpha); }
    Color Color::BabyBlue(uint8_t alpha) noexcept { return Color(155, 211, 221, alpha); }
    Color Color::BlueScreenOfDeath(uint8_t alpha) noexcept { return Color(8, 39, 245, alpha); }
    Color Color::BrightBlue(uint8_t alpha) noexcept { return Color(0, 78, 255, alpha); }
    Color Color::BrightNavy(uint8_t alpha) noexcept { return Color(75, 104, 184, alpha); }
    Color Color::CarolinaBlue(uint8_t alpha) noexcept { return Color(153, 186, 221, alpha); }
    Color Color::CetaceanBlue(uint8_t alpha) noexcept { return Color(0, 20, 75, alpha); }
    Color Color::ChambrayBlue(uint8_t alpha) noexcept { return Color(60, 82, 145, alpha); }
    Color Color::CloudBurstBlue(uint8_t alpha) noexcept { return Color(33, 46, 82, alpha); }
    Color Color::CobaltBlue(uint8_t alpha) noexcept { return Color(0, 80, 181, alpha); }
    Color Color::ComicBookBlue(uint8_t alpha) noexcept { return Color(0, 174, 239, alpha); }
    Color Color::CortanaBlue(uint8_t alpha) noexcept { return Color(0, 163, 225, alpha); }
    Color Color::Cyan(uint8_t alpha) noexcept { return Color(0, 188, 227, alpha); }
    Color Color::CornflowerBlue(uint8_t alpha) noexcept { return Color(130, 163, 255, alpha); }
    Color Color::DarkBlue(uint8_t alpha) noexcept { return Color(3, 37, 126, alpha); }
    Color Color::DazzlingBlue(uint8_t alpha) noexcept { return Color(46, 77, 167, alpha); }
    Color Color::ElectricBlue(uint8_t alpha) noexcept { return Color(89, 203, 232, alpha); }
    Color Color::FrenchBlue(uint8_t alpha) noexcept { return Color(0, 110, 179, alpha); }
    Color Color::LightsaberBlue(uint8_t alpha) noexcept { return Color(46, 103, 248, alpha); }
    Color Color::MalibuBlue(uint8_t alpha) noexcept { return Color(91, 126, 222, alpha); }
    Color Color::MarinesBlue(uint8_t alpha) noexcept { return Color(0, 68, 129, alpha); }
    Color Color::MintBlue(uint8_t alpha) noexcept { return Color(66, 158, 157, alpha); }
    Color Color::KingBlue(uint8_t alpha) noexcept { return Color(65, 105, 225, alpha); }
    Color Color::PaleBlue(uint8_t alpha) noexcept { return Color(175, 238, 238, alpha); }
    Color Color::PeacockBlue(uint8_t alpha) noexcept { return Color(0, 164, 180, alpha); }
    Color Color::PowderBlue(uint8_t alpha) noexcept { return Color(176, 224, 230, alpha); }
    Color Color::PoliceBlue(uint8_t alpha) noexcept { return Color(19, 93, 216, alpha); }
    Color Color::LightBlue(uint8_t alpha) noexcept { return Color(164, 219, 232, alpha); }
    Color Color::NavyBlue(uint8_t alpha) noexcept { return Color(32, 42, 68, alpha); }
    Color Color::DenimBlue(uint8_t alpha) noexcept { return Color(21, 96, 189, alpha); }
    Color Color::FluorescentBlue(uint8_t alpha) noexcept { return Color(172, 55, 238, alpha); }
    Color Color::HonoluluBlue(uint8_t alpha) noexcept { return Color(0, 118, 182, alpha); }
    Color Color::IceBlue(uint8_t alpha) noexcept { return Color(200, 233, 233, alpha); }
    Color Color::IndigoBlue(uint8_t alpha) noexcept { return Color(75, 0, 130, alpha); }
    Color Color::PacificBlue(uint8_t alpha) noexcept { return Color(5,  169, 199, alpha); }
    Color Color::PastelBlue(uint8_t alpha) noexcept { return Color(139, 211, 230, alpha); }
    Color Color::OceanBlue(uint8_t alpha) noexcept { return Color(0, 94, 184, alpha); }
    Color Color::Periwinkle(uint8_t alpha) noexcept { return Color(124, 131, 188, alpha); }
    Color Color::NeonBlue(uint8_t alpha) noexcept { return Color(77, 77, 255, alpha); }
    Color Color::MidnightBlue(uint8_t alpha) noexcept { return Color(100, 71, 0, alpha); }
    Color Color::TennisCourtBlue(uint8_t alpha) noexcept { return Color(30, 143, 213, alpha); }
    Color Color::SapphireBlue(uint8_t alpha) noexcept { return Color(15, 82, 186, alpha); }
    Color Color::RotaryBlue(uint8_t alpha) noexcept { return Color(0, 51, 153, alpha); }
    Color Color::RobinEggBlue(uint8_t alpha) noexcept { return Color(31, 206, 203, alpha); }
    Color Color::RichBlue(uint8_t alpha) noexcept { return Color(8, 146, 208, alpha); }
    Color Color::ReflexBlue(uint8_t alpha) noexcept { return Color(51, 51, 153, alpha); }
    Color Color::RoyalBlue(uint8_t alpha) noexcept { return Color(85, 118, 209, alpha); }
    Color Color::RoadSignBlue(uint8_t alpha) noexcept { return Color(15, 57, 139, alpha); }
    Color Color::SkyBlue(uint8_t alpha) noexcept { return Color(0, 181, 226, alpha); }
    Color Color::SeaBlue(uint8_t alpha) noexcept { return Color(0, 105, 148, alpha); }
    Color Color::Serenity(uint8_t alpha) noexcept { return Color(177, 201, 232, alpha); }
    Color Color::TealBlue(uint8_t alpha) noexcept { return Color(0, 124, 128, alpha); }
    Color Color::UmpireBlue(uint8_t alpha) noexcept { return Color(123, 178, 221, alpha); }
    Color Color::UsNavyBlue(uint8_t alpha) noexcept { return Color(0, 47, 108, alpha); }




    Color Color::Cerulean(uint8_t alpha) noexcept { return Color(0, 143, 190, alpha); }
    Color Color::LightCyan(uint8_t alpha) noexcept { return Color(224, 255, 255, alpha); }
    Color Color::PaleTurquoise(uint8_t alpha) noexcept { return Color(175, 238, 238, alpha); }
    Color Color::Aquamarine(uint8_t alpha) noexcept { return Color(127, 255, 212, alpha); }
    Color Color::Turquoise(uint8_t alpha) noexcept { return Color(64, 224, 208, alpha); }
    Color Color::MediumTurquoise(uint8_t alpha) noexcept { return Color(72, 209, 204, alpha); }
    Color Color::DarkTurquoise(uint8_t alpha) noexcept { return Color(0, 206, 209, alpha); }
    Color Color::CadetBlue(uint8_t alpha) noexcept { return Color(95, 158, 160, alpha); }
    Color Color::SteelBlue(uint8_t alpha) noexcept { return Color(70, 130, 180, alpha); }
    Color Color::LightSteelBlue(uint8_t alpha) noexcept { return Color(176, 196, 222, alpha); }
    Color Color::LightSkyBlue(uint8_t alpha) noexcept { return Color(135, 206, 250, alpha); }
    Color Color::DeepSkyBlue(uint8_t alpha) noexcept { return Color(0, 191, 255, alpha); }
    Color Color::DodgerBlue(uint8_t alpha) noexcept { return Color(30, 144, 255, alpha); }
    Color Color::Blue(uint8_t alpha) noexcept { return Color(0, 0, 255, alpha); }
    Color Color::MediumBlue(uint8_t alpha) noexcept { return Color(0, 0, 205, alpha); }

    // ===== Browns ===========

    Color Color::Cornsilk(uint8_t alpha) noexcept { return Color(255, 248, 220, alpha); }
    Color Color::BlanchedAlmond(uint8_t alpha) noexcept { return Color(255, 234, 205, alpha); }
    Color Color::Bisque(uint8_t alpha) noexcept { return Color(255, 228, 196, alpha); }
    Color Color::NavajoWhite(uint8_t alpha) noexcept { return Color(255, 222, 173, alpha); }
    Color Color::Wheat(uint8_t alpha) noexcept { return Color(245, 222, 179, alpha); }
    Color Color::BurlyWood(uint8_t alpha) noexcept { return Color(222, 184, 135, alpha); }
    Color Color::Tan(uint8_t alpha) noexcept { return Color(210, 180, 140, alpha); }
    Color Color::RosyBrown(uint8_t alpha) noexcept { return Color(188, 143, 143, alpha); }
    Color Color::SandyBrown(uint8_t alpha) noexcept { return Color(244, 164, 96, alpha); }
    Color Color::Goldenrod(uint8_t alpha) noexcept { return Color(218, 165, 32, alpha); }
    Color Color::DarkGoldenrod(uint8_t alpha) noexcept { return Color(184, 134, 11, alpha); }
    Color Color::Peru(uint8_t alpha) noexcept { return Color(205, 133, 63, alpha); }
    Color Color::Chocolate(uint8_t alpha) noexcept { return Color(210, 105, 30, alpha); }
    Color Color::SaddleBrown(uint8_t alpha) noexcept { return Color(139, 69, 19, alpha); }
    Color Color::Sienna(uint8_t alpha) noexcept { return Color(160, 82, 45, alpha); }
    Color Color::Brown(uint8_t alpha) noexcept { return Color(165, 42, 42, alpha); }
    Color Color::Maroon(uint8_t alpha) noexcept { return Color(128, 0, 0, alpha); }

    // == Beiges ===========================

    Color Color::Cream(uint8_t alpha) noexcept { return Color(240, 235, 210, alpha); }
    Color Color::UnbleachedSilk(uint8_t alpha) noexcept { return Color(229, 158, 109, alpha); }
    Color Color::DesertSand(uint8_t alpha) noexcept { return Color(227, 212, 173, alpha); }
    Color Color::Khaki(uint8_t alpha) noexcept { return Color(211, 188, 141, alpha); }


    // ===== Whites ===========

    Color Color::White(uint8_t alpha) noexcept { return Color(255, 255, 255, alpha); }
    Color Color::Snow(uint8_t alpha) noexcept { return Color(255, 250, 250, alpha); }
    Color Color::Honeydew(uint8_t alpha) noexcept { return Color(240, 255, 240, alpha); }
    Color Color::MintCream(uint8_t alpha) noexcept { return Color(245, 255, 250, alpha); }
    Color Color::AliceBlue(uint8_t alpha) noexcept { return Color(240, 248, 255, alpha); }
    Color Color::GhostWhite(uint8_t alpha) noexcept { return Color(248, 248, 255, alpha); }
    Color Color::WhiteSmoke(uint8_t alpha) noexcept { return Color(245, 245, 245, alpha); }
    Color Color::Seashell(uint8_t alpha) noexcept { return Color(255, 245, 238, alpha); }
    Color Color::Beige(uint8_t alpha) noexcept { return Color(245, 245, 220, alpha); }
    Color Color::OldLace(uint8_t alpha) noexcept { return Color(253, 245, 230, alpha); }
    Color Color::FloralWhite(uint8_t alpha) noexcept { return Color(255, 250, 240, alpha); }
    Color Color::Ivory(uint8_t alpha) noexcept { return Color(255, 255, 240, alpha); }
    Color Color::AntiqueWhite(uint8_t alpha) noexcept { return Color(250, 235, 215, alpha); }
    Color Color::Linen(uint8_t alpha) noexcept { return Color(250, 240, 230, alpha); }
    Color Color::LavenderBlush(uint8_t alpha) noexcept { return Color(255, 240, 245, alpha); }
    Color Color::MistyRose(uint8_t alpha) noexcept { return Color(255, 228, 225, alpha); }
    Color Color::OffWhite(uint8_t alpha) noexcept { return Color(242, 233, 234, alpha); }

    // TODO: Grays from https://colorcodes.io/gray/
    // ===== GRAYS ===========

    Color Color::AshGray(uint8_t alpha) noexcept { return Color(178, 190, 181, alpha); }
    Color Color::Chrome(uint8_t alpha) noexcept { return Color(219, 226, 233, alpha); }
    Color Color::AgreeableGray(uint8_t alpha) noexcept { return Color(209, 203, 193, alpha); }
    Color Color::Aluminum(uint8_t alpha) noexcept { return Color(136, 139, 141, alpha); }
    Color Color::Anthracite(uint8_t alpha) noexcept { return Color(57, 61, 71, alpha); }
    Color Color::CoolGray(uint8_t alpha) noexcept { return Color(140, 146, 172, alpha); }
    Color Color::CharcoalGray(uint8_t alpha) noexcept { return Color(54, 69, 79, alpha); }
    Color Color::Gainsboro (uint8_t alpha) noexcept { return Color(220, alpha); }
    Color Color::LightGray (uint8_t alpha) noexcept { return Color(211, alpha); }
    Color Color::Silver (uint8_t alpha) noexcept { return Color(192, alpha); }
    Color Color::DarkGray (uint8_t alpha) noexcept { return Color(169, alpha); }
    Color Color::Gray (uint8_t alpha) noexcept { return Color(128, alpha); }
    Color Color::Pewter(uint8_t alpha) noexcept { return Color(96, 98, 99, alpha); }

    Color Color::DimGray (uint8_t alpha) noexcept { return Color(105, alpha); }
    Color Color::LightSlateGray(uint8_t alpha) noexcept { return Color(119, 136, 153, alpha); }
    Color Color::SlateGray(uint8_t alpha) noexcept { return Color(112, 128, 144, alpha); }
    Color Color::DarkSlateGray(uint8_t alpha) noexcept { return Color(47, 79, 79, alpha); }
    Color Color::Black(uint8_t alpha) noexcept { return Color(0, 0, 0, alpha); }
}
