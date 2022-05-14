#pragma once
#include <type_traits>
#include <cmath>
#include <string>
#include <ostream>

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

        T &operator[](int i)
        {
            return *(&x + i);
        }

        T X() const { return x; }
        T Y() const { return y; }
        T W() const { return w; }
        T H() const { return h; }

        void X(T pX) { x = pX; }
        void Y(T pY) { y = pY; }
        void W(T pW) { w = pW; }
        void H(T pH) { h = pH; }

        Vec2_ &Set(T pX, T pY)
        {
            x = pX;
            y = pY;
            return *this;
        }

        [[nodiscard]] static constexpr Vec2_ One() { return Vec2_(1, 1); }
        [[nodiscard]] static constexpr Vec2_ Zero() { return Vec2_(0, 0); }

        // Gets the distance between two vectors
        [[nodiscard]] static float Distance(const Vec2_ &p1, const Vec2_ &p2)
        {
            float a = static_cast<float>(p1.x) - static_cast<float>(p2.x);
            float b = static_cast<float>(p1.y) - static_cast<float>(p2.y);

            return std::sqrt(a * a + b * b);
        }

        // Returns a rotated point around {0, 0} anchor
        static Vec2_ Rotate(const Vec2_ &v, float angle)
        {
            return Vec2_((T)(v.x * std::cos(angle) - v.y * std::sin(angle)),
                         (T)(v.x * std::sin(angle) + v.y * std::cos(angle)));
        }

        // Distance from zero.
        [[nodiscard]] float Length() const
        {
            return std::sqrt((float)(x * x + y * y));
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

        // Formats Vec2_ as string: "{x, y}"
        [[nodiscard]] std::string String() const
        {
            return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
        }

        // Math operators
        template <typename U>
        Vec2_ &operator+=(const Vec2_<U> &other)
        {
            x += other.X();
            y += other.Y();
            return *this;
        }

        template <typename U>
        Vec2_ &operator-=(const Vec2_<U> &other)
        {
            x -= other.X();
            y -= other.Y();
            return *this;
        }

        template <typename U>
        Vec2_ &operator*=(const Vec2_<U> &other)
        {
            x *= other.X();
            y *= other.Y();
            return *this;
        }

        template <typename U>
        Vec2_ &operator/=(const Vec2_<U> &other)
        {
            x /= other.X();
            y /= other.Y();
            return *this;
        }

        template <typename U>
        Vec2_ &operator*=(const U scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        template <typename U>
        Vec2_ &operator/=(const U scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        bool operator==(const Vec2_ &other) const
        {
            return (x == other.X() && y == other.Y());
        }

        bool operator!=(const Vec2_ &other) const
        {
            return !operator==(other);
        }

        template <typename U>
        explicit operator Vec2_<U>()
        {
            static_assert(
                    std::is_convertible_v<T, U>,
                    "Type mismatch. Vec2_ operand types T and U must have convertible types");
            return Vec2_<U>(
                    static_cast<U>(x),
                    static_cast<U>(y));
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Vec2_<T> &v)
    {
        out << "{" << std::to_string(v.X()) << ", " << std::to_string(v.Y()) << "}";
        return out;
    }

    template <typename T, typename U>
    Vec2_<T> operator+(Vec2_<T> a, Vec2_<U> b)
    {
        Vec2_<T> temp(a);
        return temp += b;
    }

    template <typename T, typename U>
    Vec2_<T> operator-(const Vec2_<T> a, const Vec2_<U> b)
    {
        Vec2_<T> temp(a);
        return temp -= b;
    }

    template <typename T, typename U>
    Vec2_<T> operator*(const Vec2_<T> a, const Vec2_<U> b)
    {
        Vec2_<T> temp(a);
        return temp *= b;
    }

    template <typename T, typename U>
    Vec2_<T> operator/(const Vec2_<T> a, const Vec2_<U> b)
    {
        Vec2_<T> temp(a);
        return temp /= b;
    }

    template <typename T, typename U>
    Vec2_<T> operator/(const Vec2_<T> v, U scalar)
    {
        static_assert(std::is_arithmetic_v<U>, "Right scalar operand must be an arithmetic type.");
        Vec2_<T> temp(v);
        return temp /= scalar;
    }

    template <typename T, typename U>
    Vec2_<T> operator*(const Vec2_<T> v, U scalar)
    {
        static_assert(std::is_arithmetic_v<U>, "Right scalar operand must be an arithmetic type.");
        Vec2_<T> temp(v);
        return temp *= scalar;
    }

    typedef Vec2_<float> Vector2;
    typedef Vec2_<int>   Point;

    template class Vec2_<float>;
    template class Vec2_<int>;
}
