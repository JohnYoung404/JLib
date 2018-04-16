#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [4/16/2018]
// Description : A scene contains all sceneObjs that need to be rendered.

#include <memory>
#include <vector>
#include "jSceneObj.h"

namespace jRayTracing {

class jScene
{
public:
    jRayObjectItersection intersect(const jRay& ray);
    jVec3f trace_ray(const jRay &ray, int depth, unsigned short(&Xi)[3]);

    void add(jSceneObj* object) { _sceneObjs.push_back(object); };
private:
    std::vector<jSceneObj*> _sceneObjs;
};

}