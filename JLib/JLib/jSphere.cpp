#include "jSphere.h"

namespace jLib {
namespace jGraphic {

jRayObjectItersection jSphere::get_intersection(const jRay& ray)
{
    bool hit = false;
    jfloat distance = 0;
    jVec3f norm = jVec3f::zero();

    jVec3f op = get_pos() - ray.Origin();
    jfloat t, eps = jfloat(1e-4), b = op.dot(ray.Direction()), det = b*b - op.dot(op) + get_square_radius();
    if (det < 0) return jRayObjectItersection(hit, distance, norm, _materialPtr);
    else det = sqrt(det);
    distance = (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
    if (distance != 0) hit = true,
        norm = ((ray.Origin() + ray.Direction() * distance) - get_pos()).normalize();

    return jRayObjectItersection(hit, distance, norm, _materialPtr);
}

}}