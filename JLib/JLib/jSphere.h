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
    virtual jRayObjectItersection get_intersection(const jRay& ray) override;
    const jfloat get_radius() const { return _radius; }
    std::shared_ptr<jIRayTracableMaterial> get_material() const { return _materialPtr; }
private:
    jfloat _radius;
    std::shared_ptr<jIRayTracableMaterial> _materialPtr;
};

}}