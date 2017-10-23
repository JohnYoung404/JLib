#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define JCheckMemory _CrtDumpMemoryLeaks	// When singletons exist, it may report false positive.
											// It can't be placed in the global scope.