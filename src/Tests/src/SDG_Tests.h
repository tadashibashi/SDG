/// This header includes all the necessary headers to run a unit test.
#pragma once
#include <catch2/catch_test_macros.hpp>
#include <SDG/Platform.h>

namespace SDG::Tests
{
    /// For use when comparing doubles.
    /// The answer will be considered close enough if equal up to the millionths place
    double Round(double d);
    /// For use when comparing doubles.
    /// The answer will be considered close enough if equal up to the millionths
    float RoundF(float f);
}

using namespace SDG;
using namespace SDG::Tests;

