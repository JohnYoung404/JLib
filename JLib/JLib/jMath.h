#pragma once
#include <cmath>
#include <cfloat>

#define PI 3.14159265359

inline bool AlmostEqual(float lhs, float rhs) {
    if (lhs == 0)
    {
        return abs(rhs) < FLT_EPSILON;
    }
    else {
        return abs(lhs - rhs) / abs(lhs) < FLT_EPSILON;
    }
}

