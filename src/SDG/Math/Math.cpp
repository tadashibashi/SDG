// Put longer multi-line, non-template math functions here
#include "Math.h"

/**
 * Returns the quadrant the coordinate is in starting with quadrant zero
 * on the bottom right, going clockwise until quadrant 3 on the top-right.
 * This function is a helper used by point direction
 */
static int
GetQuadrant(float x, float y);

SDG::Vector2
SDG::Math::Transform(SDG::Vector2 position, const SDG::Matrix4x4 &mat)
{
    float x = position.X(), y = position.Y();
    mat.Transform(&x, &y);
    return {x, y};
}

float
SDG::Math::PointDirection(float x1, float y1, float x2, float y2)
{
    float diffX = x2 - x1;
    float diffY = y2 - y1;
    int quadrant = GetQuadrant(diffX, diffY);

    if (quadrant % 2 == 0)
    { // if quadrants 0 or 2
        return Abs(DegsPerRad * (std::atan(diffY / diffX))) + (float)(quadrant * 90);
    }
    else
    {   // quadrants 1 or 3
        return 90-Abs(DegsPerRad * (std::atan((diffY / diffX)))) + (float)(quadrant * 90);
    }
}

int
GetQuadrant(float x, float y)
{
    if (x > 0 && y >= 0) {
        return 3;
    } else if (x <= 0 && y > 0) {
        return 2;
    } else if (x < 0 && y <= 0) {
        return 1;
    } else if (x >= 0 && y < 0) {
        return 0;
    }
    return -1;
}

template<>
SDG::Vector2 SDG::Math::Lerp(SDG::Vector2 val, SDG::Vector2 dest, double amt)
{
    return Vector2(Lerp(val.X(), dest.Y(), amt), Lerp(val.Y(), dest.Y(), amt));
}
