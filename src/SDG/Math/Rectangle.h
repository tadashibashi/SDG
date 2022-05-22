#pragma once
#include "Vector2.h"
#include <SDG/String.h>
#include <SDG/Debug/LoggingImpl.h>

#include <type_traits>

namespace SDG
{
    template <typename T>
    class Rect_
    {
        static_assert(std::is_arithmetic_v<T>, "Rect_ requires an arithmetic template type");
    public:
        Rect_() : x(0), y(0), w(0), h(0) { }
        Rect_(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) { }

        [[nodiscard]]
        T X() const { return x; }

        [[nodiscard]]
        T Y() const { return y; }

        [[nodiscard]]
        T Width() const { return w; }

        [[nodiscard]]
        T Height() const { return h; }

        [[nodiscard]]
        bool Empty() const noexcept
        {
            return (w == 0 && h == 0);
        }

        Rect_ &X(T pX) { x = pX; return *this; }
        Rect_ &Y(T pY) { y = pY; return *this; }
        Rect_ &Width(T pW) { w = pW; return *this; }
        Rect_ &Height(T pH) { h = pH; return *this; }

        Rect_ &Set(T pX, T pY, T width, T height)
        {
            x = pX;
            y = pY;
            w = width;
            h = height;

            return *this;
        }

        [[nodiscard]]
        T Area() const noexcept
        {
            return w * h;
        }

        [[nodiscard]]
        T Left() const noexcept { return x; }
        Rect_ &Left(T left)
        {
            w = Right() - left;
            x = left;
            return *this;
        }

        [[nodiscard]]
        T Right() const noexcept { return x + w; }
        Rect_ &Right(T right)
        {
            w = right - Left();
            return *this;
        }

        [[nodiscard]]
        T Top() const noexcept { return y; }
        Rect_ &Top(T top)
        {
            h = top - Bottom();
            y = top;
            return *this;
        }

        [[nodiscard]]
        T Bottom() const noexcept { return y + h; }
        Rect_ &Bottom(T bottom)
        {
            h = Top() - bottom;
            return *this;
        }

        [[nodiscard]]
        Vec2_<T> Size() const { return {w, h}; }

        [[nodiscard]]
        Vec2_<T> TopLeft() const { return {Left(), Top()}; }
        Rect_<T> &TopLeft(Vec2_<T> v)
        {
            Top(v.Y());
            Left(v.X());
            return *this;
        }

        [[nodiscard]]
        Vec2_<T> TopRight() const { return {Right(), Top()}; }
        Rect_<T> &TopRight(Vec2_<T> v)
        {
            Top(v.Y());
            Right(v.X());
            return *this;
        }

        [[nodiscard]]
        Vec2_<T> BottomLeft() const { return Vec2_<T>(Left(), Bottom()); }
        Rect_<T> &BottomLeft(Vec2_<T> v)
        {
            Bottom(v.Y());
            Left(v.X());
            return *this;
        }

        [[nodiscard]]
        Vec2_<T> BottomRight() const { return Vec2_<T>(Right(), Bottom()); }
        Rect_<T> &BottomRight(Vec2_<T> v)
        {
            Bottom(v.Y());
            Right(v.X());
            return *this;
        }

        [[nodiscard]]
        String Str() const noexcept
        {
            return "{" + std::to_string(x) + ", " + std::to_string(y) +
                ", " + std::to_string(w) + ", " + std::to_string(h) + "}";
        }

        bool operator==(const Rect_ &other)
        {
            return (x == other.x && y == other.y &&
                    w == other.w && h == other.h);
        }

        bool operator!=(const Rect_ &other)
        {
            return !operator==(other);
        }

        // Convertible by casting to other _Rect types. Please be aware of the effects of automatic type casting.
        template<typename U>
        explicit operator Rect_<U>()
        {
            static_assert(std::is_convertible_v<U, T>, "Rectangle type mismatch.");
            return Rect_<U> (
                    static_cast<U>(x),
                    static_cast<U>(y),
                    static_cast<U>(w),
                    static_cast<U>(h));
        }

    private:
        // data members
        T x, y, w, h;
    };

    template <typename Ostream, typename T>
    Ostream &operator << (Ostream &out, const Rect_<T> &v)
    {
        out << "{" << std::to_string(v.X()) << ", " << std::to_string(v.Y()) <<
            ", " << std::to_string(v.Width()) << ", " << std::to_string(v.Height()) << "}";
        return out;
    }

    typedef Rect_<float> FRectangle;
    typedef Rect_<int>   Rectangle;

    template class Rect_<float>;
    template class Rect_<int>;
}
