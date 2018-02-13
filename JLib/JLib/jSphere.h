#pragma once
#include <memory>
#include "jSceneObj.h"
#include "jMaterial.h"
#include "jAABBox.h"

namespace jLib {
namespace jGraphic {

class jSphere : public jSceneObj
{
public:
    jSphere(jVec3f pos, jfloat radius, const std::shared_ptr<jIRayTracableMaterial> &matPtr) 
        : jSceneObj(pos)
        , _radius(radius)
        , _square_radius(radius * radius)
        , _materialPtr(matPtr) 
        , _one_div_radius(1 / radius)
        , _aabbox(
            jVec3f(pos.x() - radius, pos.y() - radius, pos.z() - radius)
            , jVec3f(pos.x() + radius, pos.y() + radius, pos.z() + radius)
        )
    {};
    virtual jRayObjectItersection get_intersection(const jRay& ray) override;
    inline const jfloat& get_radius() const { return _radius; }
    inline const jfloat& get_one_div_radius() const { return _one_div_radius; }
    inline const jfloat& get_square_radius() const { return _square_radius; }
    inline const std::shared_ptr<jIRayTracableMaterial>& get_material() const { return _materialPtr; }
    inline const jAABBox & get_aabbox() const { return _aabbox; }
private:
    jfloat _radius;
    jfloat _one_div_radius;
    jfloat _square_radius;
    std::shared_ptr<jIRayTracableMaterial> _materialPtr;
    jAABBox _aabbox;
};

}}