#pragma once
#include "Vector2.h"
#include "MathConstants.h"

namespace SDG
{
    class Circle
    {
    public:
        Circle() : radius(), x(), y() { }
        Circle(float x, float y, float radius) :
            radius(radius), x(x), y(y) {}
        Circle(Vector2 position, float radius) :
            radius(radius), x(position.X()), y(position.Y()) { }

        Vector2 Position() const { return {x, y}; }
        float Area() const { return Math::Pi * radius * radius; }
        float Radius() const { return radius; }
        float Diameter() const { return radius * 2; }
        bool Empty() const { return radius == 0; }
        float X() const { return x; }
        float Y() const { return y; }
        
        Circle &Set(float pX, float pY, float pRadius)
        {
            x = pX; y = pY; radius = pRadius;
            return *this;
        }
        Circle &X(float pX) { x = pX; return *this; }
        Circle &Y(float pY) { y = pY; return *this; }
        Circle &Radius(float pRadius) { radius = pRadius; return *this; }
        Circle &Position(Vector2 position) { x = position.X(), y = position.Y(); return *this; }

        [[nodiscard]] bool operator == (const Circle &other) const
        {
            return x == other.X() && y == other.Y() && radius == other.Radius();
        }
    private:
        float radius, x, y;
    };
}
