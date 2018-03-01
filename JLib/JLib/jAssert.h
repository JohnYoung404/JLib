#pragma once
#include <boost/assert.hpp>

#ifdef _DEBUG
#define jDebugAssert(pred) BOOST_ASSERT(pred)
#define jDebugAssertMsg(pred, msg) BOOST_ASSERT_MSG(pred, msg)
#else
#define jDebugAssert(pred)
#define jDebugAssertMsg(pred, msg)
#endif

#define jAllBuiltAssert BOOST_ASSERT

#define jAssert jDebugAssert
#define jAssertMsg jDebugAssertMsg