#pragma once
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

        Rect_ &X(T pX) { x = pX; return *this; }
        Rect_ &Y(T pY) { y = pY; return *this; }
        Rect_ &W(T pW) { y = pW; return *this; }
        Rect_ &H(T pH) { y = pH; return *this; }

        void Set(T pX, T pY, T pW, T pH) noexcept
        {
            x = pX;
            y = pY;
            w = pW;
            h = pH;
        }

        [[nodiscard]]
        T Area() const noexcept
        {
            return w * h;
        }

        [[nodiscard]]
        T Left() const noexcept
        {
            return x;
        }

        [[nodiscard]]
        T Right() const noexcept
        {
            return x + w;
        }

        [[nodiscard]]
        T Top() const noexcept
        {
            return y;
        }

        [[nodiscard]]
        T Bottom() const noexcept
        {
            return y + h;
        }

        [[nodiscard]]
        bool Empty() const noexcept
        {
            return (w == 0 && h == 0);
        }

        bool operator==(const Rect_ &other)
        {
            return (x == other.x && y == other.y &&
                    w == other.w && h == other.y);
        }

        bool operator!=(const Rect_ &other)
        {
            return !(*this == other);
        }

        template<typename U>
        bool Intersects(const Rect_<U> &other)
        {
            static_assert(std::is_arithmetic_v<U> && std::is_convertible_v<U, T>, "Rectangle type mismatch.");
            T topA(Top()), bottomA(Bottom()),
                    leftA(Left()), rightA(Right()),
                    topB(other.Top()), bottomB(other.Bottom()),
                    leftB(other.Left()), rightB(other.Right());
            return !(topB > bottomA || bottomB < topA || rightB < leftA || leftB > rightA);
        }

        // Convertible by casting to other _Rect types. Please be aware of the effects of automatic type casting.
        template<typename U>
        explicit operator Rect_<U>()
        {
            static_assert(std::is_arithmetic_v<U> && std::is_convertible_v<U, T>, "Rectangle type mismatch.");
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

    typedef Rect_<float> FRectangle;
    typedef Rect_<int>   Rectangle;

    template class Rect_<float>;
    template class Rect_<int>;
}
