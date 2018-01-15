#pragma once

#include <tuple>

namespace jLib{
namespace jMPL{

    template<size_t Num, typename Type>
    constexpr std::array<Type, Num> make_array_n(Type t)
    {
        return __make_array_n_detail::__make_array_n_impl<decltype(constexpr make_array_n<Num>(Type()), Type)>::__make_array_n(t);
    }

    template<size_t Num, typename Type>
    constexpr decltype(auto) make_tuple_n(Type t)
    {
        return __make_tuple_n_detail::__make_tuple_n_impl<Type, Num>::__make_tuple_n(t);
    }

    namespace __make_tuple_n_detail
    {
        template<typename Type, size_t dim>
        struct __make_tuple_n_impl
        {
            inline constexpr static decltype(auto) __make_tuple_n(Type t)
            {
                return std::tuple_cat(std::make_tuple(Type(t)), __make_tuple_n_impl<Type, dim - 1>::__make_tuple_n(t));
            }
        };

        template<typename Type>
        struct __make_tuple_n_impl<Type, 1>
        {
            inline constexpr static decltype(auto) __make_tuple_n(Type t)
            {
                return std::make_tuple(Type(t));
            }
        };
    }

    namespace __make_array_n_detail
    {
        template<typename T, typename Type>
        struct __make_array_n_impl;

        template<typename... Args>
        struct __make_array_n_impl <std::tuple<Args...>, Type>
        {
            inline constexpr static decltype(auto) __make_array_n(Type t, Args...args)
            {
                return {(doNothing(args), Type())... };
            }
        };

        template<typename T>
        doNothing(T t){}
    }
}}