#pragma once

#ifdef _MSC_VER
#ifdef _DEBUG  
 
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <string>
//#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)

#define JCheckMemory() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG)
#define JPauseWhenMemAllocTimesIs(times) _CrtSetBreakAlloc(times)

#endif
#endif