#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <type_traits>

#include "jTestBase.h"
#include "jRange.h"
#include "jSudoku.h"
#include "jConstableClass.h"
#include "jHana.h"
#include "jBoostCompute.h"
#include "jMetaStateMachine.h"
#include "jMPL.h"
#include "jGraphSearch.h"
#include "jGraphGrid.h"
#include "jStringUtil.h"
#include "jGrid.h"

namespace jLib {

	class jTestManager{
	public:
		static jTestManager& instance(){
			return *_instance_ptr;
		}

        template<typename TestClass>
        std::enable_if_t<std::is_base_of<jITestable, TestClass>::value, void>   // if TestClass is not testable, report compile error.
        /*void*/ regist() {
			_allTestCase.push_back(std::shared_ptr<jITestable>(new TestClass()));
        }

		void clearTest() {
			_allTestCase.clear();
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

	std::shared_ptr<jTestManager> jTestManager::_instance_ptr = std::shared_ptr<jTestManager>(new jTestManager());	// singleton, will be destroyed when program exit,
																													// so memory-leak checker may report false positive.
    jTestManager::jTestManager() {
        //regist<jRangeTest>();
        //regist<jHeapTest>();
        //regist<jSudokuTest>();
		//regist<jConstableTest>();
		//regist<jHanaTest>();
		//regist<jBoostComputeTest>();
		//regist<jMsmTest>();
		regist<jGridTest>();
		//regist<jMPLTest>();
		//regist<jGraphSearchTest>();
		regist<jGraphGridTest>();
		regist<jStringUtilTest>();
    }
}