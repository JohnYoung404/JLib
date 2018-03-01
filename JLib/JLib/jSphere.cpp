#include "jSphere.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

jRayObjectItersection jSphere::get_intersection(const jRay& ray)
{
    bool hit = false;
    jfloat distance = 0;
    jVec3f norm = jVec3f::zero();

    //if (!get_aabbox().test_area_code(ray)) return jRayObjectItersection(hit, distance, norm, _materialPtr->get_color(), _materialPtr->get_emission(), _materialPtr->get_type());
    //摄像机在几个sphere内部。。。所以是负优化

    jVec3f op = get_pos() - ray.Origin();
    jfloat t, eps = jfloat(1e-4), b = op.dot(ray.Direction()), det = b*b - op.dot(op) + get_square_radius();
    if (det < 0) return jRayObjectItersection(hit, distance, norm, _materialPtr->get_color(), _materialPtr->get_emission(), _materialPtr->get_type());
    else det = sqrt(det);
    //distance = (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
    distance = (t = b - det) > eps ? t : 0;
    if (distance) hit = true,
        //norm = ((ray.Origin() + ray.Direction() * distance) - get_pos()).normalize();
        norm = ((ray.Origin() + ray.Direction() * distance) - get_pos()) * get_one_div_radius();

    return jRayObjectItersection(hit, distance, norm, _materialPtr->get_color(), _materialPtr->get_emission(), _materialPtr->get_type());
}

NAME_SPACE_END
NAME_SPACE_END