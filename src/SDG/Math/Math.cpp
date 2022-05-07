#include "Math.h"

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
        return Abs(RadToDeg(std::atan(diffY / diffX))) + (float)(quadrant * 90);
    }
    else
    {   // quadrants 1 or 3
        return 90-Abs(RadToDeg(std::atan((diffY / diffX)))) + (float)(quadrant * 90);
    }
}

int
SDG::Math::GetQuadrant(float x, float y)
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
