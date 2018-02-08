#pragma once
#include <memory>
#include "jVector.h"

namespace jLib {
namespace jGraphic {

class jIRayTracableMaterial;

class jRay
{
public:
    jRay(jVec3f origin, jVec3f direciton) : _origin(origin), _direction(direciton), _inv_direction(jVec3f(1.f/direciton[0], 1.f/direciton[1], 1.f/direciton[2])) {}
    inline const jVec3f Origin() const { return _origin; }
    inline const jVec3f Direction() const { return _direction; }
    inline const jVec3f InvDirection() const { return _inv_direction; }
protected:
    jVec3f _origin;
    jVec3f _direction;
    jVec3f _inv_direction;
};

class jRayObjectItersection
{
public:
    jRayObjectItersection(bool hit = false, jfloat dist = 0, jVec3f norm = jVec3f::zero(), std::shared_ptr<jIRayTracableMaterial> materialPtr = nullptr) : _hit(hit), _dist(dist), _norm(norm), _materialPtr(materialPtr) {}
    inline const bool hit() const { return _hit; }
    inline const jfloat dist() const { return _dist; }
    inline const jVec3f norm() const { return _norm; }
    inline std::shared_ptr<jIRayTracableMaterial> materialPtr() { return _materialPtr; }

private:
    bool _hit;
    jfloat _dist;
    jVec3f _norm;
    std::shared_ptr<jIRayTracableMaterial> _materialPtr;
};

}}