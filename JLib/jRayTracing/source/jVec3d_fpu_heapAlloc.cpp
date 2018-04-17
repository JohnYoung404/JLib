#include "jVec3d_fpu_heapAlloc.h"

namespace jRayTracing
{
	thread_local boost::pool<> vecPool(3*sizeof(double));
}