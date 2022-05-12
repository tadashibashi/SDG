#pragma once
#include <cmath>
#include <string>

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

        T X() const { return x; }
        T Y() const { return y; }
        T Z() const { return z; }
        void X(T pX) { x = pX; }
        void Y(T pY) { x = pY; }
        void Z(T pZ) { x = pZ; }

        T &operator[](int i)
        {
            return *(&x + i);
        }

        static constexpr Vec3_ One() { return Vec3_(1, 1, 1); }
        static constexpr Vec3_ Zero() { return Vec3_(0, 0, 0); }

        // Formats Vec3_ as string: "{x, y, z}"
        [[nodiscard]] std::string String() const
        {
            return "{" + std::to_string(x) + ", " + std::to_string(y) +
                ", " + std::to_string(z) + "}";
        }

        static double Distance(const Vec3_ &p1, const Vec3_ &p2)
        {
            double a = static_cast<double>(p1.x) - static_cast<double>(p2.x);
            double b = static_cast<double>(p1.y) - static_cast<double>(p2.y);
            double c = static_cast<double>(p1.z) - static_cast<double>(p2.z);

            return std::sqrt(a * a + b * b + c * c);
        }

        // Distance from zero.
        double Length()
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        // Only applicable if template type is a decimal/floating-point type.
        void Normalize()
        {
            double length = this->Length();
            if (length != 0)
            {
                x /= length;
                y /= length;
                z /= length;
            }
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
            x /= other.X();
            y /= other.Y();
            z /= other.Z();
            return *this;
        }

        bool operator==(const Vec3_ &other) const
        {
            return (x == other.X() &&
                    y == other.Y() &&
                    z == other.Z());
        }

        bool operator!=(const Vec3_ &other) const
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
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        template <typename U>
        explicit operator Vec3_<U>()
        {
            static_assert(std::is_arithmetic_v<U> && std::is_convertible_v<T, U>, "Vec3_ type mismatch");
            return Vec3_<U>(
                    static_cast<U>(x),
                    static_cast<U>(y),
                    static_cast<U>(z));
        }
    };

    template <typename T, typename U>
    Vec3_<T> operator+(Vec3_<T> a, Vec3_<U> b)
    {
        return a += b;
    }

    template <typename T, typename U>
    Vec3_<T> operator-(const Vec3_<T> a, const Vec3_<U> b)
    {
        return a -= b;
    }

    template <typename T, typename U>
    Vec3_<T> operator*(const Vec3_<T> a, const Vec3_<U> b)
    {
        return a *= b;
    }

    template <typename T, typename U>
    Vec3_<T> operator/(const Vec3_<T> a, const Vec3_<U> b)
    {
        return a /= b;
    }

    template <typename T, typename U>
    Vec3_<T> operator/(const Vec3_<T> v, U scalar)
    {
        static_assert(std::is_arithmetic_v<U>, "Scalar type must be arithmetic");
        return v /= scalar;
    }

    template <typename T, typename U>
    Vec3_<T> operator*(const Vec3_<T> v, U scalar)
    {
        static_assert(std::is_arithmetic_v<U>, "Scalar type must be arithmetic");
        return v *= scalar;
    }

    typedef Vec3_<float> Vector3;
    typedef Vec3_<int>   Point3;

    template class Vec3_<float>;
    template class Vec3_<int>;
}
