#pragma once
#include <memory>
#include "jSceneObj.h"
#include "jMaterial.h"

namespace jLib {
namespace jGraphic {

class jSphere : public jSceneObj
{
public:
    jSphere(jVec3f pos, jfloat radius, const std::shared_ptr<jIRayTracableMaterial> &matPtr) : jSceneObj(pos), _radius(radius), _square_radius(radius * radius), _materialPtr(matPtr) {};
    virtual jRayObjectItersection get_intersection(const jRay& ray) override;
    inline const jfloat& get_radius() const { return _radius; }
    inline const jfloat& get_square_radius() const { return _square_radius; }
    inline const std::shared_ptr<jIRayTracableMaterial>& get_material() const { return _materialPtr; }
private:
    jfloat _radius;
    jfloat _square_radius;
    std::shared_ptr<jIRayTracableMaterial> _materialPtr;
};

}}