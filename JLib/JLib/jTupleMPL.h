#pragma once

#include <tuple>

namespace jLib{
namespace jMPL{

    template<typename Type, size_t Num>
    constexpr decltype(auto) make_tuple_n(Num, Type type)
    {
        return __make_tuple_n_detail::__make_tuple_n_impl<Type, Num>::__make_tuple_n()
    }

    namespace __make_tuple_n_detail
    {
        template<typename Type, size_t dim>
        struct __make_tuple_n_impl
        {
            inline static decltype(auto) __make_tuple_n()
            {
                return std::tuple_cat(Type(), __make_tuple_n_impl<Type, dim - 1>::__make_tuple_n());
            }
        };

        template<typename Type, 1>
        struct __make_tuple_n_impl
        {
            inline static decltype(auto) __make_tuple_n()
            {
                return std::make_tuple(Type());
            }
        };
    }
}}
