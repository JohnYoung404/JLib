#pragma once
#include <boost/assert.hpp>

#ifdef _DEBUG
#define jDebugAssert BOOST_ASSERT
#define jDebugAssertMsg BOOST_ASSERT_MSG
#else
#define jDebugAssert
#define jDebugAssertMsg
#endif

#define jAllBuiltAssert BOOST_ASSERT

#define jAssert jDebugAssert
#define jAssertMsg jDebugAssertMsg