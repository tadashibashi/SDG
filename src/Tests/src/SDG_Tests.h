/// This header includes all the necessary includes to run unit tests
/// for SDG_Engine.
#pragma once
#include <catch2/catch_test_macros.hpp>
#include <Engine/Exceptions.h>
#include <Engine/Debug/Log.h>
#include <Engine/Platform.h>

namespace SDG::Tests
{
    /// For use when comparing doubles.
    /// The answer will be considered close enough if equal up to the millionths place
    double Round(double d);
    /// For use when comparing floats.
    /// The answer will be considered close enough if equal up to the millionths
    float RoundF(float f);
}

using namespace SDG;
using namespace SDG::Tests;

