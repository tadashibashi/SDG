#pragma once
#include <type_traits>
#include <cmath>
#include <string>

namespace SDG
{
    template <typename T>
    class Vec2_
    {
        static_assert(std::is_arithmetic_v<T>, "Vec2_ type T must be arithmetic.");
    public:
        Vec2_() : x(0), y(0) { }
        Vec2_(T x, T y) : x(x), y(y) { }

        union
        {
            struct { T x, y; };
            // Width and Height. Not to be confused with the xyzw paradigm.
            struct { T w, h; };
        };

        // Gets the distance between two vectors
        static float Distance(const Vec2_ &p1, const Vec2_ &p2)
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
        [[nodiscard]] std::string ToString() const
        {
            return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
        }

        // Math operators
        Vec2_ &operator+=(const Vec2_ &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2_ &operator-=(const Vec2_ &other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vec2_ &operator*=(const Vec2_ &other)
        {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        Vec2_ &operator/=(const Vec2_ &other)
        {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        template <typename U>
        Vec2_ &operator*=(const U scalar)
        {
            static_assert(std::is_arithmetic_v<U>, "Right scalar operand must be an arithmetic type.");
            x *= scalar;
            y *= scalar;
            return *this;
        }

        template <typename U>
        Vec2_ &operator/=(const U scalar)
        {
            static_assert(std::is_arithmetic_v<U>, "Right scalar operand must be an arithmetic type.");
            x /= scalar;
            y /= scalar;
            return *this;
        }

        bool operator==(const Vec2_ &other)
        {
            return (x == other.x && y == other.y);
        }

        bool operator!=(const Vec2_ &other)
        {
            return !operator==(other);
        }

        template <typename U>
        explicit operator Vec2_<U>()
        {
            static_assert(
                    std::is_arithmetic_v<U> &&
                    std::is_convertible_v<T, U>,
                    "Type mismatch. Vec2_ operands must hold convertible types");
            return Vec2_<U>(
                    static_cast<U>(x),
                    static_cast<U>(y));
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Vec2_<T> &v)
    {
        out << "{" << std::to_string(v.x) << ", " << std::to_string(v.y) << "}";
        return out;
    }

    template <typename T>
    Vec2_<T> operator+(Vec2_<T> a, Vec2_<T> b)
    {
        Vec2_<T> temp(a);
        return temp += b;
    }

    template <typename T>
    Vec2_<T> operator-(const Vec2_<T> a, const Vec2_<T> b)
    {
        Vec2_<T> temp(a);
        return temp -= b;
    }

    template <typename T>
    Vec2_<T> operator*(const Vec2_<T> a, const Vec2_<T> b)
    {
        Vec2_<T> temp(a);
        return temp *= b;
    }

    template <typename T>
    Vec2_<T> operator/(const Vec2_<T> a, const Vec2_<T> b)
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
