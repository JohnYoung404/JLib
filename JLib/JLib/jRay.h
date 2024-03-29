#pragma once
#include <memory>
#include "jUtility.h"
#include "jVector.h"
#include "jMaterial.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

enum class matType;
class jIRayTracableMaterial;

class jRay //: jObjCounter<jRay>
{
public:
    jRay(jVec3f origin, jVec3f direciton)
        : _origin(origin)
        , _direction(direciton)
        , _inv_direction(jVec3f(jfloat(1) / direciton.x(), jfloat(1) / direciton.y(), jfloat(1) / direciton.z()))
        , code_x(direciton.x() > 0 ? 01 : 10)
        , code_y(direciton.y() > 0 ? 01 : 10)
        , code_z(direciton.z() > 0 ? 01 : 10)
    {}
    inline const jVec3f& Origin() const { return _origin; }
    inline const jVec3f& Direction() const { return _direction; }
    inline const jVec3f& InvDirection() const { return _inv_direction; }

    unsigned char code_x;   //加速求交的空间码
    unsigned char code_y;
    unsigned char code_z;
private:
    jVec3f _origin;
    jVec3f _direction;
    jVec3f _inv_direction;
};

class jRayObjectItersection
{
public:
    jRayObjectItersection
    (
        bool ihit = false
        , jfloat idist = std::numeric_limits<jfloat>::max()
        , jVec3f inorm = jVec3f::zero()
        , jVec3f icolor = jVec3f::zero()
        , jVec3f iemission = jVec3f::zero()
        , matType itype = matType::DIFF
    ) : _hit(ihit), _dist(idist), _norm(inorm), _color(icolor), _emission(iemission), _type(itype) {}
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

NAME_SPACE_END
NAME_SPACE_END