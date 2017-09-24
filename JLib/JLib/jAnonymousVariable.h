// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]
// Description : Anonymous Variable Name.
#pragma once
#include "jMPL.h"

#ifdef __COUNTER__
#   define ANONYMOUS_VARIABLE concat(__var_ , __COUNTER__)
#else
#   define ANONYMOUS_VARIABLE concat(__var_ , __LINE__)
#endif