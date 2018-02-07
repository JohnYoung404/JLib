#pragma once
#include "jVector.h"

namespace jLib {
namespace jGraphic {

class jSceneObj
{
public:
    virtual ~jSceneObj() {};
    inline virtual const jVec3f get_pos() const { return _pos; }
protected:
    jSceneObj(jVec3f pos) : _pos(pos) {}
    jVec3f _pos;
};

}}