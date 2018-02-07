#pragma once
#include "jVector.h"

namespace jLib {
namespace jGraphic {

class jSceneObj
{
public:
    virtual ~jSceneObj() {};
protected:
    jSceneObj(jVec3f pos) : _pos(pos) {}
    jVec3f _pos;
};

}}