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

}}

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
}}

#include "jTestBase.h"

namespace jLib {
    class jTupleMPLTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();

            constexpr auto tuple_of_n = jMPL::make_tuple_n<3>(2);    // Intellisense Bugs here.
            constexpr auto array_of_n = jMPL::make_array_n<4>(1);
            constexpr auto array_from_tuple = jMPL::tuple_to_array(tuple_of_n); // Intellisense Bugs here.

            testConstNumber<std::get<0>(tuple_of_n)> out0; // Intellisense Bugs here.
            testConstNumber<array_of_n.at(0)> out1;
            testConstNumber<array_from_tuple.at(0)> out2;
        }
    };
}