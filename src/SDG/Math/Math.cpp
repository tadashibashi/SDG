// Put longer multi-line, non-template math functions here
#include "Math.h"
#include <cmath>

namespace SDG::Math
{
    /**
     * Returns the quadrant the coordinate is in starting with quadrant zero
     * on the bottom right, going clockwise until quadrant 3 on the top-right.
     * This function is a helper used by point direction
     */
    static int
    GetQuadrant(float x, float y);

    double
    Cos(double rad) { return std::cos(rad); }
    float
    Cos(float rad) { return std::cos(rad); }
    double
    Sin(double rad) { return std::sin(rad); }
    float
    Sin(float rad) { return std::sin(rad); }
    double
    Tan(double rad) { return std::tan(rad); }
    float
    Tan(float rad) { return std::tan(rad); }
    double
    ArcCos(double rad) { return std::acos(rad); }
    float
    ArcCos(float rad) { return std::acos(rad); }
    double
    ArcSin(double rad) { return std::asin(rad); }
    float
    ArcSin(float rad) { return std::asin(rad); }
    double
    ArcTan(double rad) { return std::atan(rad); }
    float
    ArcTan(float rad) { return std::atan(rad); }

    double
    Sqrt(double n) { return std::sqrt(n); }
    float
    Sqrt(float n) { return std::sqrt(n); }
    double
    Pow(double n, double pow) { return std::pow(n, pow); }
    float
    Pow(float n, double pow) { return std::pow(n, pow); }
    double
    Log(double n) { return std::log(n); }
    float
    Log(float n) { return std::log(n); }
    double
    Log10(double n) { return std::log10(n); }
    float
    Log10(float n) { return std::log10(n); }


    float
    PointDirection(float x1, float y1, float x2, float y2)
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
        if (x > 0 && y > 0) {
            return 0;
        } else if (x <= 0 && y > 0) {
            return 1;
        } else if (x < 0 && y <= 0) {
            return 2;
        } else if (x >= 0 && y <= 0) {
            return 3;
        }
        return -1;
    }

    double
    ModF(double x, double n)
    {
        if (n == 0) return 0;
        return std::fmod((std::fmod(x, n) + n), n);
    }

    float
    ModF(float x, float n)
    {
        if (n == 0) return 0;
        return std::fmod((std::fmod(x, n) + n), n);
    }

    int
    Mod(int x, int n)
    {
        if (n == 0) return 0;
        return (((x % n) + n) % n);
    }

    float
    PointDistance(float x1, float y1, float x2, float y2)
    {
        float a = x1 - x2;
        float b = y1 - y2;
        return std::sqrt(a * a + b * b);
    }

    double RoundN(double x, int n)
    {
        double p = std::pow(10, -n);
        return Round(x * p) / p;
    }

    float RoundN(float x, int n)
    {
        float p = std::pow(10, -n);
        return Round(x * p) / p;
    }

}

