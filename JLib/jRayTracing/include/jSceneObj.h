#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/20/2018]
// Description : base class of scene objects.

#include "jCommon.h"
#include "jVec3f_SIMD.h"
#include "jIntersection.h"

namespace jRayTracing
{ 

J_ALIGN(16) class jSceneObj
{
public:
    virtual ~jSceneObj() {};
    inline const jVec3f& get_pos() const { return _pos; }
    virtual jRayObjectItersection get_intersection(const jRay & ray) = 0;
protected:
    jSceneObj(const jVec3f &pos) : _pos(pos) {}
    jVec3f _pos;
};

}