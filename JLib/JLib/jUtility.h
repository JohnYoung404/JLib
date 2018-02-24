#pragma once

#ifdef _MSC_VER
#define jforceinline __forceinline
#define jAlign(bit) __declspec(align(bit))
#endif

#ifdef __GNUC__
#define jforceinline inline __attribute__((always_inline))
#define jAlign(bit) __attribute__((aligned(bit)))
#endif

#ifdef _MSC_VER
#define jDefaultDeprecatedMsg "Function is Deprecated. Contact JohnYoung404@outlook.com for more info."
#define jDeprecated __declspec(deprecated(jDefaultDeprecatedMsg))
#else
#define jDeprecated
#endif

namespace jLib
{

    

}