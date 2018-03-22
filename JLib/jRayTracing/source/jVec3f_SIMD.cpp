#include "jVec3f_SIMD.h"

namespace jRayTracing 
{
    J_ALIGN(16) const jVec3f_SIMD jVec3f_SIMD::_zero = jVec3f_SIMD(0, 0, 0);
}