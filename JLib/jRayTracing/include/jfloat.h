#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/17/2018]
// Description : float types definitions.

#include <limits>
#include "jdef.h"

namespace jRayTracing
{

#ifdef J_DBL_PRECISION
    using jReal = double;
#else
    using jReal = float;
#endif

}