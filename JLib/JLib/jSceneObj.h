#pragma once
#include "jVector.h"
#include "jRay.h"

namespace jLib {
namespace jGraphic {

class jSceneObj
{
public:
    virtual ~jSceneObj() {};
    virtual const jVec3f get_pos() const { return _pos; }
    virtual jRayObjectItersection get_intersection(const jRay & ray) = 0;
protected:
    jSceneObj(jVec3f pos) : _pos(pos) {}
    jVec3f _pos;
};

}}