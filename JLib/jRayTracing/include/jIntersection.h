#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/20/2018]
// Description : Interaction of Ray and Scene Object.

#include "jCommon.h"
#include "jVec3f_SIMD.h"
#include "jMaterial.h"

namespace jRayTracing{

class jRayObjectItersection
{
public:
    jRayObjectItersection
    (
        bool ihit = false
        , jReal idist = std::numeric_limits<jReal>::max()
        , const jVec3f &inorm = jVec3f(0, 0, 0)
        , const jVec3f &icolor = jVec3f(0, 0, 0)
        , const jVec3f &iemission = jVec3f(0, 0, 0)
        , matType itype = matType::DIFF
    ) : _hit(ihit), _dist(idist), _norm(inorm), _color(icolor), _emission(iemission), _type(itype) {}
    J_FORCE_INLINE const bool& hit() const { return _hit; }
    J_FORCE_INLINE const jReal& dist() const { return _dist; }
    J_FORCE_INLINE const jVec3f& norm() const { return _norm; }
    J_FORCE_INLINE const jVec3f& color() const { return _color; }
    J_FORCE_INLINE const jVec3f& emission() const { return _emission; }
    J_FORCE_INLINE const matType get_type() const { return _type; }
    //J_FORCE_INLINE const std::shared_ptr<jIRayTracableMaterial> &materialPtr() const { return _materialPtr; }

private:
    bool _hit;
    jReal _dist;
    jVec3f _norm;

    jVec3f _color;
    jVec3f _emission;
    matType _type;
    //std::shared_ptr<jIRayTracableMaterial> _materialPtr;
};

}