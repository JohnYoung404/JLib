#include "jSphere.h"

namespace jLib {
namespace jGraphic {

jRayObjectItersection jSphere::get_intersection(const jRay& ray)
{
    bool hit = false;
    jfloat distance = 0;
    jVec3f norm = jVec3f::zero();

    jVec3f op = _pos - ray.Origin();
    jfloat t, eps = 1e-4, b = op.dot(ray.Direction()), det = b*b - op.dot(op) + _radius*_radius;
    if (det < 0) return jRayObjectItersection(hit, distance, norm, _materialPtr);
    else det = sqrt(det);
    distance = (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
    if (distance != 0) hit = true,
        norm = ((ray.Origin() + ray.Direction() * distance) - _pos).normalize();

    return jRayObjectItersection(hit, distance, norm, _materialPtr);
}

}}