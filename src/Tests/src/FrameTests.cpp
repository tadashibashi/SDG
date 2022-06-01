#include "SDG_Tests.h"
#include <SDG/Graphics/Frame.h>


TEST_CASE("Frame tests", "[Frame]")
{
    Texture2D *tex = nullptr;

    Frame frame(Rectangle(0, 0, 32, 32), Rectangle(0, 0, 64, 64), true,
        Point(16, 16), "TestFrame", CRef(tex));

    REQUIRE(frame.Anchor() == Point(16, 16));
    REQUIRE(frame.Angle() == 90.f);
    REQUIRE(frame.FrameRect() == Rectangle(0, 0, 32, 32));
    REQUIRE(frame.ImageRect() == Rectangle(0, 0, 64, 64));
    REQUIRE(frame.Name() == "TestFrame");
    REQUIRE(frame.Texture().Get() == nullptr);
    REQUIRE(frame.OffsetRect() == Rectangle(0, 0, 32, 32));
}