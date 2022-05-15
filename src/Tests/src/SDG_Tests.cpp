/* =============================================================================
 * SDG_Tests
 * 
 * 
 * ===========================================================================*/
#include <catch2/catch_session.hpp>
#include "SDG_Tests.h"
#include <cmath>

int
main(int argc, char *argv[])
{
    Catch::Session().run();
    return 0;
}

double
SDG::Tests::Round(double d)
{
    return std::round(d * 1000000.0) / 1000000.0;
}

float
SDG::Tests::RoundF(float f)
{
    return std::round(f * 1000000.f) / 1000000.f;
}

