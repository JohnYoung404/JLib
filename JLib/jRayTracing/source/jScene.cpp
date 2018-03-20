#include "jScene.h"
#include "jMaterial.h"
#include "jRandom.h"

namespace jRayTracing
{

class jSphere;

jRayObjectItersection jScene::intersect(const jRay& ray)
{
    jRayObjectItersection isct = jRayObjectItersection();

    for (size_t i = 0; i < _sceneObjs.size(); i++) {
        const jRayObjectItersection &temp = _sceneObjs.at(i)->get_intersection(ray);
        if (temp.hit() && temp.dist() < isct.dist())  isct = temp;
    }
    return isct;
}

jVec3f jScene::trace_ray(const jRay &ray, int depth, unsigned short(&Xi)[3])
{
    jRayObjectItersection isct = intersect(ray);

    //return jVec3f::zero();

    // If no hit, return world colour
    if (!isct.hit()) return jVec3f::zero();

    if (isct.get_type() == matType::EMIT) return isct.emission();

    jVec3f colour = isct.color();

    // Calculate max reflection
    jReal p = colour.x() > colour.y() && colour.x() > colour.z() ? colour.x() : colour.y() > colour.z() ? colour.y() : colour.z();

    // Russian roulette termination.
    // If random number between 0 and 1 is > p, terminate and return hit object's emmission
    double rnd = jerand48(Xi);
    if (++depth > 10) {
        if (rnd < p*0.9) { // Multiply by 0.9 to avoid infinite loop with colours of 1.0
            colour = colour * (jReal(0.9) / p);
        }
        else {
            return isct.emission();
        }
    }

    jVec3f x = ray.Origin() + ray.Direction() * isct.dist();
    if (isct.get_type() == matType::REFR && depth < 3)
    {
        jRay reflected = reflected_ray(ray, x, isct.norm(), Xi, matType::SPEC);
        jRay refrected = reflected_ray(ray, x, isct.norm(), Xi, matType::REFR);
        return colour.cwise_mult_cpy(trace_ray(reflected, depth, Xi)*0.1) + colour.cwise_mult_cpy(trace_ray(refrected, depth, Xi)*0.9);
    }
    jRay reflected = reflected_ray(ray, x, isct.norm(), Xi, isct.get_type());
    //jRay reflected = isct.materialPtr()->get_reflected_ray(ray, x, isct.norm(), Xi);

    return colour.cwise_mult_org(trace_ray(reflected, depth, Xi));
}

}