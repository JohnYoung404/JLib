#include "jTestManager.h"
#include "jRange.h"
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
#include "jAdjacentPointPair.h"
#include "jIntString.h"
#include "jBigInt.h"
#include "jBitMap.h"
#include "jPerlinNoise.h"
#include "jCanvas.h"
#include "jVector.h"

namespace jLib
{

jTestManager::jTestManager()
{
    //regist<jRangeTest>();
    //regist<jConstableTest>();
    //regist<jHanaTest>();
    //regist<jBoostComputeTest>();
    //regist<jMsmTest>();
    //regist<jGridTest>();
    //regist<jMPLTest>();
    //regist<jGraphSearchTest>();
    //regist<jGraphGridTest>();
    //regist<jStringUtilTest>();
    //regist<jHashTest>();
    //regist<jAdjacentPointPairTest>();
	//regist<jIntStringTest>();
	//regist<jBigIntTest>();
	//regist<jBitMapTest>();
	//regist<jPerlinNoiseTest>();
    //regist<jCanvasTest>();
    regist<jVecBaseTest>();
    regist<jTupleMPLTest>();
}

std::unique_ptr<jTestManager> jTestManager::_instance_ptr = std::unique_ptr<jTestManager>(new jTestManager());	// singleton, will be destroyed when program exit,
                                                                                                                    // so memory-leak checker may report false positive.

}