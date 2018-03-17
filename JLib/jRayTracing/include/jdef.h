#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/17/2018]
// Description : definitions/declarations for some commonly standard declaration.

#if defined(__INTEL_COMPILER) || defined(__ICL)
#include <cstddef>
#define J_RESTRICT              __restrict
#define J_FORCE_INLINE          __forceinline
#define J_ALIGN(a)              __declspec(align(a))
#define J_DLLIMPORT             __declspec(dllimport)
#define J_DLLEXPORT             __declspec(dllexport)
#define J_DECLARE_C             __cdecl

#elif defined(_MSC_VER) 
#include <cstddef>
#define J_RESTRICT              __restrict
#define J_FORCE_INLINE          __forceinline
#define J_ALIGN(a)              __declspec(align(a))
#define J_DLLIMPORT             __declspec(dllimport)
#define J_DLLEXPORT             __declspec(dllexport)
#define J_DECLARE_C             __cdecl

#pragma warning( disable : 4996)

#elif defined(__GNUC__)
#include <cstddef>
#if ((__GNUC__ >= 3) && (__GNUC_MINOR__ >= 1)) || (__GNUC__ >= 4)
#ifdef _DEBUG
#ifndef J_FORCE_INLINE
#define J_FORCE_INLINE      inline 
#endif  
#else
#ifndef J_FORCE_INLINE
#define J_FORCE_INLINE      inline __attribute__((always_inline))
#endif
#endif
#endif

#define J_ALIGN(a)          __attribute__ ((aligned(a)))
#endif

#ifndef J_RESTRICT
#define J_RESTRICT
#endif

#ifndef J_FORCE_INLINE	
#define J_FORCE_INLINE      inline
#endif


#ifndef J_ALIGN
#define J_ALIGN(a)
#endif

#ifndef J_DLLIMPORT
#define J_DLLIMPORT
#endif

#ifndef J_DLLEXPORT
#define J_DLLEXPORT
#endif

#ifndef J_DECLARE_C
#define J_DECLARE_C
#endif