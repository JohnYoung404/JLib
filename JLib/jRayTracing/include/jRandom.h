#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/20/2018]
// Description : A wrapper for erand.

#include "jCommon.h"

namespace jRayTracing
{
    extern jReal jerand48(unsigned short(&xseed)[3]);
}