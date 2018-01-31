#pragma once
#include "jVector.h"

namespace jLib {
namespace jGraphic {

class jSceneObj
{
public:
    jSceneObj(jVec3f pos): _pos(pos){};
    virtual ~jSceneObj() {};
protected:
    jVec3f _pos;
};

}}