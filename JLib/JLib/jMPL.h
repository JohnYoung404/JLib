// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]
#pragma once
#include <iterator>
#include "jOpsMPL.h"

#define _concat(s1, s2) s1 ## s2
#define  concat(s1, s2) _concat(s1, s2)

template<int Length, typename It>
struct _sumOfArray {
    enum {
        loop_times = _div<Length, 4>::value,
        rest_elems_num = _mod<Length, 4>::value,
        beg_pos = loop_times * 4
    };
    typedef typename std::iterator_traits<It>::value_type value_type;
    inline static value_type result(It it) {
        value_type v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0;

        for (int i = 0; i < loop_times; ++i)
        {
            v1 += *(it + i * 4);
            v2 += *(it + i * 4 + 1);
            v3 += *(it + i * 4 + 2);
            v4 += *(it + i * 4 + 3);
        }
        for (int i = 0; i < rest_elems_num; ++i)
        {
            v5 += *(it + beg_pos + i);
        }
        return v1 + v2 + v3 + v4 + v5;
    }
};

///<summary>
///Use meta programming to extend loop, though normally compiler will do it for you.
///</summary>
template<int Length, typename It>
inline typename std::iterator_traits<It>::value_type 
sumOfArray(It it) {
    return _sumOfArray<Length, It>::result(it);
}

template <typename Type, size_t N>
size_t ArraySize(const Type (&arr)[N]) {
    return N;
}
