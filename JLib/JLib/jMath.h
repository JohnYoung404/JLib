#pragma once
#include <cmath>
#include <cfloat>
#include <limits> 

#define PI 3.14159265359
#define GOLDEN_DIVNUM_OF_32_BIT 2654435769
#define POS_INFINITY DBL_MAX
#define NEG_INFINITY (-POS_INFINITY)
#define NEG_ZERO (-1.0/POS_INFINITY)

inline bool AlmostEqual(float lhs, float rhs) {
	if (lhs == 0)
	{
		return abs(rhs) < FLT_EPSILON;
	}
	else {
		return abs(lhs - rhs) / abs(lhs) < FLT_EPSILON;
	}
}

 
namespace Detail
{
    template<typename FloatType, jConstrain_typename_floating_point(FloatType)>
    FloatType constexpr sqrtNewtonRaphson(FloatType x, FloatType curr, FloatType prev)
    {
        return curr == prev
            ? curr
            : sqrtNewtonRaphson<FloatType>(x, (FloatType)0.5 * (curr + x / curr), curr);
    }
}

/*
* Constexpr version of the square root
* Return value:
*   - For a finite and non-negative value of "x", returns an approximation for the square root of "x"
*   - Otherwise, returns NaN
*/

namespace jLib {
template<typename FloatType, jConstrain_typename_floating_point(FloatType)>
FloatType constexpr constable_sqrt(FloatType x)
{
    return x >= 0 && x < std::numeric_limits<FloatType>::infinity()
        ? Detail::sqrtNewtonRaphson<FloatType>(x, x, 0)
        : std::numeric_limits<FloatType>::quiet_NaN();
}
}