#pragma once

#include "jVector.h"
#include "jTexture.h"
#include "jRay.h"

namespace jLib {
namespace jGraphic {

class jMaterial
{
public:
    //jMaterial(jVec3f ambient, jVec3f diffuse, jVec3f specular, jVec3f transmittance, ...)
private:
    jVec3f _ambient;
    jVec3f _diffuse;
    jVec3f _specular;
    jVec3f _transmittance;    //Õ∏…‰¬ 
    jVec3f _emission;

    jfloat _shininess;
    jfloat _ior;                 //index of refraction ’€…‰¬ 
    jfloat _dissolve;            //1 == opaque; 0 == fully transparent
    jTexture _texture;
};

class jIRayTracableMaterial
{
public:
    jIRayTracableMaterial(jVec3f color, jVec3f emission) : _color(color), _emission(emission) {}
    virtual ~jIRayTracableMaterial() {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const = 0;

    inline const jVec3f get_emission() const { return jVec3f::zero(); }
    inline const jVec3f get_color() const { return _color; }

    virtual inline const bool is_emit() const = 0;
    /*virtual*/ inline const jVec3f color_at(jfloat u, jfloat v) const
    {
        return _color;
    };
protected:
    jVec3f _color;
    jVec3f _emission;
};

class jDiffuseMaterial : public jIRayTracableMaterial
{
public:
    jDiffuseMaterial(jVec3f diffuse_color, jTexture texture = jTexture()) : jIRayTracableMaterial(diffuse_color, jVec3f::zero()), _texture(texture) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const override;
    virtual inline const bool is_emit() const override { return false; }
    //virtual inline const jVec3f color_at(jfloat u, jfloat v) const override
    //{
    //    if (_texture.IsLoaded())
    //    {
    //        return _texture.GetPixel(u, v);
    //    }
    //    return _color;
    //}
private:
    jTexture _texture;
};

class jSpecularMaterial : public jIRayTracableMaterial
{
public:
    jSpecularMaterial(jVec3f specular_color) : jIRayTracableMaterial(specular_color, jVec3f::zero()) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const override;
    virtual inline const bool is_emit() const override { return false; }
};

class jRefractMaterial : public jIRayTracableMaterial
{
public:
    jRefractMaterial(jVec3f refract_color) : jIRayTracableMaterial(refract_color, jVec3f::zero()) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const override;
    virtual inline const bool is_emit() const override { return false; }
};

class jEmitMaterial : public jIRayTracableMaterial
{
public:
    jEmitMaterial(jVec3f color , jVec3f emission) : jIRayTracableMaterial(color, emission) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const override;
    virtual inline const bool is_emit() const override { return true; }
};

}}