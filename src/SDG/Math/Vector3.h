#pragma once
#include <cmath>
#include <string>
#include <ostream>
#include <SDG/Exceptions/InvalidArgumentException.h>
#include <SDG/Exceptions/OutOfRangeException.h>

namespace SDG
{
    template <typename T>
    class  Vec3_
    {
        static_assert(std::is_arithmetic_v<T>, "Vec3_ template type must be an arithmetic type");
        struct { T x, y, z; };
    public:
        constexpr Vec3_() : x(0), y(0), z(0) { }
        constexpr Vec3_(T x, T y, T z) : x(x), y(y), z(z) { }

        [[nodiscard]] T X() const { return x; }
        [[nodiscard]] T Y() const { return y; }
        [[nodiscard]] T Z() const { return z; }
        Vec3_ &X(T pX) { x = pX; return *this; }
        Vec3_ &Y(T pY) { y = pY; return *this; }
        Vec3_ &Z(T pZ) { z = pZ; return *this; }

        Vec3_ &Set(T pX, T pY, T pZ)
        {
            x = pX;
            y = pY;
            z = pZ;
            return *this;
        }

        T &operator[](int i)
        {
            if (i < 0 || i > 2)
                throw OutOfRangeException(i, "Vector3 indexer must be 0, 1, or 2");
            return *(&x + i);
        }

        [[nodiscard]] static constexpr Vec3_ One() { return Vec3_(1, 1, 1); }
        [[nodiscard]] static constexpr Vec3_ Zero() { return Vec3_(0, 0, 0); }

        // Formats Vec3_ as string: "{x, y, z}"
        [[nodiscard]] std::string String() const
        {
            return "{" + std::to_string(x) + ", " + std::to_string(y) +
                ", " + std::to_string(z) + "}";
        }

        [[nodiscard]] static double Distance(const Vec3_ &p1, const Vec3_ &p2)
        {
            double a = static_cast<double>(p1.x) - static_cast<double>(p2.x);
            double b = static_cast<double>(p1.y) - static_cast<double>(p2.y);
            double c = static_cast<double>(p1.z) - static_cast<double>(p2.z);

            return std::sqrt(a * a + b * b + c * c);
        }

        // Distance from {0, 0, 0}
        [[nodiscard]] double Length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        // Only applicable if template type is a decimal/floating-point type.
        Vec3_ &Normalize()
        {
            double length = this->Length();
            if (length != 0)
            {
                x /= length;
                y /= length;
                z /= length;
            }

            return *this;
        }

        template <typename U>
        Vec3_ &operator+=(const Vec3_<U> &other)
        {
            x += other.X();
            y += other.Y();
            z += other.Z();
            return *this;
        }

        template <typename U>
        Vec3_ &operator-=(const Vec3_<U> &other)
        {
            x -= other.X();
            y -= other.Y();
            z -= other.Z();
            return *this;
        }

        template <typename U>
        Vec3_ &operator*=(const Vec3_<U> &other)
        {
            x *= other.X();
            y *= other.Y();
            z *= other.Z();
            return *this;
        }

        template <typename U>
        Vec3_ &operator/=(const Vec3_<U> &other)
        {
            if (other.X() == 0 || other.Y() == 0 || other.Z() == 0)
                throw InvalidArgumentException("Vec3_::operator/=(const Vec3_<U> other)",
                                           "other", "results in division by zero");
            x /= other.X();
            y /= other.Y();
            z /= other.Z();
            return *this;
        }

        [[nodiscard]] bool operator==(const Vec3_ &other) const
        {
            return (x == other.X() &&
                    y == other.Y() &&
                    z == other.Z());
        }

        [[nodiscard]] bool operator!=(const Vec3_ &other) const
        {
            return !(*this == other);
        }

        template <typename U>
        Vec3_ &operator*=(const U scalar)
        {
            static_assert(std::is_arithmetic_v<U>, "Scalar type must be arithmetic");
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        template <typename U>
        Vec3_ &operator/=(const U scalar)
        {
            static_assert(std::is_arithmetic_v<U>, "Scalar type must be arithmetic");
            if (scalar == 0)
                throw InvalidArgumentException("Vec3_::operator/=(const U scalar)",
                                               "scalar", "results in division by zero");
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        template <typename U>
        [[nodiscard]] explicit operator Vec3_<U>()
        {
            static_assert(std::is_arithmetic_v<U> && std::is_convertible_v<T, U>, "Vec3_ type mismatch");
            return Vec3_<U>(
                    static_cast<U>(x),
                    static_cast<U>(y),
                    static_cast<U>(z));
        }
    };

    template <typename T, typename U>
    [[nodiscard]] Vec3_<T> operator+(Vec3_<T> a, Vec3_<U> b)
    {
        return Vec3_<T>(a) += b;
    }

    template <typename T, typename U>
    [[nodiscard]] Vec3_<T> operator-(const Vec3_<T> a, const Vec3_<U> b)
    {
        return Vec3_<T>(a) -= b;
    }

    template <typename T, typename U>
    [[nodiscard]] Vec3_<T> operator*(const Vec3_<T> a, const Vec3_<U> b)
    {
        return Vec3_<T>(a) *= b;
    }

    template <typename T, typename U>
    [[nodiscard]] Vec3_<T> operator/(const Vec3_<T> a, const Vec3_<U> b)
    {
        return Vec3_<T>(a) /= b;
    }

    template <typename T, typename U>
    [[nodiscard]] Vec3_<T> operator/(const Vec3_<T> v, U scalar)
    {
        static_assert(std::is_arithmetic_v<U>, "Scalar type must be arithmetic");
        return Vec3_<T>(v) /= scalar;
    }

    template <typename T, typename U>
    [[nodiscard]] Vec3_<T> operator*(const Vec3_<T> v, U scalar)
    {
        static_assert(std::is_arithmetic_v<U>, "Scalar type must be arithmetic");
        return Vec3_<T>(v) *= scalar;
    }

    template <typename T>
    std::ostream &operator << (std::ostream &os, const Vec3_<T> v)
    {
        os << v.String();
        return os;
    }

    typedef Vec3_<float> Vector3;
    typedef Vec3_<int>   Point3;

    template class Vec3_<float>;
    template class Vec3_<int>;
}
