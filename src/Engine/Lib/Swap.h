#pragma once

namespace SDG
{
    /// Swaps a with b with the default copy assignment operator.
    /// Please specialize this function for special cases.
    template <typename T>
    inline void Swap(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

#define SDG_Swap(a, b) do \
    { unsigned char z__swap_temp__z[sizeof(a) == sizeof(b) ? (signed)sizeof(a) : -1]; \
      memcpy(z__swap_temp__z, &b, sizeof(a)); \
      memcpy(&b,&a,       sizeof(a)); \
      memcpy(&a,z__swap_temp__z,sizeof(a)); \
    } while(0)
}
