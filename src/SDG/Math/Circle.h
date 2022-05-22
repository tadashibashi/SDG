#pragma once
#include <SDG/Math/MathConstants.h>

namespace SDG
{
    class Circle
    {
    public:
        Circle() : radius(), x(), y() { }
        Circle(float x, float y, float radius) :
            radius(radius), x(x), y(y) {}

        float Area() const { return Math::Pi * radius * radius; }
        float Radius() const { return radius; }
        float Diameter() const { return radius * 2; }
        bool Empty() const { return radius == 0; }
        float X() const { return x; }
        float Y() const { return y; }

        Circle &X(float pX) { x = pX; return *this; }
        Circle &Y(float pY) { y = pY; return *this; }
        Circle &Radius(float pRadius) { radius = pRadius; return *this; }
    private:
        float radius, x, y;
    };
}
