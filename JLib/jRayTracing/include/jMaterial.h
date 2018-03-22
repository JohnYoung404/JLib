#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/19/2018]
// Description : Material interface class.

#include "jRay.h"

namespace jRayTracing
{ 

enum class matType 
{
    EMIT, 
    DIFF, 
    SPEC, 
    REFR 
};

extern const jRay reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3], matType type);

J_ALIGN(16) class jIMaterial
{
public:
    jIMaterial(const jVec3f &color, const jVec3f &emission, matType type) : _color(color), _emission(emission), _type(type) {}
    virtual ~jIMaterial() {}

    J_FORCE_INLINE const jVec3f& get_emission() const { return _emission; }
    J_FORCE_INLINE const jVec3f& get_color() const { return _color; }
    J_FORCE_INLINE const matType& get_type() const { return _type; }
    J_FORCE_INLINE const jVec3f& color_at(jReal u, jReal v) const
    {
        return _color;
    };
protected:
    jVec3f _color;
    jVec3f _emission;
    matType _type;
};

J_ALIGN(16) class jDiffuseMaterial : public jIMaterial
{
public:
    jDiffuseMaterial(const jVec3f &diffuse_color) : jIMaterial(diffuse_color, jVec3f::zero(), matType::DIFF) {}
};

J_ALIGN(16) class jSpecularMaterial : public jIMaterial
{
public:
    jSpecularMaterial(const jVec3f &specular_color) : jIMaterial(specular_color, jVec3f::zero(), matType::SPEC) {}
};

J_ALIGN(16) class jRefractMaterial : public jIMaterial
{
public:
    jRefractMaterial(const jVec3f &refract_color) : jIMaterial(refract_color, jVec3f::zero(), matType::REFR) {}
};

J_ALIGN(16) class jEmitMaterial : public jIMaterial
{
public:
    jEmitMaterial(const jVec3f &color, const jVec3f &emission) : jIMaterial(color, emission, matType::EMIT) {}
};

}