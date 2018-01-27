// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [1/26/2018]
// Description : Matrix Library.

#pragma once
#include <array>
#include <memory>
#include <initializer_list>
#include "jVector.h"
#include "jGrid.h"
#include "jMatrixMPL.h"

namespace jLib{
namespace jContainer {

template <typename Type, size_t Degree>
class jMatBase
{
    enum { size = Degree * Degree };
public:
    jMatBase() : _mat_ptr(std::shared_ptr<Type>(new Type[size], std::default_delete<Type[]>())), _mat_accesser(Degree, Degree, _mat_ptr) { _mat_accesser.reset(); }
    jMatBase(const std::initializer_list<Type> &InitList) : _mat_ptr(std::shared_ptr<Type>(new Type[size], std::default_delete<Type[]>())), _mat_accesser(Degree, Degree, _mat_ptr)
    {
#ifdef _DEBUG
        BOOST_ASSERT(InitList.size() == size);
#endif
        _mat_accesser.reset();
        auto itr = InitList.begin();
        for (int i = 0; i < size; ++i, ++itr)
        {
            _mat_accesser.at(i) = *itr;
        }
    }
    jMatBase(const jMatBase &rhs) : _mat_ptr(std::shared_ptr<Type>(new Type[size], std::default_delete<Type[]>())), _mat_accesser(Degree, Degree, _mat_ptr)
    {
        if (std::is_arithmetic<Type>::value)
            memcpy(_mat_ptr.get(), rhs._mat_ptr.get(), size * sizeof(Type));
        else
            for (int i = 0; i < size; ++i)   _mat_ptr.get()[i] = rhs._mat_ptr.get()[i];
    }
    jMatBase(jMatBase &&rhs) noexcept : _mat_accesser(Degree, Degree, rhs._mat_ptr)
    {
        _mat_ptr = rhs._mat_ptr;
        rhs._mat_ptr = nullptr;
    }
    jMatBase& operator=(const jMatBase &rhs)
    {
        if (this != &rhs)
        {
            if (std::is_arithmetic<Type>::value)
                memcpy(_mat_ptr.get(), rhs._mat_ptr.get(), size * sizeof(Type));
            else
                for (int i = 0; i < size; ++i)   _mat_ptr.get()[i] = rhs._mat_ptr.get()[i];
        }
        return *this;
    }
    jMatBase& operator=(jMatBase &&rhs) noexcept
    {
        if (this != &rhs)
        {
            _mat_ptr = rhs._mat_ptr;
            rhs._mat_ptr = nullptr;
            _mat_accesser.bindPtr(_mat_ptr);
        }
        return *this;
    }

    Type & at(size_t col, size_t row) {
        return _mat_accesser.at(col, row);
    }
    Type & at(size_t raw_pos) {
        return _mat_accesser.at(raw_pos);
    }
    const Type & at(size_t col, size_t row) const {
        return _mat_accesser.at(col, row);
    }
    const Type & at(size_t raw_pos) const {
        return _mat_accesser.at(raw_pos);
    }
    typename jGrid<Type>::col_itr_pair col_at(int col)
    {
        return _mat_accesser.col_at(col);
    }
    typename jGrid<Type>::const_col_itr_pair col_at(int col) const
    {
        return _mat_accesser.col_at(col);
    }
    typename jGrid<Type>::row_itr_pair row_at(int row)
    {
        return _mat_accesser.row_at(row);
    }
    typename jGrid<Type>::const_row_itr_pair row_at(int row) const
    {
        return _mat_accesser.row_at(row);
    }
public:
    inline static const jMatBase zero(){ return jMatBase(); }
    inline static const jMatBase identity()
    {
        jMatBase ret;
        for (int i = 0; i < Degree; ++i)
        {
            ret._mat_accesser.at(i, i) = Type(1);
        }
        return ret;
    }

    template<typename Type, size_t Degree>
    inline friend const jMatBase<Type, Degree> inverse(const jMatBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree>
    inline friend const jMatBase<Type, Degree> adjoint(const jMatBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree>
    inline friend const Type determinant(const jMatBase<Type, Degree> &rhs);

    template<typename Type, size_t Degree>
    inline friend const jMatBase<Type, Degree> operator+ (const jMatBase<Type, Degree> &lhs, const jMatBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree>
    inline friend const jMatBase<Type, Degree> operator- (const jMatBase<Type, Degree> &lhs, const jMatBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree>
    inline friend const jMatBase<Type, Degree> operator* (const jMatBase<Type, Degree> &lhs, const jMatBase<Type, Degree> &rhs);
    template<typename Type, size_t Degree>
    inline friend const jVecBase<Type, Degree> operator* (const jMatBase<Type, Degree> &lmat, const jVecBase<Type, Degree> &rvec);  //列乘法
    template<typename Type, size_t Degree>
    inline friend const jVecBase<Type, Degree> operator* (const jVecBase<Type, Degree> &lvec, const jMatBase<Type, Degree> &rmat);  //行乘法
private:
    std::shared_ptr<Type> _mat_ptr;
    jGrid<Type> _mat_accesser;
};

template <typename Type, size_t Degree>
std::ostream& operator<< (std::ostream& os, const jMatBase<Type, Degree> &outMat) {
    for (int row = 0; row < Degree; ++row)
    {
        auto row_itr = outMat.row_at(row);
        for (auto & val : row_itr)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    return os;
}

template<typename Type, size_t Degree>
inline const jMatBase<Type, Degree> operator+ (const jMatBase<Type, Degree> &lhs, const jMatBase<Type, Degree> &rhs)
{
    jMatBase<Type, Degree> ret = lhs;
    for (int i = 0; i < jMatBase<Type, Degree>::size; ++i)  ret.at(i) += rhs.at(i);
    return ret;
}

template<typename Type, size_t Degree>
inline const jMatBase<Type, Degree> operator- (const jMatBase<Type, Degree> &lhs, const jMatBase<Type, Degree> &rhs)
{
    jMatBase<Type, Degree> ret = lhs;
    for (int i = 0; i < jMatBase<Type, Degree>::size; ++i)  ret.at(i) -= rhs.at(i);
    return ret;
}

template<typename Type, size_t Degree>
inline const jMatBase<Type, Degree> operator* (const jMatBase<Type, Degree> &lhs, const jMatBase<Type, Degree> &rhs)
{
    jMatBase<Type, Degree> ret;
    for (int i = 0; i < Degree; ++i)
        for (int j = 0; j < Degree; ++j)
            for (int k = 0; k < Degree; ++k)
                ret.at(i, j) += lhs.at(k, j) * rhs.at(i, k);
    return ret;
}

template<typename Type, size_t Degree>
inline const jVecBase<Type, Degree> operator* (const jMatBase<Type, Degree> &lmat, const jVecBase<Type, Degree> &rvec)  //列乘法
{
    jVecBase<Type, Degree> ret;
    for (int i = 0; i < Degree; ++i)
        for (int j = 0; j < Degree; ++j)
            ret[i] += lmat.at(j, i) * rvec[j];
    return ret;
}

template<typename Type, size_t Degree>
inline const jVecBase<Type, Degree> operator* (const jVecBase<Type, Degree> &lvec, const jMatBase<Type, Degree> &rmat)  //行乘法
{
    jVecBase<Type, Degree> ret;
    for (int i = 0; i < Degree; ++i)
        for (int j = 0; j < Degree; ++j)
            ret[i] += lvec[j] * rmat.at(i, j);
    return ret;
}

template<typename Type, size_t Degree>
inline const Type determinant(const jMatBase<Type, Degree> &rhs)
{
    return jMPL::determinantOfMatrix<Type, Degree>::invoke(rhs);
}

template<typename Type, size_t Degree>
inline const jMatBase<Type, Degree> adjoint(const jMatBase<Type, Degree> &rhs)
{
    auto ret = jMatBase<Type, Degree>();
    for (int i = 0; i < Degree; ++i)
    {
        for (int j = 0; j < Degree; ++j)
        {
            auto tmp = jMatBase<Type, Degree - 1>();
            for (int m = 0; m < Degree - 1; ++m) {
                for (int n = 0; n < Degree - 1; ++n) {
                    tmp.at(m, n) = rhs.at((m < i ? m : m + 1), (n < j ? n : n + 1));
                }
            }
            ret.at(j, i) = ((i + j) % 2 == 0 ? 1 : -1) * determinant(tmp);
        }
    }
    return ret;
}

template<typename Type, size_t Degree>
inline const jMatBase<Type, Degree> inverse(const jMatBase<Type, Degree> &rhs)
{
    Type det = determinant(rhs);
    if (det == 0) det = std::numeric_limits<Type>::epsilon();
    auto ret = adjoint(rhs);
    for (int i = 0; i < Degree; ++i)
    {
        for (int j = 0; j < Degree; ++j)
        {
            ret.at(i, j) = ret.at(i, j) / det;
        }
    }
    return ret;
}

}}

#include "jTestBase.h"
namespace jLib {
    class jMatBaseTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();
            using namespace jContainer;

            jMatBase<float, 5> fm = {
                1, 1, 1, 1, 1,
                1, 2, 3, 4, 5,
                1, 5, 1, 2, 3,
                1, 3, 9, 5, 6,
                2, 0, 3, 2, 9
            };
            std::cout << inverse(fm) << std::endl;
            getchar();
        }
    };
}