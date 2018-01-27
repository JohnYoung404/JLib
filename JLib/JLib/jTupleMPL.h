#pragma once

#include <tuple>
#include <utility>
#include <type_traits>
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

namespace jLib {
namespace jMPL {
    template<typename... Args, typename Func>
    void tuple_for_each(const std::tuple<Args...> &t, Func &f)
    {
        tuple_for_each_::__tuple_processor<decltype(t), Func, sizeof...(Args)>::__tuple_process(t, f);
    }

    namespace tuple_for_each_ {
        template<typename Tuple, typename Func, size_t N>
        struct __tuple_processor
        {
            inline static void __tuple_process(const Tuple &t, Func &f)
            {
                __tuple_processor<Tuple, Func, N - 1>::__tuple_process(t, f);
                f(std::get<N - 1>(t));
            }
        };

        template<typename Tuple, typename Func>
        struct __tuple_processor<Tuple, Func, 1>
        {
            inline static void __tuple_process(const Tuple &t, Func &f)
            {
                f(std::get<0>(t));
            }
        };
    }

}}


#include "jTestBase.h"

namespace jLib {
    class jTupleMPLTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();

            constexpr auto tuple_of_n = jMPL::make_tuple_n<3>(2);    // Intellisense Bugs here.
            constexpr auto array_from_tuple = jMPL::tuple_to_array(tuple_of_n); // Intellisense Bugs here.

            testConstNumber<std::get<0>(tuple_of_n)> out0; // Intellisense Bugs here.
            testConstNumber<array_from_tuple.at(0)> out1;

            auto t1 = std::make_tuple(1, "2", 3.4f);
            int n = 5;
            auto t2 = std::tuple_cat(t1, std::tie(n), std::make_pair(6, 7));
            jMPL::tuple_for_each(t2, [](auto &val) { std::cout << val << " "; });
            std::cout << std::endl;
        }
    };
}