#pragma once
#include <memory>
#include <vector>

namespace jLib {

	struct jITestable
	{
		virtual void test() = 0;
	};

	class jTestManager{
	public:
		static jTestManager& instance(){
			return *instance_ptr_;
		}

		void regist() {
			
		}

		void addTest(std::shared_ptr<jITestable> testToAdd) {
			allTestCase_.push_back(testToAdd);
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

	std::shared_ptr<jTestManager> jTestManager::instance_ptr_ = std::shared_ptr<jTestManager>(new jTestManager());
	jTestManager::jTestManager() {
		regist();
	}
}