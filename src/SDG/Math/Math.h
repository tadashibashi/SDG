/*!
 * @file Math.h
 * Contains a group of math helper functions under the SDG::Math namespace.
 * For pseudo-random number generation, please look at Rand.h
 *
 */
#pragma once
#include "MathConstants.h"

#include <SDG/Lib/Swap.h>

#include <initializer_list>
#include <type_traits>

// Optional more efficient Min/Max/Clamp, perhaps for internal use
#define SDG_Min(a, b) ((a) < (b) ? (a) : (b))
#define SDG_Max(a, b) ((a) > (b) ? (a) : (b))
#define SDG_Clamp(n, min, max) (((n) < (max) ? (n) : (max)) > (min) ? \
    ((n) < (max) ? (n) : (max)) : (min))

namespace SDG::Math
{
    /// Linear interpolation. Requires floating point for accuracy, but
    /// integer types are usable with a floored result.
    template <typename T>
    inline double Lerp(T val, T dest, double amt)
    {
        return (dest - val) * amt + val;
    }

    inline float Lerp(float val, float dest, float amt)
    {
        return (dest - val) * amt + val;
    }

    template<typename T>
    inline double ToDegrees(T rad)
    {
        return rad * DegsPerRad;
    }

    inline float ToDegrees(float rad)
    {
        return rad * (float)DegsPerRad;
    }

    template<typename T>
    inline double ToRadians(T degrees)
    {
        return degrees * RadsPerDeg;
    }

    inline float ToRadians(float degrees)
    {
        return degrees * (float)RadsPerDeg;
    }

    /// Returns the largest of two numbers. Please use SDG_Min for a more
    /// efficient macro version.
    template <typename T>
    inline T Min(T a, T b)
    {
        return SDG_Min(a, b);
    }

    /// Returns the largest of two numbers. Please use SDG_Max for a more
    /// efficient macro version.
    template <typename T>
    inline T Max(T a, T b)
    {
        return SDG_Max(a, b);
    }

    /// Constrains a value between two numbers, inclusively on both ends.
    /// Min may be greater than max, and the number will still be clamped
    /// between by both ends.
    template <typename T>
    inline T Clamp(T value, T min, T max)
    {
        // Protect case where min > max
        return (min > max) ? SDG_Clamp(value, max, min) :
            SDG_Clamp(value, min, max);
    }

    /// Returns the absolute value of a number
    template <typename T>
    inline T Abs(T n) { return n < 0 ? -n : n; }

    /// Returns +1 on positive number or 0, and -1 on negative numbers
    template <typename T>
    inline T Sign(T n) { return (T)(n < 0 ? -1 : 1); }

    template <typename T>
    inline T Round(T n) { return (T)((int)(n + (n < 0 ? -0.5L : 0.5L))); }

    /// Round to the 10^n's place.
    double RoundN(double x, int n);

    /// Round to the 10^n's place.
    float RoundN(float x, int n);

    double Cos(double rad);
    float Cos(float rad);
    double Sin(double rad);
    float Sin(float rad);
    double Tan(double rad);
    float Tan(float rad);
    double ArcCos(double rad);
    float ArcCos(float rad);
    double ArcSin(double rad);
    float ArcSin(float rad);
    double ArcTan(double rad);
    float ArcTan(float rad);

    double Sqrt(double n);
    float Sqrt(float n);
    double Pow(double n, double pow);
    float Pow(float n, double pow);

    double Log(double n);
    float Log(float n);
    double Log10(double n);
    float Log10(float n);

    /// Returns the Y value from a projected position.
    template<typename T>
    inline double TrajectoryX(T degrees, T length)
    {
        return Cos(degrees * RadsPerDeg) * length;
    }

    inline float TrajectoryX(float degrees, float length)
    {
        return Cos(degrees * RadsPerDeg) * length;
    }

    /// Returns the Y value from a projected position.
    template<typename T>
    inline double TrajectoryY(T degrees, T length)
    {
        // Negative value to match downward y coordinate system
        return -(Sin(degrees * RadsPerDeg) * length);
    }

    inline float TrajectoryY(float degrees, float length)
    {
        // Negative value to match downward y coordinate system
        return (float)-(Sin(degrees * RadsPerDeg) * length);
    }

    /**
    * Modulo function for floating point types that does not reflect across 0
    */
    double ModF(double x, double n);
    float ModF(float x, float n);

    /// Modulo function for integral types that does not reflect across 0
    int Mod(int x, int n);

    /**
     * Return a number that 'wraps around' to the opposite boundary when either boundary is exceeded.
     * Used with floating point numbers.
     * Upper boundary is exclusive, and lower inclusive. (low - ]high
     * @param x Number to wrap.
     * @param lowBounds lower boundary; must be <= n2
     * @param hiBounds upper boundary; must be >= n1
     */
    template <typename T>
    inline T WrapF(T x, T lowBounds, T hiBounds)
    {
        static_assert(std::is_floating_point_v<T>, "type T must be floating point");
        if (lowBounds > hiBounds)
            Swap(lowBounds, hiBounds);

        return ModF(x - lowBounds, hiBounds - lowBounds) + lowBounds;
    }

    /**
     * Return a number that 'wraps around' to the opposite boundary when either boundary is exceeded.
     * Used with integral numbers.
     * Upper boundary is exclusive, and lower inclusive. (low - ]high
     * @param x Number to wrap.
     * @param lowBounds lower boundary; must be <= n2
     * @param hiBounds upper boundary; must be >= n1
     */
    template <typename T>
    inline T Wrap(T x, T lowBounds, T hiBounds)
    {
        static_assert(std::is_integral_v<T>, "type T must be floating point");
        if (lowBounds > hiBounds)
            Swap(lowBounds, hiBounds);

        return Mod(x - lowBounds, hiBounds - lowBounds) + lowBounds;
    }

    /// Gets the angle between an origal x1, y1 point and another at x2, y2
    float PointDirection(float x1, float y1, float x2, float y2);
    float PointDistance(float x1, float y1, float x2, float y2);
}
