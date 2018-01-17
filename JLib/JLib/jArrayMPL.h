#pragma once
#include <array>
#include <type_traits>

// because C++11 doesn't support constexpr lambda,
// some template could be rewritten. Without lambda,
// I must pass variables as params other than capture them.

namespace jLib {
namespace jMPL {

    // make a array of same n elements.
    template<size_t Num, typename Type>
    inline constexpr decltype(auto) make_array_n(Type t)
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

    template<typename elem_ops, typename Type, size_t Degree>
    inline constexpr decltype(auto) array_zip(const std::array<Type, Degree> &lhs, const std::array<Type, Degree> &rhs)
    {
        return __array_zip_detail::__array_zip_impl<Type, Degree, elem_ops>(lhs, rhs, std::make_index_sequence<Degree>());
    }

    namespace __array_zip_detail
    {
        template<typename Type, size_t Degree, typename elem_ops, size_t... I>
        inline constexpr decltype(auto) __array_zip_impl(const std::array<Type, Degree> &lhs, const std::array<Type, Degree> &rhs, std::index_sequence<I...>)
        {
            return std::array<Type, Degree> {elem_ops::invoke(lhs.at(I), rhs.at(I))...};
        }
    }

    template<typename elem_ops, typename Type, size_t Degree>
    inline constexpr decltype(auto) array_for_each(const std::array<Type, Degree> &prime, const Type &scalar)
    {
        return __array_for_each_detail::__array_for_each_impl<Type, Degree, elem_ops>(prime, scalar, std::make_index_sequence<Degree>());
    }

    namespace __array_for_each_detail
    {
        template<typename Type, size_t Degree, typename elem_ops, size_t... I>
        inline constexpr decltype(auto) __array_for_each_impl(const std::array<Type, Degree> &prime, const Type &scalar, std::index_sequence<I...>)
        {
            return std::array<Type, Degree> {elem_ops::invoke(prime.at(I), scalar)...};
        }
    }

    template<typename elem_ops, typename Type, size_t Degree>
    inline constexpr decltype(auto) array_fold(const std::array<Type, Degree> &prime, const Type &header)
    {
        return Degree == 0 ? header : __array_fold_detail::__array_fold_impl_host<Type, Degree, elem_ops, Degree>::__array_fold_impl(prime, header);
    }

    namespace __array_fold_detail
    {
        template<typename Type, size_t Degree, typename elem_ops, size_t Dim>
        struct __array_fold_impl_host
        {
            inline static constexpr const Type __array_fold_impl(const std::array<Type, Degree> &prime, const Type &header)
            {
                return elem_ops::invoke(__array_fold_impl_host<Type, Degree, elem_ops, Dim - 1>::__array_fold_impl(prime, header), prime.at(Dim - 1));
            }
        };

        template<typename Type, size_t Degree, typename elem_ops>
        struct __array_fold_impl_host<Type, Degree, elem_ops, 0>
        {
            inline static constexpr const Type __array_fold_impl(const std::array<Type, Degree> &prime, const Type &header)
            {
                return header;
            }
        };
    }

}}

namespace jLib {
namespace jMPL {

    template<typename Type>
    struct array_elem_ops_plus
    {
        inline static constexpr const Type invoke(const Type &lhs, const Type &rhs)
        {
            return lhs + rhs;
        }
    };

    template<typename Type>
    struct array_elem_ops_minus
    {
        inline static constexpr const Type invoke(const Type &lhs, const Type &rhs)
        {
            return lhs - rhs;
        }
    };

    template<typename Type>
    struct array_elem_ops_mult
    {
        inline static constexpr const Type invoke(const Type &lhs, const Type &rhs)
        {
            return lhs * rhs;
        }
    };

}
}

namespace jLib {
namespace jMPL {
    
    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_add(const std::array<Type, Degree> &lhs, const std::array<Type, Degree> &rhs)
    {
        return array_zip<array_elem_ops_plus<Type>>(lhs, rhs);
    }

    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_minus(const std::array<Type, Degree> &lhs, const std::array<Type, Degree> &rhs)
    {
        return array_zip<array_elem_ops_minus<Type>>(lhs, rhs);
    }

    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_scalar_mult(const std::array<Type, Degree> &prime, const Type &scalar)
    {
        return array_for_each<array_elem_ops_mult<Type>>(prime, scalar);
    }

    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_scalar_mult(const Type &scalar, const std::array<Type, Degree> &prime)
    {
        return array_for_each<array_elem_ops_mult<Type>>(prime, scalar);
    }

    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_dot_mult(const std::array<Type, Degree> &lhs, const std::array<Type, Degree> &rhs)
    {
        return array_for_each<array_elem_ops_mult<Type>>(prime, scalar);
    }

}
}

#include "jTestBase.h"

namespace jLib {
    class jArrayMPLTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();
            constexpr auto array_of_n = jMPL::make_array_n<4>(1);
            testConstNumber<array_of_n.at(0)> out0;
            constexpr auto arr_null = std::array<int, 0>{};
            constexpr auto arr_1 = std::array<int, 5>{1, 2, 3, 4, 9};
            constexpr auto arr_2 = std::array<int, 5>{5, 6, 7, 8, 6};
            constexpr auto arr_sum = jMPL::array_minus(arr_1, arr_2);
            constexpr auto arr_sum_each = jMPL::array_scalar_mult(5, arr_1);
            constexpr auto arr_fold = jMPL::array_fold<jMPL::array_elem_ops_plus<int>>(arr_1, 0);
            constexpr auto arr_fold2 = jMPL::array_fold<jMPL::array_elem_ops_plus<int>>(arr_null, 100);
            testConstNumber<arr_sum[3]> out1;
        }
    };
}