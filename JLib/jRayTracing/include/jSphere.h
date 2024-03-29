#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [4/16/2018]
// Description : Inherited from SceneObj, a kind of Renderable Object.

#include <memory>
#include "jSceneObj.h"
#include "jMaterial.h"
#include "jAABBox.h"

namespace jRayTracing{

J_ALIGN(16) class jSphere : public jSceneObj
{
public:
    jSphere(const jVec3f &pos, jReal radius, std::shared_ptr<jIMaterial> matPtr)
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
    J_FORCE_INLINE const jReal& get_radius() const { return _radius; }
    J_FORCE_INLINE const jReal& get_one_div_radius() const { return _one_div_radius; }
    J_FORCE_INLINE const jReal& get_square_radius() const { return _square_radius; }
    J_FORCE_INLINE const std::shared_ptr<jIMaterial>& get_material() const { return _materialPtr; }
    J_FORCE_INLINE const jAABBox & get_aabbox() const { return _aabbox; }
private:
    jReal _radius;
    jReal _one_div_radius;
    jReal _square_radius;
    std::shared_ptr<jIMaterial> _materialPtr;
    jAABBox _aabbox;
};

}