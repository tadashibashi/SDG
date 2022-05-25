#pragma once
#include "Math.h"

#include <SDG/Debug/LogImpl.h>
#include <SDG/Exceptions/InvalidArgumentException.h>
#include <SDG/Exceptions/OutOfRangeException.h>
#include <SDG/String.h>

#include <type_traits>

namespace SDG
{
    template <typename T>
    class Vec2_
    {
        static_assert(std::is_arithmetic_v<T>, "Vec2_ type T must be arithmetic.");
        union
        {
            struct { T x, y; };
            // Width and Height. Not to be confused with the xyzw paradigm.
            struct { T w, h; };
        };

    public:
        constexpr Vec2_() : x(0), y(0) { }
        constexpr Vec2_(T x, T y) : x(x), y(y) { }

        [[nodiscard]]
        T &operator[](unsigned i)
        {
            switch(i)
            {
                case 0: return x;
                case 1: return y;
                default:
                    throw OutOfRangeException(i,
                      "Vector2 indexers may only be 0 or 1");
            }
        }

        [[nodiscard]] T X() const { return x; }
        [[nodiscard]] T Y() const { return y; }
        [[nodiscard]] T W() const { return w; }
        [[nodiscard]] T H() const { return h; }

        Vec2_ &X(T pX) { x = pX; return *this; }
        Vec2_ &Y(T pY) { y = pY; return *this; }
        Vec2_ &W(T pW) { w = pW; return *this; }
        Vec2_ &H(T pH) { h = pH; return *this; }

        Vec2_ &Set(T pX, T pY)
        {
            x = pX;
            y = pY;
            return *this;
        }

        [[nodiscard]]
        static constexpr Vec2_ One() { return Vec2_(1, 1); }
        [[nodiscard]]
        static constexpr Vec2_ Zero() { return Vec2_(0, 0); }

        // Returns a rotated point around {0, 0} anchor
        [[nodiscard]]
        static Vec2_ Rotate(const Vec2_ &v, float degrees)
        {
            float rads = degrees * Math::RadsPerDeg;
            float cosRads = Math::Cos(rads);
            float sinRads = Math::Sin(rads);
            return {(T)(v.x * cosRads - v.y * sinRads),
                         (T)(v.x * sinRads + v.y * cosRads)};
        }

        // Distance from zero.
        [[nodiscard]]
        float Length() const
        {
            return Math::Sqrt((float)(x * x + y * y));
        }

        // Scales x and y so that it totals 1 in length
        // (Only applicable on floating-point types)
        Vec2_ &Normalize()
        {
            T length = (T)this->Length();
            if (length != 0)
            {
                x /= length;
                y /= length;
            }
            return *this;
        }

        Vec2_ Normal() const
        {
            return Vec2_(*this).Normalize();
        }

        // Formats Vec2_ as string: "{x, y}"
        [[nodiscard]]
        String Str() const
        {
            return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
        }

        // Math operators
        template <typename U>
        Vec2_ &operator += (const Vec2_<U> &other)
        {
            x += other.X();
            y += other.Y();
            return *this;
        }

        template <typename U>
        Vec2_ &operator -= (const Vec2_<U> &other)
        {
            x -= other.X();
            y -= other.Y();
            return *this;
        }

        template <typename U>
        Vec2_ &operator *= (const Vec2_<U> &other)
        {
            x *= other.X();
            y *= other.Y();
            return *this;
        }

        template <typename U>
        Vec2_ &operator /= (const Vec2_<U> &other)
        {
            if (other.X() == 0 || other.Y() == 0)
                throw InvalidArgumentException(
                    "Vec2_::operator/=(Vec2_ other)",
                    "other", "division by zero");
            x /= other.X();
            y /= other.Y();
            return *this;
        }

        template <typename U>
        Vec2_ &operator *= (const U scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        template <typename U>
        Vec2_ &operator /= (const U scalar)
        {
            if (scalar == 0)
                throw InvalidArgumentException("Vec2_::operator/=(U scalar)",
                                               "scalar", "division by zero");
            x /= scalar;
            y /= scalar;
            return *this;
        }

        [[nodiscard]]
        bool operator == (const Vec2_ &other) const
        {
            return (x == other.X() && y == other.Y());
        }

        [[nodiscard]]
        bool operator != (const Vec2_ &other) const
        {
            return !operator==(other);
        }

        Vec2_ &operator -()
        {
            x = -x;
            y = -y;
            return *this;
        }

        template <typename U>
        [[nodiscard]] explicit operator Vec2_<U>()
        {
            static_assert(
                    std::is_convertible_v<T, U>,
                    "Type mismatch. Vec2_ operand types T and U must have "
                    "convertible types");
            return Vec2_<U>(
                    static_cast<U>(x),
                    static_cast<U>(y));
        }
    };

    template <typename U, typename Ostream>
    Ostream &operator << (Ostream &out, const Vec2_<U> &v)
    {
        out << v.Str();
        return out;
    }

    template <typename T, typename U>
    [[nodiscard]] Vec2_<T> operator+(Vec2_<T> a, Vec2_<U> b)
    {
        return Vec2_<T>(a) += b;
    }

    template <typename T, typename U>
    [[nodiscard]] Vec2_<T> operator-(const Vec2_<T> a, const Vec2_<U> b)
    {
        return Vec2_<T>(a) -= b;
    }

    template <typename T, typename U>
    [[nodiscard]] Vec2_<T> operator*(const Vec2_<T> a, const Vec2_<U> b)
    {
        return Vec2_<T>(a) *= b;
    }

    /// Divides a Vec2_ by a Vec2_.
    /// Throws SDG::InvalidArgumentException if any division by zero.
    template <typename T, typename U>
    [[nodiscard]] Vec2_<T> operator/(const Vec2_<T> a, const Vec2_<U> b)
    {
        return Vec2_<T>(a) /= b;
    }

    /// Divides a Vec2_ by a scalar.
    /// Throws SDG::InvalidArgumentException if division by zero.
    template <typename T, typename U>
    [[nodiscard]] Vec2_<T> operator/(const Vec2_<T> v, U scalar)
    {
        static_assert(std::is_arithmetic_v<U>,
                "Right scalar operand must be an arithmetic type.");

        Vec2_<T> temp(v);
        return (temp /= scalar);
    }

    template <typename T, typename U>
    [[nodiscard]] Vec2_<T> operator*(const Vec2_<T> v, U scalar)
    {
        static_assert(std::is_arithmetic_v<U>,
                "Right scalar operand must be an arithmetic type.");
        Vec2_<T> temp(v);
        return (temp *= scalar);
    }

    typedef Vec2_<float> Vector2;
    typedef Vec2_<int>   Point;

    template class Vec2_<float>;
    template class Vec2_<int>;
}
