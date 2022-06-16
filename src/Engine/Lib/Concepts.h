#pragma once
#include "TypeTraits.h"

template <typename T, typename Stream>
concept Streamable = SDG::is_streamable<Stream, T>::value;

template <typename T, typename U>
concept Derived = std::is_base_of<U, T>::value;

template <typename T>
concept Arithmetic = std::is_arithmetic<T>::value;

template <typename T>
concept Floating = std::is_floating_point<T>::value;

template <typename T>
concept Comparable = std::is_same< bool, decltype(std::declval<T>() < std::declval<T>()) >::value;

template <typename It, typename T>
concept Iterates = std::is_same<T, SDG::iterator_value_t<It>>::value;

template <typename T, typename... TArgs>
concept ConstructibleFrom = std::is_same<T, decltype(T(std::declval<TArgs>()...))>::value;
