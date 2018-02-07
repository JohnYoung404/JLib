#pragma once
#include <memory>
#include "jSceneObj.h"
#include "jMaterial.h"

namespace jLib {
namespace jGraphic {

class jSphere : public jSceneObj
{
public:
    jSphere(jVec3f pos, jfloat radius, std::shared_ptr<jIRayTracableMaterial> matPtr) : jSceneObj(pos), _radius(radius), _materialPtr(matPtr) {};
private:
    jfloat _radius;
    std::shared_ptr<jIRayTracableMaterial> _materialPtr;
};

}}