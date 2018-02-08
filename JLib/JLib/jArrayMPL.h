#pragma once
#include <array>
#include "jTypeTraits.h"
#include "jMath.h"

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

    template<typename Type>
    struct array_elem_ops_div
    {
        inline static constexpr const Type invoke(const Type &lhs, const Type &rhs)
        {
            return lhs / rhs;
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
    inline constexpr decltype(auto) array_mult(const std::array<Type, Degree> &lhs, const std::array<Type, Degree> &rhs)
    {
        return array_zip<array_elem_ops_mult<Type>>(lhs, rhs);
    }

    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_scalar_mult(const std::array<Type, Degree> &prime, const Type &scalar)
    {
        return array_for_each<array_elem_ops_mult<Type>>(prime, scalar);
    }

    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_scalar_div(const std::array<Type, Degree> &prime, const Type &scalar)
    {
        return array_for_each<array_elem_ops_div<Type>>(prime, scalar);
    }

    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_scalar_mult(const Type &scalar, const std::array<Type, Degree> &prime)
    {
        return array_for_each<array_elem_ops_mult<Type>>(prime, scalar);
    }

    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_dot_mult(const std::array<Type, Degree> &lhs, const std::array<Type, Degree> &rhs)
    {
        return array_fold<array_elem_ops_plus<Type>>(array_zip<array_elem_ops_mult<Type>>(lhs, rhs), Type(0));
    }

    template<typename Type, size_t Degree, jConstrain_typename_num_equal(Degree, 3)>
    inline constexpr decltype(auto) array_cross_mult(const std::array<Type, Degree> &lhs, const std::array<Type, Degree> &rhs)
    {
        return std::array<Type,Degree>{lhs.at(1)*rhs.at(2) - lhs.at(2)*rhs.at(1), lhs.at(2)*rhs.at(0) - lhs.at(0)*rhs.at(2), lhs.at(0)*rhs.at(1) - lhs.at(1)*rhs.at(0)};
    }

    template<typename Type, size_t Degree>
    inline constexpr decltype(auto) array_square_length(const std::array<Type, Degree> &prime)
    {
        return array_dot_mult(prime, prime);
    }

    template<typename ToType, typename Type, size_t Degree>
    inline constexpr decltype(auto) array_length(const std::array<Type, Degree> &prime)
    {
        return constable_sqrt<ToType>(static_cast<ToType>(array_square_length(prime)));
    }

    template<typename Type, size_t Degree, jConstrain_typename_floating_point(Type)>
    inline constexpr decltype(auto) array_normalize(const std::array<Type, Degree> &prime)
    {
        return  array_length<Type>(prime) == 0 
            ? make_array_n<Degree>(std::numeric_limits<Type>::quiet_NaN()) 
            : array_for_each<array_elem_ops_div<Type>>(prime, array_length<Type>(prime));
    }

    template<typename Type, size_t Degree, jConstrain_typename_floating_point(Type)>
    inline constexpr decltype(auto) array_cos_theta(const std::array<Type, Degree> &lhs, const std::array<Type, Degree> &rhs)
    {
        return  array_length<Type>(lhs) * array_length<Type>(rhs) == 0
            ? std::numeric_limits<Type>::quiet_NaN()
            : array_dot_mult(lhs, rhs) / (array_length<Type>(lhs) * array_length<Type>(rhs));
    }

    template<typename Type, size_t Degree, jConstrain_typename_floating_point(Type)>
    inline constexpr decltype(auto) array_lerp(const std::array<Type, Degree> &from, const std::array<Type, Degree> &to, const Type& interpolator)
    {
        return array_add(from, array_scalar_mult(interpolator, array_minus(to, from)));
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
            constexpr auto arr_mult = jMPL::array_dot_mult(arr_1, arr_2);
            constexpr auto arr_cross = jMPL::array_cross_mult(std::array<int, 3>{1, 0, 0}, std::array<int, 3>{0, 1, 0});
            //constexpr auto arr_error_cross = jMPL::array_cross_mult(arr_1, arr_2);
            constexpr auto arr_square_len = jMPL::array_square_length(arr_1);
            testConstNumber<arr_sum[3]> out1;
            testConstNumber<arr_mult> out2;
            testConstNumber<arr_cross[0]> out3;
            testConstNumber<arr_square_len> out4;
            constexpr auto arr_len = jMPL::array_length<float>(arr_cross);
            constexpr auto arr_double = std::array<double, 4>{1, 0, 2, 4};
            constexpr auto arr_double2 = std::array<double, 4>{3, 6, 0, 7};
            constexpr auto arr_float_NAN = std::array<float, 3>{0, 0, 0};
            constexpr auto arr_norm = jMPL::array_normalize(arr_double);
            constexpr auto arr_norm2 = jMPL::array_normalize(arr_float_NAN);
            constexpr auto array_costheta = jMPL::array_cos_theta(arr_double, arr_double2);
            constexpr auto array_lerped = jMPL::array_lerp(arr_double, arr_double2, 0.5);
        }
    };
}