#pragma once
#include <cmath>
#include <cfloat>

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