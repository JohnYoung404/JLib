#pragma once
#include "jMPL.h"

#ifdef __COUNTER__
#   define ANONYMOUS_VARIABLE concat(__var_ , __COUNTER__)
#else
#   define ANONYMOUS_VARIABLE concat(__var_ , __LINE__)
#endif