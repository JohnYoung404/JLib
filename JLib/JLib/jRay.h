#pragma once
#include "jVector.h"

namespace jLib {
namespace jGraphic {

class jRay
{
public:
    jRay(jVec3f origin, jVec3f direciton) : _origin(origin), _direction(direciton), _inv_direction(jVec3f(1.f/direciton[0], 1.f/direciton[1], 1.f/direciton[2])) {}
    inline jVec3f Origin() const { return _origin; }
    inline jVec3f Direction() const { return _direction; }
    inline jVec3f InvDireciton() const { return _inv_direction; }
protected:
    jVec3f _origin;
    jVec3f _direction;
    jVec3f _inv_direction;
};

}}