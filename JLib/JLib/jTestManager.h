// Author : John Young
// Contact : JohnYoung404@outlook.com
// Description : Test Manager to manage unit test.
#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <type_traits>
#include "jTypeTraits.h"
#include "jTestBase.h"

namespace jLib {

class jTestManager{
public:

    static jTestManager& instance(){
        return *_instance_ptr;
    }

    template<typename TestClass, jConstrain_typename_is_subclass(TestClass, jITestable)>
    void regist() {
        _allTestCase.push_back(std::unique_ptr<jITestable>(new TestClass()));
    }

    void doAllTest() {
        for (auto &testPtr : _allTestCase)
        {
            testPtr->test();
        }
    }
private:
    jTestManager();
    static std::unique_ptr<jTestManager> _instance_ptr;
    std::vector<std::unique_ptr<jITestable> > _allTestCase;
};

}