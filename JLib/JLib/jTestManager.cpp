#include "jTestManager.h"
#include "jRange.h"
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
#include "jArrayMPL.h"
#include "jTupleMPL.h"
#include "jMatrix.h"
#include "jMatrixCvt.h"

namespace jLib
{

jTestManager::jTestManager()
{
    //regist<jRangeTest>();
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
    //regist<jVecBaseTest>();
    //regist<jTupleMPLTest>();
    //regist<jArrayMPLTest>();
    regist<jMatBaseTest>();
    regist<jMatCvtTest>();
}

std::unique_ptr<jTestManager> jTestManager::_instance_ptr = std::unique_ptr<jTestManager>(new jTestManager());  //singleton

}