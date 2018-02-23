#pragma once

#ifdef _MSC_VER
#define jforceinline __forceinline
#endif

#ifdef __GNUC__
#define jforceinline inline __attribute__((always_inline))
#endif

#define jDefaultDeprecatedMsg "Function is Deprecated. Contact JohnYoung404@outlook.com for more info."
#define jDeprecated __declspec(deprecated(jDefaultDeprecatedMsg))

#include <algorithm>

namespace jLib
{

    

}