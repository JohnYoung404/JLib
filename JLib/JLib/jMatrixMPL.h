// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [1/27/2018]
// Description : calculate determinant of matrix with different degrees.
#pragma once
#include "jUtility.h"

namespace jLib{
namespace jContainer{
    template<typename Type, size_t Degree>
    class jMatBase;                         //Forward Statement;
}}

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jMPL)

template<typename Type, size_t Degree, jConstrain_typename_floating_point(Type)>
struct determinantOfMatrix {
    inline static const Type invoke(const jContainer::jMatBase<Type, Degree> &rhs) {
        Type dsum = 0, dsign = 1;
        for (int i = 0; i < Degree; ++i)
        {
            jContainer::jMatBase<Type, Degree - 1> tmp;
            for (int j = 0; j < Degree - 1; ++j)
            {
                for (int k = 0; k < Degree - 1; ++k)
                {
                    tmp.at(j, k) = rhs.at(j + 1, (k >= i ? k + 1 : k));
                }
            }
            dsum += rhs.at(0, i) * dsign * determinantOfMatrix<Type, Degree - 1>::invoke(tmp);
            dsign = -1 * dsign;
        }
        return dsum;
    }
};

template<typename Type>
struct determinantOfMatrix<Type, 0> {
    inline static const Type invoke(const jContainer::jMatBase<Type, 0> &rhs) {
        return 0;
    }
};

template<typename Type>
struct determinantOfMatrix<Type, 1> {
    inline static const Type invoke(const jContainer::jMatBase<Type, 1> &rhs) {
        return rhs.at(0, 0);
    }
};

template<typename Type>
struct determinantOfMatrix<Type, 2> {
    inline static const Type invoke(const jContainer::jMatBase<Type, 2> &rhs) {
        return rhs.at(0, 0) * rhs.at(1, 1) - rhs.at(0, 1) * rhs.at(1, 0);
    }
};

template<typename Type>
struct determinantOfMatrix<Type, 3> {
    inline static const Type invoke(const jContainer::jMatBase<Type, 3> &rhs) {
        return rhs.at(0, 0) * rhs.at(1, 1) * rhs.at(2, 2) + rhs.at(0, 1) * rhs.at(1, 2) * rhs.at(2, 0)
            + rhs.at(0, 2) * rhs.at(1, 0) * rhs.at(2, 1) - rhs.at(0, 2) * rhs.at(1, 1) * rhs.at(2, 0)
            - rhs.at(0, 0) * rhs.at(1, 2) * rhs.at(2, 1) - rhs.at(0, 1) * rhs.at(1, 0) * rhs.at(2, 2);
    }
};

template<typename Type>
struct determinantOfMatrix<Type, 4> {
    inline static const Type invoke(const jContainer::jMatBase<Type, 4> &rhs) {
        const Type _3142_3241(rhs.at(0, 2) * rhs.at(1, 3) - rhs.at(1, 2) * rhs.at(0, 3));
        const Type _3143_3341(rhs.at(0, 2) * rhs.at(2, 3) - rhs.at(2, 2) * rhs.at(0, 3));
        const Type _3144_3441(rhs.at(0, 2) * rhs.at(3, 3) - rhs.at(3, 2) * rhs.at(0, 3));
        const Type _3243_3342(rhs.at(1, 2) * rhs.at(2, 3) - rhs.at(2, 2) * rhs.at(1, 3));
        const Type _3244_3442(rhs.at(1, 2) * rhs.at(3, 3) - rhs.at(3, 2) * rhs.at(1, 3));
        const Type _3344_3443(rhs.at(2, 2) * rhs.at(3, 3) - rhs.at(3, 2) * rhs.at(2, 3));
        return    rhs.at(0, 0) * (rhs.at(1, 1) * _3344_3443 - rhs.at(2, 1) * _3244_3442 + rhs.at(3, 1) * _3243_3342)
            - rhs.at(1, 0) * (rhs.at(0, 1) * _3344_3443 - rhs.at(2, 1) * _3144_3441 + rhs.at(3, 1) * _3143_3341)
            + rhs.at(2, 0) * (rhs.at(0, 1) * _3244_3442 - rhs.at(1, 1) * _3144_3441 + rhs.at(3, 1) * _3142_3241)
            - rhs.at(3, 0) * (rhs.at(0, 1) * _3243_3342 - rhs.at(1, 1) * _3143_3341 + rhs.at(2, 1) * _3142_3241);
    }
};

NAME_SPACE_END
NAME_SPACE_END