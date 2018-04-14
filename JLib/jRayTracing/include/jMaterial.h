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

class jIMaterial
{
public:
    jIMaterial(jVec3f color, jVec3f emission, matType type) : _color(color), _emission(emission), _type(type) {}
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

class jDiffuseMaterial : public jIMaterial
{
public:
    jDiffuseMaterial(const jVec3f &diffuse_color) : jIMaterial(diffuse_color, jVec3f(0, 0, 0), matType::DIFF) {}
};

class jSpecularMaterial : public jIMaterial
{
public:
    jSpecularMaterial(const jVec3f &specular_color) : jIMaterial(specular_color, jVec3f(0, 0, 0), matType::SPEC) {}
};

class jRefractMaterial : public jIMaterial
{
public:
    jRefractMaterial(const jVec3f &refract_color) : jIMaterial(refract_color, jVec3f(0, 0, 0), matType::REFR) {}
};

class jEmitMaterial : public jIMaterial
{
public:
    jEmitMaterial(const jVec3f &color, const jVec3f &emission) : jIMaterial(color, emission, matType::EMIT) {}
};

}