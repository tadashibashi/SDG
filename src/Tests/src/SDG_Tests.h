#pragma once
#include <catch2/catch_test_macros.hpp>
#include <SDG/Platform.h>
#include <cmath>

namespace SDG
{
    // For use when comparing doubles
    // The answer will be considered close enough if equal up to the millionths place
    double Round(double d);
    float RoundF(float f);
}

using namespace SDG;

