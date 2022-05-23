#include "Shape.h"

namespace SDG
{
    Vector2
    Math::Transform(Vector2 position, const Matrix4x4 &mat)
    {
        float x = position.X(), y = position.Y();
        mat.Transform(&x, &y);
        return {x, y};
    }

    Vector2
    Math::Lerp(Vector2 val, Vector2 dest, double amt)
    {
        return Vector2(Lerp(val.X(), dest.X(), amt),
                       Lerp(val.Y(), dest.Y(), amt));
    }

    FRectangle
    Math::Lerp(FRectangle val, FRectangle dest, double amt)
    {
        return FRectangle(Lerp(val.X(), dest.X(), amt),
                          Lerp(val.Y(), dest.Y(), amt),
                          Lerp(val.Width(), dest.Width(), amt),
                          Lerp(val.Height(), dest.Height(), amt));
    }

    Circle Math::Lerp(Circle val, Circle dest, double amt)
    {
        return Circle(Lerp(val.X(), dest.X(), amt),
            Lerp(val.Y(), dest.Y(), amt),
            Lerp(val.Radius(), dest.Radius(), amt));
    }

    Vector2
    Math::Round(Vector2 v)
    {
        return Vector2(Math::Round(v.X()), Math::Round(v.Y()));
    }

    FRectangle
    Math::Round(FRectangle rect)
    {
        return FRectangle(Math::Round(rect.X()), Math::Round(rect.Y()),
                          Math::Round(rect.Width()), Math::Round(rect.Height()));
    }
    Circle Math::Round(Circle c)
    {
        return Circle(Round(c.X()), Round(c.Y()), Round(c.Radius()));
    }
}
