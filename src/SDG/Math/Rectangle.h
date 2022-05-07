#pragma once
#include <type_traits>
#include <ostream>

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

        void X(T pX) { x = pX; }
        void Y(T pY) { y = pY; }
        void Width(T pW) { w = pW; }
        void Height(T pH) { h = pH; }

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

        [[nodiscard]]
        std::string String() const noexcept
        {
            return "{" + std::to_string(x) + ", " + std::to_string(y) +
                ", " + std::to_string(w) + ", " + std::to_string(h) + "}";
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

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Rect_<T> &v)
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
