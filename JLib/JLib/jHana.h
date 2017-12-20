#pragma once
//#include "boost/hana.hpp"			//...You can't even include it without considering testing it...
#include "jTestBase.h"

//namespace hana = boost::hana;

namespace {
	//auto has_to_string = hana::is_valid([](auto t)->decltype(
	//	(void)hana::traits::declval(t).to_string;
	//) {});
	//
	//struct  aStruct
	//{
	//	int x;
	//};
}

namespace jLib {
	class jHanaTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			std::cout << "Haha" << std::endl;
			//int l;
			//aStruct s;
			//std::cout << has_to_string(l) << std::endl;
			//std::cout << has_to_string(s) << std::endl;
		}
	};
}