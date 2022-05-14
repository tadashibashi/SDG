/* =============================================================================
 * MathConstants
 * 
 * 
 * ===========================================================================*/
#pragma once
// Just in case there is some macro that clashes
#ifdef Pi
#undef Pi
#endif

#ifdef DegsPerRad
#undef DegsPerRad
#endif

#ifdef RadsPerDeg
#undef RadsPerDeg
#endif

namespace SDG::Math
{
    const double Pi = 3.1415926535897932;
    /// Multiply Radians by this to get Degrees.
    const double DegsPerRad = 180.0 / Pi;
    /// Multiply Degrees by this to get Radians.
    const double RadsPerDeg = Pi / 180.0;
}