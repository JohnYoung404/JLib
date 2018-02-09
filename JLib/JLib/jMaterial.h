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
    virtual ~jIRayTracableMaterial() {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short(&Xi)[3]) const = 0;
    virtual const jVec3f get_emission() const = 0;
    virtual const bool is_emit() const = 0;
    virtual const jVec3f get_color() const = 0;
    virtual const jVec3f color_at(jfloat u, jfloat v) const
    {
        return get_color();
    };
};

class jDiffuseMaterial : public jIRayTracableMaterial
{
public:
    jDiffuseMaterial(jVec3f diffuse_color, jTexture texture = jTexture()) : _color(diffuse_color), _texture(texture) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short(&Xi)[3]) const override;
    virtual const jVec3f get_emission() const override { return jVec3f::zero(); };
    virtual const jVec3f get_color() const override { return _color; };
    virtual const bool is_emit() const override { return false; }
    virtual const jVec3f color_at(jfloat u, jfloat v) const override
    {
        if (_texture.IsLoaded())
        {
            return _texture.GetPixel(u, v);
        }
        return _color;
    }
private:
    jVec3f _color;
    jTexture _texture;
};

class jSpecularMaterial : public jIRayTracableMaterial
{
public:
    jSpecularMaterial(jVec3f specular_color) : _color(specular_color) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short(&Xi)[3]) const override;
    virtual const jVec3f get_emission() const override { return jVec3f::zero();}
    virtual const jVec3f get_color() const override { return _color; }
    virtual const bool is_emit() const override { return false; }
private:
    jVec3f _color;
};

class jRefractMaterial : public jIRayTracableMaterial
{
public:
    jRefractMaterial(jVec3f refract_color) : _color(refract_color){}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short(&Xi)[3]) const override;
    virtual const jVec3f get_emission() const override { return jVec3f::zero(); }
    virtual const jVec3f get_color() const override { return _color; }
    virtual const bool is_emit() const override { return false; }
private:
    jVec3f _color;
};

class jEmitMaterial : public jIRayTracableMaterial
{
public:
    jEmitMaterial(jVec3f color , jVec3f emission) : _color(color), _emission(emission) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short(&Xi)[3]) const override;
    virtual const jVec3f get_emission() const override { return _emission; }
    virtual const jVec3f get_color() const override { return _color; }
    virtual const bool is_emit() const override { return true; }
private:
    jVec3f _emission;
    jVec3f _color;
};

}}