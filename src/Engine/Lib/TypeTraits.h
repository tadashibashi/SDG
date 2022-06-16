#pragma once
#include <type_traits>

namespace SDG
{
    template <typename T, typename...TArgs>
    inline constexpr bool is_constructible_from_v = is_constructible_from<T, TArgs...>::value;

    template<typename S, typename T>
    class is_streamable
    {
        template<typename SS, typename TT>
        static auto test(int)
            -> decltype(std::declval<SS &>() << std::declval<TT>(), std::true_type());

        template<typename, typename>
        static auto test(...)->std::false_type;

    public:
        static const bool value = decltype(test<S, T>(0))::value;
    };

    template<typename S, typename T>
    inline constexpr bool is_streamable_v = is_streamable<S, T>::value;

    template<typename Func, typename R, typename...Args>
    class is_callable_with
    {
        template<typename FFunc, typename RR, typename...AArgs>
        static auto test(int)
            -> decltype(std::is_same_v<RR, decltype( std::declval<FFunc>()(std::declval<AArgs>()...))>, std::true_type());

        template<typename FFunc, typename RR, typename...AArgs>
        static auto test(...)->std::false_type;

    public:
        static const bool value = decltype(test<Func, R, Args...>(0))::value;
    };

    template<typename Func, typename R, typename...Args>
    class is_callable_with<Func, R(Args...)> : public is_callable_with<Func, R, Args...> { };

    template<typename Func, typename R, typename...Args>
    inline constexpr bool is_callable_with_v(const Func &&) { return is_callable_with<Func, R(Args...)>::value; }

    template <typename It>
    struct iterator_value
    {
        using type = typename std::decay<decltype(*std::declval<It>())>::type;
    };

    template <typename It>
    using iterator_value_t = typename iterator_value<It>::type;

    template <typename Iterable>
    struct iterable_value
    {
        using type = typename iterator_value<decltype(std::declval<Iterable>().begin())>::type;
    };

    template <typename Iterable>
    using iterable_value_t = typename iterable_value<Iterable>::type;
}
