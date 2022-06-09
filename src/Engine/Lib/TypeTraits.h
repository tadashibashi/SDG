#pragma once
#include <type_traits>

namespace SDG
{
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

   /* template<typename Iterator>
    inline constexpr auto iterator_value_type_v = std::decay_t< decltype( *std::declval<Iterator>() ) >;

    template<typename Container>
    inline constexpr auto iterable_value_type_v = iterator_value_type_v<decltype(std::declval<Container>().begin())>;*/
    
}
