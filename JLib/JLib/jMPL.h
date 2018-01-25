// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]
#pragma once
#include <iterator>
#include <functional>
#include <tuple>
#include "jOpsMPL.h"
#include "jMatrix.h"

#define _concat(s1, s2) s1 ## s2
#define  jconcat(s1, s2) _concat(s1, s2)

#ifdef __COUNTER__
#   define ANONYMOUS_VARIABLE jconcat(__var_ , __COUNTER__)
#else
#   define ANONYMOUS_VARIABLE jconcat(__var_ , __LINE__)
#endif

template<int Length, typename It>
struct _sumOfArray {
    enum {
        loop_times = jLib::_div<Length, 4>::value,
        rest_elems_num = jLib::_mod<Length, 4>::value,
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

/*
namespace jGraphic {
	template<size_t Degree, typename Type>
	struct determinantOfMatrix {
		inline static const Type invoke (const jMat_base<Degree, Type> &rhs) {
			Type dsum = 0, dsign = 1;
			for (int i = 0; i < Degree; ++i)
			{
				jMat_base<Degree - 1, Type> tmp = jMat_base<Degree - 1, Type>::Zero();
				for (int j = 0; j < Degree - 1; ++j)
				{
					for (int k = 0; k < Degree - 1; ++k)
					{
						tmp.RefOfPos(j, k) = rhs.RefOfPos(j + 1, (k >= i ? k + 1 : k));
					}
				}
				dsum += rhs.RefOfPos(0, i) * dsign * determinantOfMatrix<Degree - 1, Type>::invoke(tmp);
				dsign = -1 * dsign;
			}
			return dsum;
		}
	};

	template<typename Type>
	struct determinantOfMatrix<0, Type> {
		inline static const Type invoke(const jMat_base<0, Type> &rhs) {
			return 0;
		}
	};

	template<typename Type>
	struct determinantOfMatrix<1, Type> {
		inline static const Type invoke(const jMat_base<1, Type> &rhs) {
			return rhs.RefOfPos(0, 0);
		}
	};

	template<typename Type>
	struct determinantOfMatrix<2, Type> {
		inline static const Type invoke(const jMat_base<2, Type> &rhs) {
			return rhs.RefOfPos(0, 0) * rhs.RefOfPos(1, 1) - rhs.RefOfPos(0, 1) * rhs.RefOfPos(1, 0);
		}
	};

	template<typename Type>
	struct determinantOfMatrix<3, Type> {
		inline static const Type invoke(const jMat_base<3, Type> &rhs) {
			return rhs.RefOfPos(0, 0) * rhs.RefOfPos(1, 1) * rhs.RefOfPos(2, 2) + rhs.RefOfPos(0, 1) * rhs.RefOfPos(1, 2) * rhs.RefOfPos(2, 0)
				 + rhs.RefOfPos(0, 2) * rhs.RefOfPos(1, 0) * rhs.RefOfPos(2, 1) - rhs.RefOfPos(0, 2) * rhs.RefOfPos(1, 1) * rhs.RefOfPos(2, 0)
				 - rhs.RefOfPos(0, 0) * rhs.RefOfPos(1, 2) * rhs.RefOfPos(2, 1) - rhs.RefOfPos(0, 1) * rhs.RefOfPos(1, 0) * rhs.RefOfPos(2, 2);
		}
	};

	template<typename Type>
	struct determinantOfMatrix<4, Type> {
		inline static const Type invoke(const jMat_base<4, Type> &rhs) {
			const Type _3142_3241(rhs.RefOfPos(2, 0) * rhs.RefOfPos(3, 1) - rhs.RefOfPos(2, 1) * rhs.RefOfPos(3, 0));
			const Type _3143_3341(rhs.RefOfPos(2, 0) * rhs.RefOfPos(3, 2) - rhs.RefOfPos(2, 2) * rhs.RefOfPos(3, 0));
			const Type _3144_3441(rhs.RefOfPos(2, 0) * rhs.RefOfPos(3, 3) - rhs.RefOfPos(2, 3) * rhs.RefOfPos(3, 0));
			const Type _3243_3342(rhs.RefOfPos(2, 1) * rhs.RefOfPos(3, 2) - rhs.RefOfPos(2, 2) * rhs.RefOfPos(3, 1));
			const Type _3244_3442(rhs.RefOfPos(2, 1) * rhs.RefOfPos(3, 3) - rhs.RefOfPos(2, 3) * rhs.RefOfPos(3, 1));
			const Type _3344_3443(rhs.RefOfPos(2, 2) * rhs.RefOfPos(3, 3) - rhs.RefOfPos(2, 3) * rhs.RefOfPos(3, 2));
			return    rhs.RefOfPos(0, 0) * (rhs.RefOfPos(1, 1) * _3344_3443 - rhs.RefOfPos(1, 2) * _3244_3442 + rhs.RefOfPos(1, 3) * _3243_3342)
					- rhs.RefOfPos(0, 1) * (rhs.RefOfPos(1, 0) * _3344_3443 - rhs.RefOfPos(1, 2) * _3144_3441 + rhs.RefOfPos(1, 3) * _3143_3341)
					+ rhs.RefOfPos(0, 2) * (rhs.RefOfPos(1, 0) * _3244_3442 - rhs.RefOfPos(1, 1) * _3144_3441 + rhs.RefOfPos(1, 3) * _3142_3241)
					- rhs.RefOfPos(0, 3) * (rhs.RefOfPos(1, 0) * _3243_3342 - rhs.RefOfPos(1, 1) * _3143_3341 + rhs.RefOfPos(1, 2) * _3142_3241);
		}
	};
}*/

namespace jLib
{

namespace jMPL
{
	template<typename... Args, typename Func>
	void tuple_for_each(const std::tuple<Args...> &t, Func &f)
	{
		tuple_for_each_::__tuple_processor<decltype(t), Func, sizeof...(Args)>::__tuple_process(t, f);
	}

	namespace tuple_for_each_{
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
}

}

#include "jTestBase.h"

namespace jLib {
	class jMPLTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			auto t1 = std::make_tuple(1, "2", 3.4f);
			int n = 5;
			auto t2 = std::tuple_cat(t1, std::tie(n), std::make_pair(6, 7));
			jMPL::tuple_for_each(t2, [](auto &val) { std::cout << val << " "; });
			std::cout << std::endl;
		}
	};
}