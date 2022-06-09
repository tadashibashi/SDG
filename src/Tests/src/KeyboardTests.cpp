#include "SDG_Tests.h"
#include <Engine/Input/Keyboard.h>
#include <SDL_events.h>

TEST_CASE("Keyboard tests", "[Keyboard]")
{
    Keyboard keys;
    keys.Initialize();

    SECTION("Get KeyName")
    {
        std::string keyname;
        keyname = Keyboard::KeyName(Key::A);
        REQUIRE(keyname == "A");

        keyname = Keyboard::KeyName(Key::Backspace);
        REQUIRE(keyname == "Backspace");

        keyname = Keyboard::KeyName(Key::F1);
        REQUIRE(keyname == "F1");

        keyname = Keyboard::KeyName(Key::International4);
        REQUIRE(keyname.empty());
    }

    // No way to auto-test keyboard input functions unless there is some library that
    // simulates hardware keyboard presses/releases.
}
