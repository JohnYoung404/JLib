#pragma once
#include <memory>
#include <vector>
#include "jSceneObj.h"

namespace jRayTracing {

class jScene
{
public:
    jRayObjectItersection intersect(const jRay& ray);
    jVec3f trace_ray(const jRay &ray, int depth, unsigned short(&Xi)[3]);

    void add(std::shared_ptr<jSceneObj> object) { _sceneObjs.push_back(object); };
private:
    std::vector< std::shared_ptr<jSceneObj> > _sceneObjs;
};

}