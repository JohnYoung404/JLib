#pragma once

#include <tuple>
#include <utility>
#include <array>

// make a tuple of same n elements.
namespace jLib{
namespace jMPL{

    template<size_t Num, typename Type>
    constexpr decltype(auto) make_tuple_n(Type t)
    {
        return __make_tuple_n_detail::__make_tuple_n_impl(t, std::make_index_sequence<Num>());
    }

    namespace __make_tuple_n_detail
    {
        template<typename Type, size_t... I>
        inline constexpr decltype(auto) __make_tuple_n_impl(Type t, std::index_sequence<I...>)
        {
            return std::make_tuple( (I, t)... );
        }
    }
}}

// make an array from a tuple containing elements of same type.
namespace jLib {
namespace jMPL {

    template<typename T, typename... U>
    inline constexpr decltype(auto) tuple_to_array(const std::tuple<T, U...>& t)
    {
        return __tuple_to_array_detail::__tuple_to_array_impl(t, std::make_index_sequence<1 + sizeof...(U)>());
    }

    namespace __tuple_to_array_detail
    {
        template<typename T, typename... U, size_t... I>
        inline constexpr decltype(auto) __tuple_to_array_impl (const std::tuple<T, U...>& t, std::index_sequence<I...>)
        {
            return std::array<T, 1 + sizeof...(U)>{ std::get<I>(t)... };
        }
    }

}
}

// make a array of same n elements.
namespace jLib {
    namespace jMPL {

        template<size_t Num, typename Type>
        constexpr decltype(auto) make_array_n(Type t)
        {
            return __make_array_n_detail::__make_array_n_impl<Num>(t, std::make_index_sequence<Num>());
        }

        namespace __make_array_n_detail
        {
            template<size_t Num, typename Type, size_t... I>
            inline constexpr decltype(auto) __make_array_n_impl(Type t, std::index_sequence<I...>)
            {
                return std::array<Type, Num> {(I, t)...};
            }
        }
    }
}

// 
namespace jLib {
    namespace jMPL {

        template<typename Type, typename... Args>
        constexpr decltype(auto) make_array_from_braced_init_list(Args... args)
        {
            return std::array<Type, sizeof...(args)> {Type(args)...};
        }
        //
        //namespace __make_array_n_detail
        //{
        //    template<size_t Num, typename Type, size_t... I>
        //    inline constexpr decltype(auto) __make_array_n_impl(Type t, std::index_sequence<I...>)
        //    {
        //        return std::array<Type, Num> {(I, t)...};
        //    }
        //}
    }
}