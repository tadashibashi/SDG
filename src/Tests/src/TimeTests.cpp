/* =============================================================================
 * TimeTests
 * 
 * 
 * ===========================================================================*/
#include "SDG_Tests.h"
#include <SDG/Time/Time.h>
#include <SDL.h>

TEST_CASE("Time tests", "[Time]")
{
    SECTION("Default constructor values")
    {
        Time time;
        REQUIRE(time.Ticks() == 0);
        REQUIRE(time.FrameTicks() == 0);
    }

    SECTION("Regular use case")
    {
        // Initialize SDL, since Time depends on SDL
        REQUIRE(SDL_Init(SDL_INIT_TIMER) == 0);

        SDL_Delay(10);

        Time time;

        REQUIRE(time.Now() == 10);
        time.Update();
        REQUIRE(time.Ticks() >= 10);

        SDL_Delay(10);
        time.Update();

        REQUIRE(time.FrameTicks() >= 10);
        REQUIRE(time.Ticks() >= 20);

        double ms = time.As(Time::Unit::Ms);
        REQUIRE(ms == (double)time.Ticks());
        REQUIRE(ms == time.As(Time::Unit::Sec) * 1000.0);
        REQUIRE(ms == time.As(Time::Unit::Min) * 1000.0 * 60.0);
        REQUIRE(ms == time.As(Time::Unit::Hr) * 1000.0 * 3600.0);

        SDL_Quit();
    }
}