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
        const bool &ihit = false
        , const jReal &idist = std::numeric_limits<jReal>::max()
        , const jVec3f &inorm = jVec3f::zero()
        , const jVec3f &icolor = jVec3f::zero()
        , const jVec3f &iemission = jVec3f::zero()
        , const matType &itype = matType::DIFF
    ) : _hit(ihit), _dist(idist), _norm(inorm), _color(icolor), _emission(iemission), _type(itype) {}
    inline const bool& hit() const { return _hit; }
    inline const jReal& dist() const { return _dist; }
    inline const jVec3f& norm() const { return _norm; }
    inline const jVec3f& color() const { return _color; }
    inline const jVec3f& emission() const { return _emission; }
    inline const matType get_type() const { return _type; }
    //inline const std::shared_ptr<jIRayTracableMaterial> &materialPtr() const { return _materialPtr; }

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