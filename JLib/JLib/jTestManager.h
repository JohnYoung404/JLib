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
#include "jGrid.cpp"
#include "jMPL.h"
#include "jGraphSearch.h"
#include "jGraphGrid.h"

namespace jLib {

	class jTestManager{
	public:
		static jTestManager& instance(){
			return *instance_ptr_;
		}

        template<typename TestClass>
        std::enable_if_t<std::is_base_of<jITestable, TestClass>::value, void>   // if TestClass is not testable, report compile error.
        /*void*/ regist() {
            allTestCase_.push_back(std::shared_ptr<jITestable>(new TestClass()));
        }

		void clearTest() {
			allTestCase_.clear();
		}
		void doAllTest() {
			for (auto testPtr : allTestCase_)
			{
                testPtr->test();
			}
		}
	private:
        jTestManager();
		static std::shared_ptr<jTestManager> instance_ptr_;
		std::vector<std::shared_ptr<jITestable> > allTestCase_;
	};

	std::shared_ptr<jTestManager> jTestManager::instance_ptr_ = std::shared_ptr<jTestManager>(new jTestManager());	// singleton, will be destroyed when program exit,
																													// so memory-leak checker may report false positive.
    jTestManager::jTestManager() {
        //regist<jRangeTest>();
        //regist<jHeapTest>();
        //regist<jSudokuTest>();
		//regist<jConstableTest>();
		//regist<jHanaTest>();
		//regist<jBoostComputeTest>();
		//regist<jMsmTest>();
		//regist<jGridTest>();
		//regist<jMPLTest>();
		regist<jGraphSearchTest>();
		regist<jGraphGridTest>();
    }
}