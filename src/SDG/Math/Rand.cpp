/* =============================================================================
 * Rand
 *
 *
 * ===========================================================================*/
#include "Rand.h"
#include <SDG/Debug.hpp>

namespace SDG
{
    static std::random_device randDevice;
    static std::mt19937 mt(randDevice());
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);

    float Rand::Next(float n)
    {
        return distribution(mt) * n;
    }

    int Rand::INext(int n)
    {
        return static_cast<int>(Next((float)n));
    }

    float Rand::Range(float low, float high)
    {
        SDG_Assert(low <= high);
        return Next() * (high - low) + low;
    }

    int Rand::IRange(int low, int high)
    {
        return static_cast<int>(Range((float)low, (float)high));
    }

    bool Rand::Chance(int n, int outof) {
        if (outof > 0)
        {
            return INext(outof) < n;
        }
        else
        {
            return false;
        }
    }

    bool Rand::Chance(float n, float outof) {
        if (outof > 0)
        {
            return Next() < n / outof;
        }
        else
        {
            return false;
        }
    }


}