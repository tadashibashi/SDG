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

namespace SDG
{
    const float PI = 3.1415926535897932f;
    const float RAD_TO_DEG = 180.f / PI;
    const float DEG_TO_RAD = PI / 180.f;

    class Math
    {
    public:
        template <typename T>
        static T Lerp(T val, T dest, T amt)
        {
            static_assert(std::is_floating_point_v<T>, "Lerp parameters must be a type of floating point.");
            return (dest - val) * amt + val;
        }

        static Vector2 Lerp(Vector2 val, Vector2 dest, float amt)
        {
            return Vector2(Lerp(val.X(), dest.Y(), amt), Lerp(val.Y(), dest.Y(), amt));
        }

        static Vector2 Transform(Vector2 position, const Matrix4x4 &mat);

        template <typename T>
        static T RadToDeg(T rad)
        {
            static_assert(std::is_floating_point_v<T>, "type T must be a floating point.");
            return rad * RAD_TO_DEG;
        }

        template <typename T>
        static T DegToRad(T degrees)
        {
            static_assert(std::is_floating_point_v<T>, "type T must be a floating point.");
            return degrees * DEG_TO_RAD;
        }

        template <typename T>
        static float TrajectoryX(T degrees, T length)
        {
            static_assert(std::is_floating_point_v<T>, "type T must be a floating point.");
            return std::cos(DegToRad(degrees)) * length;
        }

        template <typename T>
        static float TrajectoryY(T degrees, T length)
        {
            static_assert(std::is_floating_point_v<T>, "type T must be a floating point.");

            // Negative value to match downward y coordinate system
            return -(std::sin(DegToRad(degrees)) * length);
        }

        /**
         * Get the resulting Vector from an angle and length
         * @param degrees
         * @param length
         * @return
         */
        static Vector2 Trajectory(float degrees, float length)
        {
            return Vector2(TrajectoryX(degrees, length), TrajectoryY(degrees, length));
        }

        template <typename T>
        static T Clamp(T value, T min, T max)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            return Max(Min(value, max), min);
        }

        template <typename T>
        static T Min(T a, T b)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            return a < b ? a : b;
        }

        template <typename T>
        static T Min(const std::initializer_list<T> &nums)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            return std::min(nums);
        }

        template <typename T>
        static T Max(T a, T b)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            return a > b ? a : b;
        }

        template <typename T>
        static T Max(const std::initializer_list<T> &nums)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            return std::max(nums);
        }

        template <typename T>
        static T Abs(T n)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            return n < 0 ? -n : n;
        }

        template <typename T>
        static T Sign(T n)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            return (T)(n < 0 ? -1 : 1);
        }

        template <typename T>
        static T Add(std::initializer_list<T> num)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            T total = 0;
            for (auto n: num)
            {
                total += n;
            }

            return total;
        }

        /**
        * Modulo function that does not reflect across 0
        */
        template <typename T>
        static float Mod(T x, T n)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            return (T)fmodf((fmodf((float)x, (float)n) + n), (float)n);
        }

        /**
         * Return a number that 'wraps around' to the opposite boundary when either boundary is exceeded.
         * @param x Number to wrap.
         * @param n1 First boundary; must be less than n2
         * @param n2 Second boundary; must be greater than n1
         */
        template <typename T>
        static T Wrap(T x, T n1, T n2)
        {
            static_assert(std::is_arithmetic_v<T>, "type T must be arithmetic");
            SDG_Assert(n1 < n2);

            return Mod(x - n1, n2 - n1) + n1;
        }

        static Vector2 Wrap(Vector2 val, Vector2 low, Vector2 high)
        {
            return Vector2(Wrap(val.X(), low.X(), high.X()), Wrap(val.Y(), low.Y(), high.Y()));
        }

        static float PointDirection(float x1, float y1, float x2, float y2);

    private:
        /**
         * Returns the quadrant the coordinate is in starting with quadrant zero
         * on the bottom right, going clockwise until quadrant 3 on the top-right.
         * This function is a helper used by point direction
         */
        static int GetQuadrant(float x, float y);

    };
}
