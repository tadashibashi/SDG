/*!
 * @file Math.h
 * Contains a group of math helper functions under the SDG::Math namespace.
 * For pseudo-random number generation, please look at Rand.h
 *
 */
#pragma once
#include <SDG/Templates/Swap.h>
#include "MathConstants.h"

namespace SDG::Math
{
    /// Linear interpolation. Requires floating point for accuracy, but
    /// integer types are usable with a floored result.
    template <typename T>
    inline T Lerp(T val, T dest, double amt)
    {
        return (dest - val) * amt + val;
    }

    inline double ToDegrees(double rad)
    {
        return rad * DegsPerRad;
    }

    inline double ToRadians(double degrees)
    {
        return degrees * RadsPerDeg;
    }

    /// Returns the Y value from a projected position.
    double TrajectoryX(double degrees, double length);

    /// Returns the Y value from a projected position.
    double TrajectoryY(double degrees, double length);

    /// Returns the largest of two numbers.
    template <typename T>
    inline T Min(T a, T b)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        return a < b ? a : b;
    }

    /// Returns the largest of two numbers.
    template <typename T>
    inline T Max(T a, T b)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        return a > b ? a : b;
    }


    /// Constrains a value between two numbers, inclusively on both ends.
    /// Min may be greater than max, and the number will still be clamped
    /// between by both ends.
    template <typename T>
    inline T Clamp(T value, T min, T max)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");

        // Protect case where min > max
        if (min > max)
            Swap(min, max);

        return Max(Min(value, max), min);
    }

    /// Returns the absolute value of a number
    template <typename T>
    inline T Abs(T n)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        return n < 0 ? -n : n;
    }

    /// Returns +1 on positive number or 0, and -1 on negative numbers
    template <typename T>
    inline T Sign(T n)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        return (T)(n < 0 ? -1 : 1);
    }

    /// Adds a list of numbers
    template <typename T>
    inline T Add(std::initializer_list<T> num)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        T total = 0;
        for (auto n: num)
        {
            total += n;
        }

        return total;
    }

    template <typename T>
    T Round(T n)
    {
        static_assert(std::is_arithmetic_v<T>,
                      "must be arithmetic type to perform Math::Round");

        return (T)((int)( (long double)n + 0.5L ));
    }

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

    /**
    * Modulo function for floating point types that does not reflect across 0
    */
    double ModF(double x, double n);

    /// Modulo function for integral types that does not reflect across 0
    long Mod(long x, long n);

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
