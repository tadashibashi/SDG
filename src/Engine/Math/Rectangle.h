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
        [[nodiscard]] inline auto X() const noexcept { return x; }
        /// Sets the horizontal position of the rectangle.
        inline Rect_ &X(T pX) noexcept { x = pX; return *this; }

        /// Gets the vertical position of the rectangle.
        [[nodiscard]] inline auto Y() const noexcept { return y; }
        /// Sets the vertical position of the rectangle.
        inline Rect_ &Y(T pY) noexcept { y = pY; return *this; }

        /// Gets the width of the rectangle.
        [[nodiscard]] inline auto Width() const noexcept { return w; }
        /// Sets the width of the rectangle.
        inline Rect_ &Width(T pW) { w = pW; return *this; }

        /// Gets the height of the rectangle.
        [[nodiscard]] inline auto Height() const noexcept { return h; }
        /// Sets the height of the rectangle.
        inline Rect_ &Height(T pH) noexcept { h = pH; return *this; }

        /// Sets the members of the rectangle.
        Rect_ &Set(T pX, T pY, T width, T height) noexcept;

        Vec2_<T> Position() const noexcept { return { x, y }; }
        Rect_ &Position(T pX, T pY) noexcept { x = pX, y = pY; return *this; }

        /// Returns whether the rectangle is empty (zero area)
        [[nodiscard]] bool Empty() const noexcept;
        /// Returns the dimensions of the rectangle as a vec2
        [[nodiscard]] auto Size() const noexcept -> Vec2_<T> { return {w, h}; }

        auto Size(Vec2_<T> size) noexcept -> Rect_ & { w = size.X(); h = size.Y(); return *this; }
        /// Gets the area of the rectangle (width x height)
        [[nodiscard]] auto Area() const noexcept -> T { return w * h; }

        /// Gets the length of the diagonal distance from one opposite corner to another
        [[nodiscard]] auto Diagonal() const noexcept -> double { return Math::Sqrt(double(w * w + h * h)); }

        /// Gets the horizontal position of the rectangle's left side.
        [[nodiscard]] auto Left() const noexcept -> T { return x; }
        /// Sets the horizontal position of the rectangle's left side.
        /// It cannot exceed the right side, and will be limited by it.
        auto Left(T left) noexcept -> Rect_ &;

        /// Gets the horizontal position of the rectangle's right side.
        [[nodiscard]] auto Right() const noexcept -> T { return x + w; }
        /// Sets the horizontal position of the rectangle's right side.
        /// It cannot cross the left side, and will be limited by it.
        auto Right(T right) noexcept -> Rect_ &;

        /// Gets the vertical position of the rectangle's top.
        [[nodiscard]] auto Top() const noexcept -> T { return y; }

        /// Sets the position of the rectangle's top.
        /// It cannot cross the bottom side, and will be limited by it.
        auto Top(T top) noexcept -> Rect_ &;

        /// Gets the vertical position of the rectangle's bottom side.
        [[nodiscard]] auto Bottom() const noexcept -> T { return y + h; }

        /// Sets the position of the rectangle's bottom.
        /// It cannot cross the top side, and will be limited by it.
        auto Bottom(T bottom) noexcept -> Rect_ &;

        /// Gets the position of the rectangle's top-left corner.
        [[nodiscard]] auto LeftTop() const noexcept -> Vec2_<T>;

        /// Sets the position of the rectangle's top-left corner.
        auto LeftTop(Vec2_<T> v) noexcept -> Rect_<T> &;

        /// Gets the position of the rectangle's top-right corner.
        [[nodiscard]] auto RightTop() const noexcept -> Vec2_<T>;

        /// Sets the position of the rectangle's top-right corner.
        auto RightTop(Vec2_<T> v) noexcept -> Rect_<T> &;

        /// Gets the position of the rectangle's bottom-left corner.
        [[nodiscard]] auto LeftBottom() const noexcept -> Vec2_<T>;
        /// Sets the position of the rectangle's bottom-left corner.
        auto LeftBottom(Vec2_<T> v) noexcept -> Rect_<T> &;

        /// Gets the position of the rectangle's bottom-right corner.
        [[nodiscard]] auto RightBottom() const noexcept -> Vec2_<T>;
        /// Sets the position of the rectangle's bottom-right corner.
        auto RightBottom(Vec2_<T> v) noexcept -> Rect_<T> &;

        /// Creates a string representation of the rectangle.
        [[nodiscard]] auto Str() const noexcept -> String;

        [[nodiscard]] auto operator==(const Rect_ &other) const noexcept -> bool;
        [[nodiscard]] auto operator!=(const Rect_ &other) const noexcept -> bool;

        // Convertible by casting to other _Rect types.
        // Please be aware of the effects of automatic numeric type casting.
        template<typename U>
        explicit operator Rect_<U>() const noexcept;

    private:
        // data members
        T x, y, w, h;
    };
}

#include "Rectangle.inl"