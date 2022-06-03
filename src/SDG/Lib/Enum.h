#pragma once

#define FlagOps(type, uType) inline type operator | (type a, type b) { \
    return static_cast<type>(static_cast<uType>(a) | static_cast<uType>(b)); } \
    inline type &operator |= (type &a, const type &b) { \
    return a = static_cast<type>(static_cast<uType>(a) | static_cast<uType>(b));}
