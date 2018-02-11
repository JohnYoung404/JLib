#include "jScene.h"
#include "jMaterial.h"
#include "jRandom.h"

namespace jLib {
namespace jGraphic {

    class jSphere;

jRayObjectItersection jScene::intersect(const jRay& ray)
{
    jRayObjectItersection isct = jRayObjectItersection();
    jRayObjectItersection temp;
    size_t size = _sceneObjs.size();

    for (size_t i = 0; i < size; i++) {
        temp = _sceneObjs.at(i)->get_intersection(ray);
        
        if (temp.hit()) {
            if (isct.dist() == 0 || temp.dist() < isct.dist()) isct = temp;
        }
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
    jfloat p = colour.x() > colour.y() && colour.x() > colour.z() ? colour.x() : colour.y() > colour.z() ? colour.y() : colour.z();
    
    // Russian roulette termination.
    // If random number between 0 and 1 is > p, terminate and return hit object's emmission
    double rnd = jMath::jRandom::jerand48(Xi);
    if (++depth > 10) {
        if (rnd < p*0.9) { // Multiply by 0.9 to avoid infinite loop with colours of 1.0
            colour = colour * (jfloat(0.9) / p);
        }
        else {
            return isct.emission();
        }
    }
    
    jVec3f x = ray.Origin() + ray.Direction() * isct.dist();
    jRay reflected = reflected_ray(ray, x, isct.norm(), Xi, isct.get_type());
    //jRay reflected = isct.materialPtr()->get_reflected_ray(ray, x, isct.norm(), Xi);
    
    return colour.mult(trace_ray(reflected, depth, Xi));
}

}}