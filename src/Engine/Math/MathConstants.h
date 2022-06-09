/*!
 * @file MathConstants.h
 * File for keeping math constants
 */
#pragma once

namespace SDG::Math
{
    const double Pi = 3.1415926535897932;
    /// Multiply Radians by this to get Degrees.
    const double DegsPerRad = 180.0 / Pi;
    /// Multiply Degrees by this to get Radians.
    const double RadsPerDeg = Pi / 180.0;
}