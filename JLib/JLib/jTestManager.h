#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <type_traits>
#include "jTestBase.h"


namespace jLib {

class jTestManager{
public:

	static jTestManager& instance(){
			return *_instance_ptr;
		}

    template<typename TestClass>
    std::enable_if_t<std::is_base_of<jITestable, TestClass>::value, void>   // if TestClass is not testable, report compile error.
    regist() {
			_allTestCase.push_back(std::shared_ptr<jITestable>(new TestClass()));
        }

	void doAllTest() {
			for (auto testPtr : _allTestCase)
			{
                testPtr->test();
			}
		}
private:
    jTestManager();
	static std::shared_ptr<jTestManager> _instance_ptr;
	std::vector<std::shared_ptr<jITestable> > _allTestCase;
};

	
}