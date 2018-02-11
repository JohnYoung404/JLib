#pragma once
#include <memory>
#include "jVector.h"
#include "jMaterial.h"

namespace jLib {
namespace jGraphic {

enum class matType;
class jIRayTracableMaterial;

class jRay
{
public:
    jRay(jVec3f origin, jVec3f direciton) : _origin(origin), _direction(direciton), _inv_direction(jVec3f(jfloat(1)/direciton.x(), jfloat(1)/direciton.y(), jfloat(1)/direciton.z())) {}
    inline const jVec3f& Origin() const { return _origin; }
    inline const jVec3f& Direction() const { return _direction; }
    inline const jVec3f& InvDirection() const { return _inv_direction; }
private:
    jVec3f _origin;
    jVec3f _direction;
    jVec3f _inv_direction;
};

class jRayObjectItersection
{
public:
    jRayObjectItersection(bool ihit = false, jfloat idist = 0, jVec3f inorm = jVec3f::zero(), const std::shared_ptr<jIRayTracableMaterial> &matPtr = nullptr) : _hit(ihit), _dist(idist), _norm(inorm) 
    {
        if (matPtr.use_count())
        {
            _color = matPtr->get_color();
            _emission = matPtr->get_emission();
            _type = matPtr->get_type();
        }
    }
    inline const bool& hit() const { return _hit; }
    inline const jfloat& dist() const { return _dist; }
    inline const jVec3f& norm() const { return _norm; }
    inline const jVec3f& color() const { return _color; }
    inline const jVec3f& emission() const { return _emission; }
    inline const matType get_type() const { return _type; }
    //inline const std::shared_ptr<jIRayTracableMaterial> &materialPtr() const { return _materialPtr; }

private:
    bool _hit;
    jfloat _dist;
    jVec3f _norm;

    jVec3f _color;
    jVec3f _emission;
    matType _type;
    //std::shared_ptr<jIRayTracableMaterial> _materialPtr;
};

}}