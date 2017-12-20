#pragma once
//#include "boost/compute/core.hpp"			//...You can't even include it without considering testing it...
#include "jTestBase.h"

//namespace compute = boost::compute;

namespace jLib {
	class jBoostComputeTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			//compute::device d = compute::system::default_device();
		}
	};
}