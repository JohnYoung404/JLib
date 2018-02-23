#pragma once

#ifdef _MSC_VER
#define jforceinline __forceinline
#endif

#ifdef __GNUC__
#define jforceinline inline __attribute__((always_inline))
#endif

#ifdef _MSC_VER
#define jDefaultDeprecatedMsg "Function is Deprecated. Contact JohnYoung404@outlook.com for more info."
#define jDeprecated __declspec(deprecated(jDefaultDeprecatedMsg))
#else
#define jDeprecated
#endif

#include <algorithm>

namespace jLib
{

    

}