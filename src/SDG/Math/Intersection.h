#pragma once
#include "Math.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Rectangle.h"
#include "Circle.h"

#include <utility>

namespace SDG::Math
{
    /// Function to check intersection between shapes
    template <typename ShapeA, typename ShapeB>
    inline bool Intersects(ShapeA a, ShapeB b)
    {
        return Intersection::Impl_(a, b);
    }

    // Intended for private implementation
    namespace Intersection
    {
        template <typename T, typename U>
        static inline bool Impl_(Rect_<T> a, Rect_<U> b)
        {
            return !(a.Top() > b.Bottom() || a.Bottom() < b.Top() ||
                     a.Right() < b.Left() || a.Left() > b.Right());
        }

        template <typename T, typename U>
        static inline bool Impl_(Rect_<T> rect, Vec2_<U> pt)
        {
            return !(pt.X() < rect.X() || pt.X() > rect.Right() ||
                     pt.Y() < rect.Y() || pt.Y() > rect.Bottom());
        }

        template <typename T>
        static inline bool Impl_(Rect_<T> rect, Circle circ)
        {
            float cx = circ.X(), cy = circ.Y();

            // Find closest Rect corner if outside
            if (cx < rect.Left())
                cx = rect.Left();
            else if (cx > rect.Right())
                cx = rect.Right();
            if (cy < rect.Top())
                cy = rect.Top();
            else if (cy > rect.Bottom())
                cy = rect.Bottom();

            return PointDistance(circ.X(), circ.Y(), cx, cy) <= circ.Radius();
        }

        /// Nearest pixel intersection check
        template <typename T, typename U>
        static inline bool Impl_(Vec2_<T> a, Vec2_<U> b)
        {
            return Math::Round(a) == Math::Round(b);
        }

        template <typename T, typename U>
        static inline bool Impl_(Vec2_<T> pt, Rect_<U> rect)
        {
            return Impl_(rect, pt);
        }

        template <typename T>
        static inline bool Impl_(Vec2_<T> pt, Circle circ)
        {
            float distance = PointDistance(pt.X(), pt.Y(),circ.X(), circ.Y());
            return distance <= circ.Radius();
        }

        static inline bool Impl_(Circle a, Circle b)
        {
            float distance = PointDistance(a.X(), a.Y(), b.X(), b.Y());
            return distance < a.Radius() + b.Radius();
        }

        template <typename T>
        static inline bool Impl_(Circle circ, Rect_<T> rect)
        {
            return Impl_(std::move(rect), std::move(circ));
        }

        template <typename T>
        static inline bool Impl_(Circle circ, Vec2_<T> pt)
        {
            return Impl_(std::move(pt), std::move(circ));
        }
    }

}