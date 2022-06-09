#include "MathShape.h"
#include <Engine/Debug/Assert.h>

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

    Vector3
    Math::Round(Vector3 v)
    {
        return Vector3(Math::Round(v.X()), Math::Round(v.Y()), Math::Round(v.Z()));
    }

    FRectangle
    Math::Round(FRectangle rect)
    {
        return FRectangle(Math::Round(rect.X()), Math::Round(rect.Y()),
                          Math::Round(rect.Width()), Math::Round(rect.Height()));
    }

    Circle
    Math::Round(Circle c)
    {
        return Circle(Round(c.X()), Round(c.Y()), Round(c.Radius()));
    }

    Vector2
    Math::RoundN(Vector2 v, int n)
    {
        return Vector2(Math::RoundN(v.X(), n), Math::RoundN(v.Y(), n));
    }

    Vector3
    Math::RoundN(Vector3 v, int n)
    {
        return Vector3(Math::RoundN(v.X(), n), Math::RoundN(v.Y(), n), Math::RoundN(v.Z(), n));
    }

    FRectangle
    Math::RoundN(FRectangle rect, int n)
    {
        return FRectangle(Math::RoundN(rect.X(), n), Math::RoundN(rect.Y(), n),
            Math::RoundN(rect.Width(), n), Math::RoundN(rect.Height(), n));
    }
    Circle
    Math::RoundN(Circle c, int n)
    {
        return Circle(RoundN(c.X(), n), RoundN(c.Y(), n), RoundN(c.Radius(), n));
    }

    Circle
    Math::Clamp(Circle circ, FRectangle rect)
    {
        SDG_Assert(circ.Diameter() <= rect.Width() && circ.Diameter() <= rect.Height());

        Vector2 position =
            Clamp(circ.Position(), FRectangle(
                rect.X() + circ.Radius(), rect.Y() + circ.Radius(),
                rect.Width() - circ.Diameter(), rect.Height() - circ.Diameter()));

        return Circle(position, circ.Radius());
    }
}
