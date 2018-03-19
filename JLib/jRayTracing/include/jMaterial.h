#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/19/2018]
// Description : Material interface class.

#include "jRay.h"

namespace jRayTracing
{ 

template<typename MatType>
class jIMaterial
{
public:
    J_FORCE_INLINE const MatType& Cast() { return static_cast<const MatType&>(*this); }
    J_FORCE_INLINE MatType& Cast() { return static_cast<MatType&>(*this); }

public:
    J_FORCE_INLINE const jVec3f& get_emission() const { return Cast().get_emission(); }
    J_FORCE_INLINE const jVec3f& get_color() const { return Cast().get_color(); }
    J_FORCE_INLINE const jVec3f& color_at() const { return Cast().color_at(); }
    J_FORCE_INLINE const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const 
    { 
        return Cast().get_reflected_ray(input, hitPos, norm, Xi);
    }
private:
    jIMaterial() {};
    friend MatType;
};

}