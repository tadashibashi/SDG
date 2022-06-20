#include "SDG_Tests.h"
#include <Engine/Game/Graphics/Frame.h>
#include <Engine/Graphics/Texture.h>

TEST_CASE("Frame tests", "[Frame]")
{
    Texture *tex = nullptr;

    Frame frame(Rect_<uint16_t>{ 0, 0, 32, 32 }, Rect_<uint16_t>{ 0, 0, 64, 64 }, true,
        Vec2_<uint16_t>(16, 16), tex);

    REQUIRE(frame.Anchor() == Vec2_<uint16_t>(16, 16));
    REQUIRE(frame.Angle() == -90.f);
    REQUIRE(frame.FrameRect() == Rect_<uint16_t>(0, 0, 32, 32));
    REQUIRE(frame.ImageRect() == Rect_<uint16_t>(0, 0, 64, 64));
    REQUIRE(frame.Texture() == nullptr);
    REQUIRE(frame.OffsetPos(false) == Point::Zero());
}