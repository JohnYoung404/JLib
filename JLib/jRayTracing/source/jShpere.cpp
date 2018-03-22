#include "jSphere.h"

namespace jRayTracing{

jRayObjectItersection jSphere::get_intersection(const jRay& ray)
{
    bool hit = false;
    jReal distance = 0;
    jVec3f norm = jVec3f::zero();

    VectorRegister pos = VectorLoadAligned(get_pos()._VEC);
    VectorRegister org = VectorLoadAligned(ray.Origin()._VEC);
    VectorRegister dir = VectorLoadAligned(ray.Direction()._VEC);
    VectorRegister op = VectorSubtract(pos, org);
    jReal b = VectorDot3(op, dir).m128_f32[0], t, eps = jReal(1e-3);
    jReal det = b * b - VectorDot3(op, op).m128_f32[0] + get_square_radius();
    if (det < 0) return jRayObjectItersection(hit, distance, norm, _materialPtr->get_color(), _materialPtr->get_emission(), _materialPtr->get_type());
    else det = sqrt(det);
    distance = (t = b - det) > eps ? t : 0;
    if (distance)
    {
        hit = true;
        J_ALIGN(16) jReal dis[4] = { distance, distance, distance, 0 };
        VectorRegister distance = VectorLoadAligned(dis);
        VectorRegister dir_dot_dis = VectorDot3(dir, distance);
        VectorRegister org_add_that = VectorAdd(org, dir_dot_dis);
        VectorRegister that_minus_pos = VectorSubtract(org_add_that, pos);
        VectorStoreAligned(that_minus_pos, norm._VEC);
        norm.scalar_mul_org(get_one_div_radius());
    }
    return jRayObjectItersection(hit, distance, norm, _materialPtr->get_color(), _materialPtr->get_emission(), _materialPtr->get_type());

    //jVec3f op = get_pos() - ray.Origin();
    //jReal t, eps = jReal(1e-4), b = op.dot(ray.Direction()), det = b*b - op.dot(op) + get_square_radius();
    //if (det < 0) return jRayObjectItersection(hit, distance, norm, _materialPtr->get_color(), _materialPtr->get_emission(), _materialPtr->get_type());
    //else det = sqrt(det);
    ////distance = (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
    //distance = (t = b - det) > eps ? t : 0;
    //if (distance) hit = true,
    //    //norm = ((ray.Origin() + ray.Direction() * distance) - get_pos()).normalize();
    //    norm = ((ray.Origin() + ray.Direction() * distance) - get_pos()) * get_one_div_radius();
    //
    //return jRayObjectItersection(hit, distance, norm, _materialPtr->get_color(), _materialPtr->get_emission(), _materialPtr->get_type());
}
}