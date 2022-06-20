#include "Rectangle.h"

namespace SDG
{
    template<typename T>
    auto Rect_<T>::Set(T pX, T pY, T width, T height) noexcept -> Rect_<T> &
    {
        x = pX;
        y = pY;
        w = width;
        h = height;

        return *this;
    }

    template<typename T>
    auto Rect_<T>::Empty() const noexcept -> bool
    {
        return (w == 0 && h == 0);
    }

    template<typename T>
    auto Rect_<T>::Left(T left) noexcept -> Rect_<T> &
    {
        T right = Right();
        left = SDG_Min(left, right);

        w = right - left;
        x = left;
        return *this;
    }

    template<typename T>
    auto Rect_<T>::Right(T right) noexcept -> Rect_<T> &
    {
        T left = Left();
        right = SDG_Max(right, left);

        w = right - left;
        return *this;
    }

    template<typename T>
    auto Rect_<T>::Top(T top) noexcept -> Rect_<T> &
    {
        T bottom = Bottom();
        top = SDG_Min(top, bottom);

        h = bottom - top;
        y = top;
        return *this;
    }

    template<typename T>
    auto Rect_<T>::Bottom(T bottom) noexcept -> Rect_<T> &
    {
        T top = Top();
        bottom = SDG_Max(bottom, top);

        h = bottom - top;
        return *this;
    }

    template<typename T>
    auto Rect_<T>::LeftTop() const noexcept -> Vec2_<T>
    {
        return { Left(), Top() };
    }

    template<typename T>
    auto Rect_<T>::LeftTop(Vec2_<T> v) noexcept -> Rect_<T> &
    {
        Top(v.Y());
        Left(v.X());
        return *this;
    }

    template<typename T>
    auto Rect_<T>::RightTop() const noexcept -> Vec2_<T>
    {
        return { Right(), Top() };
    }

    template<typename T>
    auto Rect_<T>::RightTop(Vec2_<T> v) noexcept -> Rect_<T> &
    {
        Top(v.Y());
        Right(v.X());
        return *this;
    }

    template<typename T>
    auto Rect_<T>::LeftBottom() const noexcept -> Vec2_<T>
    {
        return Vec2_<T>(Left(), Bottom());
    }

    template<typename T>
    auto Rect_<T>::LeftBottom(Vec2_<T> v) noexcept -> Rect_<T> &
    {
        Bottom(v.Y());
        Left(v.X());
        return *this;
    }

    template<typename T>
    auto Rect_<T>::RightBottom() const noexcept -> Vec2_<T>
    {
        return Vec2_<T>(Right(), Bottom());
    }

    template<typename T>
    auto Rect_<T>::RightBottom(Vec2_<T> v) noexcept -> Rect_<T> &
    {
        Bottom(v.Y());
        Right(v.X());
        return *this;
    }

    template<typename T>
    auto Rect_<T>::Str() const noexcept -> String
    {
        return "{" + std::to_string(x) + ", " + std::to_string(y) +
            ", " + std::to_string(w) + ", " + std::to_string(h) + "}";
    }

    template<typename T>
    auto Rect_<T>::operator==(const Rect_ &other) const noexcept -> bool
    {
        return (x == other.x && y == other.y &&
            w == other.w && h == other.h);
    }

    template<typename T>
    auto Rect_<T>::operator!=(const Rect_ &other) const noexcept -> bool
    {
        return !operator==(other);
    }

    template<typename T>
    template<typename U>
    Rect_<T>::operator Rect_<U>() const noexcept
    {
        return Rect_<U>(
            static_cast<U>(x),
            static_cast<U>(y),
            static_cast<U>(w),
            static_cast<U>(h));
    }


    template <typename Ostream, typename T>
    auto operator << (Ostream &out, const Rect_<T> &v) -> Ostream &
    {
        out << "{" << std::to_string(v.X()) << ", " << std::to_string(v.Y()) <<
            ", " << std::to_string(v.Width()) << ", " << std::to_string(v.Height()) << "}";
        return out;
    }

    using FRectangle = Rect_<float>;
    using Rectangle = Rect_<int>;

    template class Rect_<float>;
    template class Rect_<int>;
}