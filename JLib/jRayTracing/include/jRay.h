#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/18/2018]
// Description : Ray that represented by origin & direction.

#include <memory>
#include "jCommon.h"
#include "jVec3f_SIMD.h"

namespace jRayTracing
{

struct jRay
{
public:
    jRay(jVec3f origin, jVec3f direciton)
        : _origin(origin)
        , _direction(direciton)
        , _inv_direction(direciton.Reciprocal_cpy())
        , code_x(direciton.x() > 0 ? 01 : 10)
        , code_y(direciton.y() > 0 ? 01 : 10)
        , code_z(direciton.z() > 0 ? 01 : 10)
    {}
    J_FORCE_INLINE const jVec3f& Origin() const { return _origin; }
    J_FORCE_INLINE const jVec3f& Direction() const { return _direction; }
    J_FORCE_INLINE const jVec3f& InvDirection() const { return _inv_direction; }

    unsigned char code_x;   //加速求交的空间码
    unsigned char code_y;
    unsigned char code_z;
private:
    jVec3f _origin;
    jVec3f _direction;
    jVec3f _inv_direction;

};

}