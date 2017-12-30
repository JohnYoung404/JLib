#include "jTestManager.h"

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
#include "jHash.h"

namespace jLib
{

jTestManager::jTestManager()
{
    //regist<jRangeTest>();
    //regist<jHeapTest>();
    //regist<jSudokuTest>();
    //regist<jConstableTest>();
    //regist<jHanaTest>();
    //regist<jBoostComputeTest>();
    //regist<jMsmTest>();
    //regist<jGridTest>();
    //regist<jMPLTest>();
    //regist<jGraphSearchTest>();
    regist<jGraphGridTest>();
    regist<jStringUtilTest>();
    regist<jHashTest>();
}

std::shared_ptr<jTestManager> jTestManager::_instance_ptr = std::shared_ptr<jTestManager>(new jTestManager());	// singleton, will be destroyed when program exit,
                                                                                                                    // so memory-leak checker may report false positive.

}