/* =============================================================================
 * Math
 *
 *
 * ===========================================================================*/
#pragma once
#include "Vector2.h"
#include "Matrix4x4.h"
#include <SDG/Debug.hpp>

#include <cmath>
#include <initializer_list>
#include <algorithm>

// Just in case there is some macro that clashes
#ifdef Pi
#undef Pi
#endif

namespace SDG::Math
{
    const double Pi = 3.1415926535897932;
    /// Multiply Radians by this to get Degrees.
    const double DegsPerRad = 180.0 / Pi;
    /// Multiply Degrees by this to get Radians.
    const double RadsPerDeg = Pi / 180.0;

    /// Linear interpolation. Requires floating point for accuracy, but
    /// integer types are usable with a floored result.
    template <typename T>
    inline T Lerp(T val, T dest, double amt)
    {
        return (dest - val) * amt + val;
    }

    /// Linear interpolation
    /// @tparam T requires floating point for accuracy, although integers will work, but get floored.
    /// @param val the Vec2 to work with
    /// @param dest the target destination
    /// @param amt the amount to lerp by as a percentage (0 to 1.f)
    template <>
    Vector2 Lerp(Vector2 val, Vector2 dest, double amt);

    Vector2 Transform(Vector2 position, const Matrix4x4 &mat);

    inline double RadToDeg(double rad)
    {
        return rad * DegsPerRad;
    }

    inline double DegToRad(double degrees)
    {
        return degrees * RadsPerDeg;
    }

    /// Returns the Y value from a projected position.
    template <typename T>
    inline T TrajectoryX(T degrees, T length)
    {
        static_assert(std::is_floating_point_v<T>, "type T must be a floating point.");
        return std::cos(DegToRad(degrees)) * length;
    }

    /// Returns the Y value from a projected position.
    template <typename T>
    inline T TrajectoryY(T degrees, T length)
    {
        static_assert(std::is_floating_point_v<T>, "type T must be a floating point.");

        // Negative value to match downward y coordinate system
        return -(std::sin(DegToRad(degrees)) * length);
    }

    /**
     * Get the resulting Vector from an angle and length.
     * If an integer type is used, the result will be floored, and won't be precise.
     * @param degrees
     * @param length
     * @return
     */
    template <typename T>
    inline Vec2_<T> Trajectory(T degrees, T length)
    {
        return Vec2_<T>(TrajectoryX(degrees, length), TrajectoryY(degrees, length));
    }

    /// Returns the smallest of two numbers.
    template <typename T>
    inline T Min(T a, T b)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        return a < b ? a : b;
    }

    /// Returns the smallest value from a list of numbers.
    template <typename T>
    inline T Min(const std::initializer_list<T> &nums)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        return std::min(nums);
    }

    /// Returns the largest of two numbers.
    template <typename T>
    inline T Max(T a, T b)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        return a > b ? a : b;
    }

    /// Returns the largest number from a list.
    template <typename T>
    inline T Max(const std::initializer_list<T> &nums)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        return std::max(nums);
    }

    /// Constrains a value between two numbers, inclusively on both ends.
    /// min value must be smaller or equal to max.
    template <typename T>
    inline T Clamp(T value, T min, T max)
    {
        static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
        SDG_Assert(min <= max);
        return Max(Min(value, max), min);
    }

    template <>
    inline Vector2 Clamp(Vector2 value, Vector2 min, Vector2 max)
    {
        SDG_Assert(min.X() <= max.X());
        SDG_Assert(min.Y() <= max.Y());

        return {Clamp(value.X(), min.X(), max.X()),
                Clamp(value.Y(), min.Y(), max.Y())};
    }

    template <>
    inline Point Clamp(Point value, Point min, Point max)
    {
        SDG_Assert(min.X() <= max.X());
        SDG_Assert(min.Y() <= max.Y());

        return {Clamp(value.X(), min.X(), max.X()),
                Clamp(value.Y(), min.Y(), max.Y())};
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

    /// Adds a container of numbers
    template <typename Iterator>
    inline double Add(Iterator begin, Iterator end)
    {
        double total = 0;
        for (Iterator it = begin; it != end; ++it) total += *it;
        return total;
    }

    /**
    * Modulo function for floating point types that does not reflect across 0
    */
    template <typename T>
    inline T ModF(T x, T n)
    {
        static_assert(std::is_floating_point_v<T>, "T must be floating point type");
        if (n == 0) return 0;
        return (T)fmod((fmod(x, n) + n), n);
    }

    /// Modulo function for integral types that does not reflect across 0
    template <typename T>
    inline T Mod(T x, T n)
    {

        static_assert(std::is_integral_v<T>, "T must be integral type");
        if (n == 0) return 0;
        return (((x % n) + n) % n);
    }

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
        SDG_Assert(lowBounds <= hiBounds);

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
        SDG_Assert(lowBounds <= hiBounds);

        return Mod(x - lowBounds, hiBounds - lowBounds) + lowBounds;
    }

    template <>
    inline Vector2 WrapF(Vector2 val, Vector2 low, Vector2 high)
    {
        return Vector2(WrapF(val.X(), low.X(), high.X()), WrapF(val.Y(), low.Y(), high.Y()));
    }

    template <>
    inline Point Wrap(Point val, Point low, Point high)
    {
        return Point(Wrap(val.X(), low.X(), high.X()), Wrap(val.Y(), low.Y(), high.Y()));
    }

    /// Gets the angle between an origal x1, y1 point and another at x2, y2
    inline float PointDirection(float x1, float y1, float x2, float y2);
}
