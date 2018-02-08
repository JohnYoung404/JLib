#pragma once
#include <memory>
#include <vector>
#include "jSceneObj.h"
#include "jColor.h"

namespace jLib{
namespace jGraphic{

class jScene
{
    jRayObjectItersection intersect(const jRay& ray);
    jVec3f trace_ray(const jRay &ray, int depth, unsigned short(&Xi)[3]);

    inline const jColor get_ambient() const { return _ambient; }
    void add(std::shared_ptr<jSceneObj> object) { _sceneObjs.push_back(object); };
private:
    std::vector< std::shared_ptr<jSceneObj> > _sceneObjs;
    jColor _ambient;
};

}}