#pragma once
#include "jVector.h"
#include "jRay.h"
#include "jUtility.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

class jSceneObj
{
public:
    virtual ~jSceneObj() {};
    inline const jVec3f& get_pos() const { return _pos; }
    virtual jRayObjectItersection get_intersection(const jRay & ray) = 0;
protected:
    jSceneObj(jVec3f pos) : _pos(pos) {}
    jVec3f _pos;
};

NAME_SPACE_END
NAME_SPACE_END