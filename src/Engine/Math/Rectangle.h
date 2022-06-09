/*!
 * @file Rectangle.h
 * @namepspace SDG
 * @class Rect_
 * Represents an axis-aligned rectangle. Templatizable to all numeric types.
 * Two included typedefs are Rectangle (Rect_<int>), and FRectangle
 * (Rect_<float>)
 *
 * Corner names use reversed "LeftTop" instead of normal English "TopLeft",
 * since it is easier to associate [x, y] coord order with the new name order.
 */
#pragma once
#include "Vector2.h"

#include <Engine/Debug/LogImpl.h>
#include <Engine/Lib/String.h>
#include <Engine/Math/Math.h>

namespace SDG
{
    /// Represents an axis-aligned rectangle.
    /// @tparam T Type of the members. Two typedefs that come
    /// with the file are Rectangle (Rect_<int>), and FRectangle (Rect_<float>)
    template <typename T>
    class Rect_
    {
    public:
        Rect_() noexcept : x(0), y(0), w(0), h(0) { }
        Rect_(T x, T y, T width, T height) noexcept :
            x(x), y(y), w(width), h(height) { }
        Rect_(Vec2_<T> pos, Vec2_<T> size) noexcept :
            x(pos.X()), y(pos.Y()), w(size.X()), h(size.Y()) { }
        Rect_(Vec2_<T> pos, T width, T height) noexcept :
            x(pos.X()), y(pos.Y()), w(width), h(height) { }
        Rect_(T x, T y, Vec2_<T> size) noexcept :
            x(x), y(y), w(size.X()), h(size.Y()) { }

        /// Gets the horizontal position of the rectangle.
        [[nodiscard]] T X() const noexcept { return x; }
        /// Sets the horizontal position of the rectangle.
        Rect_ &X(T pX) noexcept { x = pX; return *this; }

        /// Gets the vertical position of the rectangle.
        [[nodiscard]] T Y() const noexcept { return y; }
        /// Sets the vertical position of the rectangle.
        Rect_ &Y(T pY) noexcept { y = pY; return *this; }

        /// Gets the width of the rectangle.
        [[nodiscard]] T Width() const noexcept { return w; }
        /// Sets the width of the rectangle.
        Rect_ &Width(T pW) { w = pW; return *this; }

        /// Gets the height of the rectangle.
        [[nodiscard]] T Height() const noexcept { return h; }
        /// Sets the height of the rectangle.
        Rect_ &Height(T pH) noexcept { h = pH; return *this; }

        /// Sets the members of the rectangle.
        Rect_ &Set(T pX, T pY, T width, T height) noexcept;

        Vec2_<T> Position() const noexcept { return { x, y }; }
        Rect_ &Position(T pX, T pY) noexcept { x = pX, y = pY; return *this; }

        /// Returns whether the rectangle is empty (zero area)
        [[nodiscard]] bool Empty() const noexcept;
        /// Returns the dimensions of the rectangle as a vec2
        [[nodiscard]] Vec2_<T> Size() const noexcept { return {w, h}; }
        Rect_ &Size(Vec2_<T> size) noexcept { w = size.X(); h = size.Y(); return *this; }
        /// Gets the area of the rectangle (width x height)
        [[nodiscard]] T Area() const noexcept { return w * h; }

        /// Gets the length of the diagonal distance from one opposite corner to another
        [[nodiscard]] double Diagonal() const noexcept { return Math::Sqrt(double(w * w + h * h)); }

        /// Gets the horizontal position of the rectangle's left side.
        [[nodiscard]] T Left() const noexcept { return x; }
        /// Sets the horizontal position of the rectangle's left side.
        /// It cannot exceed the right side, and will be limited by it.
        Rect_ &Left(T left) noexcept;

        /// Gets the horizontal position of the rectangle's right side.
        [[nodiscard]] T Right() const noexcept { return x + w; }
        /// Sets the horizontal position of the rectangle's right side.
        /// It cannot cross the left side, and will be limited by it.
        Rect_ &Right(T right) noexcept;

        /// Gets the vertical position of the rectangle's top.
        [[nodiscard]] T Top() const noexcept { return y; }
        /// Sets the horizontal position of the rectangle's top.
        /// It cannot cross the bottom side, and will be limited by it.
        Rect_ &Top(T top) noexcept;

        /// Gets the vertical position of the rectangle's bottom side.
        [[nodiscard]] T Bottom() const noexcept { return y + h; }
        /// Sets the horizontal position of the rectangle's top.
        /// It cannot cross the bottom side, and will be limited by it.
        Rect_ &Bottom(T bottom) noexcept;

        /// Gets the position of the rectangle's top-left corner.
        [[nodiscard]] Vec2_<T> LeftTop() const noexcept;
        /// Sets the position of the rectangle's top-left corner.
        Rect_<T> &LeftTop(Vec2_<T> v) noexcept;

        /// Gets the position of the rectangle's top-right corner.
        [[nodiscard]] Vec2_<T> RightTop() const noexcept;
        /// Sets the position of the rectangle's top-right corner.
        Rect_<T> &RightTop(Vec2_<T> v) noexcept;

        /// Gets the position of the rectangle's bottom-left corner.
        [[nodiscard]] Vec2_<T> LeftBottom() const noexcept;
        /// Sets the position of the rectangle's bottom-left corner.
        Rect_<T> &LeftBottom(Vec2_<T> v) noexcept;

        /// Gets the position of the rectangle's bottom-right corner.
        [[nodiscard]] Vec2_<T> RightBottom() const noexcept;
        /// Sets the position of the rectangle's bottom-right corner.
        Rect_<T> &RightBottom(Vec2_<T> v) noexcept;

        /// Creates a string representation of the rectangle.
        [[nodiscard]] String Str() const noexcept;

        bool operator==(const Rect_ &other) const noexcept;
        bool operator!=(const Rect_ &other) const noexcept;

        // Convertible by casting to other _Rect types.
        // Please be aware of the effects of automatic numeric type casting.
        template<typename U>
        explicit operator Rect_<U>() const noexcept;

    private:
        // data members
        T x, y, w, h;
    };

    template<typename T>
    Rect_<T> &
    Rect_<T>::Set(T pX, T pY, T width, T height) noexcept
    {
        x = pX;
        y = pY;
        w = width;
        h = height;

        return *this;
    }

    template<typename T>
    bool
    Rect_<T>::Empty() const noexcept
    {
        return (w == 0 && h == 0);
    }

    template<typename T>
    Rect_<T> &
    Rect_<T>::Left(T left) noexcept
    {
        T right = Right();
        left = SDG_Min(left, right);

        w = right - left;
        x = left;
        return *this;
    }

    template<typename T>
    Rect_<T> &
    Rect_<T>::Right(T right) noexcept
    {
        T left = Left();
        right = SDG_Max(right, left);

        w = right - left;
        return *this;
    }

    template<typename T>
    Rect_<T> &
    Rect_<T>::Top(T top) noexcept
    {
        T bottom = Bottom();
        top = SDG_Min(top, bottom);

        h = bottom - top;
        y = top;
        return *this;
    }

    template<typename T>
    Rect_<T> &
    Rect_<T>::Bottom(T bottom) noexcept
    {
        T top = Top();
        bottom = SDG_Max(bottom, top);

        h = bottom - top;
        return *this;
    }

    template<typename T>
    Vec2_<T>
    Rect_<T>::LeftTop() const noexcept
    {
        return {Left(), Top()};
    }

    template<typename T>
    Rect_<T> &
    Rect_<T>::LeftTop(Vec2_<T> v) noexcept
    {
        Top(v.Y());
        Left(v.X());
        return *this;
    }

    template<typename T>
    Vec2_<T>
    Rect_<T>::RightTop() const noexcept
    {
        return {Right(), Top()};
    }

    template<typename T>
    Rect_<T> &
    Rect_<T>::RightTop(Vec2_<T> v) noexcept
    {
        Top(v.Y());
        Right(v.X());
        return *this;
    }

    template<typename T>
    Vec2_<T>
    Rect_<T>::LeftBottom() const noexcept
    {
        return Vec2_<T>(Left(), Bottom());
    }

    template<typename T>
    Rect_<T> &
    Rect_<T>::LeftBottom(Vec2_<T> v) noexcept
    {
        Bottom(v.Y());
        Left(v.X());
        return *this;
    }

    template<typename T>
    Vec2_<T>
    Rect_<T>::RightBottom() const noexcept
    {
        return Vec2_<T>(Right(), Bottom());
    }

    template<typename T>
    Rect_<T> &
    Rect_<T>::RightBottom(Vec2_<T> v) noexcept
    {
        Bottom(v.Y());
        Right(v.X());
        return *this;
    }

    template<typename T>
    String
    Rect_<T>::Str() const noexcept
    {
        return "{" + std::to_string(x) + ", " + std::to_string(y) +
               ", " + std::to_string(w) + ", " + std::to_string(h) + "}";
    }

    template<typename T>
    bool
    Rect_<T>::operator==(const Rect_ &other) const noexcept
    {
        return (x == other.x && y == other.y &&
                w == other.w && h == other.h);
    }

    template<typename T>
    bool
    Rect_<T>::operator!=(const Rect_ &other) const noexcept
    {
        return !operator==(other);
    }

    template<typename T>
    template<typename U>
    Rect_<T>::operator Rect_<U>() const noexcept
    {
        return Rect_<U> (
                static_cast<U>(x),
                        static_cast<U>(y),
                        static_cast<U>(w),
                        static_cast<U>(h));
    }


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
