#pragma once
#include <initializer_list>
#include <boost/assert.hpp>
#include <cmath>
#include <array>
#include <cstring>
#include "jTypeTraits.h"
#include "jArrayMPL.h"

namespace jLib{
namespace jContainer{

template <typename Type, size_t Degree>
class jVecBase
{
public:
    template<typename ...Args>
    constexpr jVecBase(Args... inputs) : _inner_vec{ static_cast<Type>(inputs)... } {}
    constexpr jVecBase() : _inner_vec{} {}
    constexpr jVecBase(const jVecBase &rhs) : _inner_vec(rhs._inner_vec) {}
    jVecBase(jVecBase &&rhs) noexcept
    {
        _inner_vec = std::move(rhs._inner_vec);
    }

    jVecBase& operator=(const jVecBase &rhs) 
    {
        if (this != &rhs) {
            _inner_vec = rhs._inner_vec;
        }
        return *this;
    }

    jVecBase& operator= (jVecBase &&rhs) noexcept
    {
        if (this != &rhs) {
            this->_inner_vec = std::move(rhs._inner_vec);
        }
        return *this;
    }

    constexpr const Type & at(size_t pos) const {
        return _inner_vec.at(pos);
    }
    Type & at(size_t pos)
    {
        return _inner_vec.at(pos);
    }
    constexpr const Type & operator[](size_t pos) const {
        return _inner_vec.at(pos);
    }
    Type & operator[](size_t pos)
    {
        return _inner_vec.at(pos);
    }

    inline constexpr const Type square_length() const 
    {
        return (*this) * (*this);
    }

    template<jConstrain_typename_floating_point(Type)>
    inline constexpr const jVecBase normalize() const
    {
        return jVecBase(jMPL::array_normalize(this->_inner_vec));
    }

public:
    inline static constexpr const size_t dim(){
        return Degree;
    }
    inline static constexpr const jVecBase zero()
    {
        return jVecBase(jMPL::make_array_n<Degree>(static_cast<Type>(0)));
    }
    inline static constexpr const jVecBase identity()
    {
        return jVecBase(jMPL::make_array_n<Degree>(static_cast<Type>(1)));
    }

    template<typename Type, size_t Degree>
    inline friend constexpr const jVecBase<Type, Degree> operator+ (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree>
    inline friend constexpr const jVecBase<Type, Degree> operator- (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree>
    inline friend constexpr const Type operator* (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree>
    inline friend constexpr const jVecBase<Type, Degree> operator* (const jVecBase<Type, Degree> &prime, const Type &scalar);
    template<typename Type, size_t Degree>
    inline friend constexpr const jVecBase<Type, Degree> operator* (const Type &scalar, const jVecBase<Type, Degree> &prime);
    template<typename Type, size_t Degree, jConstrain_typename_num_eqal(Degree, 3)>
    inline friend constexpr const jVecBase<Type, Degree> operator^ (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs);

    template<typename Type, size_t Degree>
    inline friend constexpr const Type dot (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree, jConstrain_typename_num_eqal(Degree, 3)>
    inline friend constexpr const jVecBase<Type, Degree> cross (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree, jConstrain_typename_floating_point(Type)>
    inline friend constexpr const Type cos_theta(const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs);
private:
    constexpr jVecBase(const std::array<Type, Degree> &rhs) :_inner_vec(rhs) {}
    constexpr jVecBase(std::array<Type, Degree> &&rhs) noexcept : _inner_vec(std::move(rhs)) {}
    std::array<Type, Degree> _inner_vec;
};

template<typename Type, size_t Degree>
inline constexpr const jVecBase<Type, Degree> operator+ (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs)
{
    return jVecBase<Type, Degree>(jMPL::array_add(lhs._inner_vec, rhs._inner_vec));
}

template<typename Type, size_t Degree>
inline constexpr const jVecBase<Type, Degree> operator- (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs)
{
    return jVecBase<Type, Degree>(jMPL::array_minus(lhs._inner_vec, rhs._inner_vec));
}

template<typename Type, size_t Degree>
inline constexpr const Type operator* (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs)
{
    return jMPL::array_dot_mult(lhs._inner_vec, rhs._inner_vec);
}

template<typename Type, size_t Degree>
inline constexpr const jVecBase<Type, Degree> operator* (const jVecBase<Type, Degree> &prime, const Type &scalar)
{
    return jVecBase<Type, Degree>(jMPL::array_scalar_mult(prime._inner_vec, scalar));
}

template<typename Type, size_t Degree>
inline constexpr const jVecBase<Type, Degree> operator* (const Type &scalar, const jVecBase<Type, Degree> &prime)
{
    return jVecBase<Type, Degree>(jMPL::array_scalar_mult(prime._inner_vec, scalar));
}

template<typename Type, size_t Degree, jConstrain_typename_num_eqal(Degree, 3)>
inline constexpr const jVecBase<Type, Degree> operator^ (const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs)
{
    return jVecBase<Type, Degree>(jMPL::array_cross_mult(lhs._inner_vec, rhs._inner_vec));
}

template<typename Type, size_t Degree>
inline constexpr const Type dot(const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs)
{
    return lhs * rhs;
}

template<typename Type, size_t Degree, jConstrain_typename_num_eqal(Degree, 3)>
inline constexpr const jVecBase<Type, Degree> cross(const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs)
{
    return lhs ^ rhs;
}

template<typename Type, size_t Degree, jConstrain_typename_floating_point(Type)>
inline constexpr const Type cos_theta(const jVecBase<Type, Degree> &lhs, const jVecBase<Type, Degree> &rhs)
{
    return jMPL::array_cos_theta(lhs._inner_vec, rhs._inner_vec);
}

template<typename Type>
using jVec2 = jVecBase<Type, 2>;
template<typename Type>
using jVec3 = jVecBase<Type, 3>;

using jPoint2D = jVecBase<float, 2>;
using jPoint3D = jVecBase<float, 3>;
}}

#include "jTestBase.h"
#include "jVectorTraits.h"
namespace jLib {
    class jVecBaseTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();

            constexpr jContainer::jVecBase<int, 4> theVec = { 1, 2, 3, 4};
            constexpr jContainer::jVecBase<int, 4> otherVec = {3, 2, 1, 0};
            constexpr auto vec_square_len = theVec.square_length();
            constexpr auto identityVec = jContainer::jVecBase<int, 4>::identity();  //intellisense bug.
            testConstNumber<identityVec.at(0)> out2;

            const jContainer::jVecBase<int, 5> constVec = { 1, 2 };
            testConstNumber<jMPL::jVecTraits::is_vec<decltype(constVec)>::value> out3;
            testConstNumber<decltype(constVec)::dim()> out4;

            constexpr auto vec_sum = theVec + otherVec - otherVec;  //intellisense bug.
            testConstNumber<vec_sum[2]> out7;

            constexpr auto vec_dot_mult = theVec * otherVec;
            constexpr auto vec_scar_mult = theVec * 6;  //intellisense bug.

            constexpr jContainer::jVecBase<double, 3> aVec = { 1, 1, 1};
            constexpr jContainer::jVecBase<double, 3> bVec = { 2, 2, 2};

            constexpr auto vec_cross_mult = jContainer::cross(aVec, bVec); //intellisense bug.
            constexpr auto vec_norm = aVec.normalize(); //intellisense bug.
            constexpr auto vec_cos_theta = jContainer::cos_theta(aVec, bVec);
            testConstNumber<(int)vec_norm[0]> out8;
        }
    };
}