#include "jSphere.h"

namespace jRayTracing{

jRayObjectItersection jSphere::get_intersection(const jRay& ray)
{
    bool hit = false;
    jReal distance = 0;
    
    jVec3f op = get_pos() - ray.Origin();
    jReal t, eps = jReal(1e-4), b = op.dot(ray.Direction()), det = b*b - op.dot(op) + get_square_radius();
    if (det < 0) return jRayObjectItersection(hit, distance, jVec3f::zero(), _materialPtr->get_color(), _materialPtr->get_emission(), _materialPtr->get_type());
    else det = sqrt(det);
    distance = (t = b - det) > eps ? t : 0;
	jVec3f norm;
	if (distance)
	{
		hit = true;
		norm = ((ray.Direction() * distance).add_org(ray.Origin()).sub_org(get_pos())).scalar_mul_org(get_one_div_radius());
	}
    return jRayObjectItersection(hit, distance, norm, _materialPtr->get_color(), _materialPtr->get_emission(), _materialPtr->get_type());
}
}