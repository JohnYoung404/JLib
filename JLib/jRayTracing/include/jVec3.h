#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [4/17/2018]
// Description : 3D-Vector define.

#include "jVec3d_fpu.h"
#include "jVec3d_fpu_heapAlloc.h"
#include "jVec3f_fpu.h"
#include "jVec3f_SIMD.h"

namespace jRayTracing
{
	using  jVec3f = jVec3d_fpu_heapAlloc;
}