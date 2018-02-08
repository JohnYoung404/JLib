#include "jScene.h"
#include "jMaterial.h"
#include "jRandom.h"

namespace jLib {
namespace jGraphic {

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

    // If no hit, return world colour
    if (!isct.hit()) return jVec3f::zero();
    /*if (!isct.hit){
    double u, v;
    v = (acos(Vec(0,0,1).dot(ray.direction))/M_PI);
    u = (acos(ray.direction.y)/ M_PI);
    return bg.get_pixel(fabs(u), fabs(v))*1.2;
    }*/
    if (isct.materialPtr()->is_emit() == true) return isct.materialPtr()->get_emission();
    //Vec x = ray.origin + ray.direction * isct.u;

    jVec3f colour = isct.materialPtr()->get_color();
    //return colour * isct.n.dot((Vec(1,-3,8)-x).norm());

    // Calculate max reflection
    jfloat p = colour.x() > colour.y() && colour.x() > colour.z() ? colour.x() : colour.y() > colour.z() ? colour.y() : colour.z();

    // Russian roulette termination.
    // If random number between 0 and 1 is > p, terminate and return hit object's emmission
    double rnd = jMath::jRandom::jerand48(Xi);
    if (++depth > 30) {
        if (rnd < p*0.9) { // Multiply by 0.9 to avoid infinite loop with colours of 1.0
            colour = colour * (jfloat(0.9) / p);
        }
        else {
            return isct.materialPtr()->get_emission();
        }
    }

    jVec3f x = ray.Origin() + ray.Direction() * isct.dist();
    jRay reflected = isct.materialPtr()->get_reflected_ray(ray, x, isct.norm(), Xi);

    return colour * (trace_ray(reflected, depth, Xi));
}

}}