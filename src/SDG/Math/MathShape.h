/// Contains functions and overloads involving non-primitive SDG math classes
#pragma once
#include "Circle.h"
#include "Intersection.h"
#include "Math.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Rectangle.h"

namespace SDG::Math
{
    /// Linear interpolation
    /// @param val the Vec2 to work with
    /// @param dest the target destination
    /// @param amt the amount to lerp by as a percentage (0 to 1.f)
    Vector2 Lerp(Vector2 val, Vector2 dest, double amt);
    FRectangle Lerp(FRectangle val, FRectangle dest, double amt);
    Circle Lerp(Circle val, Circle dest, double amt);

    Vector2 Round(Vector2 v);
    Vector3 Round(Vector3 v);
    FRectangle Round(FRectangle rect);
    Circle Round(Circle c);
    Vector2 RoundN(Vector2 v, int n);
    Vector3 RoundN(Vector3 v, int n);
    FRectangle RoundN(FRectangle rect, int n);
    Circle RoundN(Circle c, int n);

    Vector2 Transform(Vector2 position, const Matrix4x4 &mat);

    /**
     * Get the resulting Vector from an angle and length..
     * @param degrees
     * @param length
     */
    inline Vector2 Trajectory(float degrees, float length)
    {
        return Vector2(TrajectoryX(degrees, length),
                       TrajectoryY(degrees, length));
    }

    /// Constrains a value between two Vectors, inclusively on both ends.
    /// Min's x and y values may be greater than max's, or some combination,
    /// and the number will still be contained by both limits.
    inline Vector2 Clamp(Vector2 value, Vector2 min, Vector2 max)
    {
        return {Clamp(value.X(), min.X(), max.X()),
                Clamp(value.Y(), min.Y(), max.Y())};
    }

    /// Constrains a point inside of a rectangle
    inline Vector2 Clamp(Vector2 value, FRectangle bounds)
    {
        return {Clamp(value.X(), bounds.Left(), bounds.Right()),
                Clamp(value.Y(), bounds.Top(), bounds.Bottom())};
    }

    /// Constrains a value between two Vectors, inclusively on both ends.
    /// Min's x and y values may be greater than max's, or some combination,
    /// and the number will still be contained by both limits.
    inline Point Clamp(Point value, Point min, Point max)
    {
        return {Clamp(value.X(), min.X(), max.X()),
                Clamp(value.Y(), min.Y(), max.Y())};
    }

    /// Constrains a point inside of a rectangle
    inline Point Clamp(Point value, Rectangle bounds)
    {
        return {Clamp(value.X(), bounds.Left(), bounds.Right()),
                Clamp(value.Y(), bounds.Top(), bounds.Bottom())};
    }

    /// Clamps a circle inside a rectangle
    /// Please make sure that the rectangle's width and height are greater than
    /// the circle's diameter.
    Circle Clamp(Circle circ, FRectangle rect);

    /// Wraps a point inside of a rectangle
    inline Vector2 Wrap(Vector2 v, FRectangle rect)
    {
        return Vector2(WrapF(v.X(), rect.Left(), rect.Right()),
                       WrapF(v.Y(), rect.Top(), rect.Bottom()));
    }

    /// @brief Wraps a point inside of a rectangle with added margin
    /// @param p - point to wrap
    /// @param rect - rectangle to add margin to 
    /// @param margin - margin added to rectangle
    /// @return resulting point
    inline Vector2 Wrap(Vector2 v, FRectangle rect, Vector2 margin)
    {
        return Wrap(v, FRectangle(rect.X() - margin.X(), rect.Y() - margin.Y(),
            rect.Width() + margin.X() * 2.f, rect.Height() + margin.Y() * 2.f));
    }

    /// Wraps a point inside of a rectangle
    inline Point Wrap(Point p, Rectangle rect)
    {
        return Point(Wrap(p.X(), rect.Left(), rect.Right()),
                       Wrap(p.Y(), rect.Top(), rect.Bottom()));
    }

    /// @brief Wraps a point inside of a rectangle with added margin
    /// @param p - point to wrap
    /// @param rect - rectangle to add margin to
    /// @param margin - margin added to rectangle
    /// @return resulting point
    inline Point Wrap(Point p, Rectangle rect, Point margin)
    {
        return Wrap(p, Rectangle(rect.X() - margin.X(), rect.Y() - margin.Y(),
            rect.Width() + margin.X() * 2, rect.Height() + margin.Y() * 2));
    }

    /// Gets the angle, in degrees, between two points
    inline float PointDirection(Vector2 a, Vector2 b)
    {
        return PointDirection(a.X(), a.Y(), b.X(), b.Y());
    }

    /// Gets the angle, in degrees, between two points
    inline float PointDirection(Point a, Point b)
    {
        return PointDirection(a.X(), a.Y(), b.X(), b.Y());
    }

    inline float PointDistance(Vector2 a, Vector2 b)
    {
        return PointDistance(a.X(), a.Y(),
                             b.X(), b.Y());
    }

    inline float PointDistance(Point a, Point b)
    {
        return PointDistance((float)a.X(), (float)a.Y(),
                             (float)b.X(), (float)b.Y());
    }
}
