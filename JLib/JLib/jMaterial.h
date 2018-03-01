#pragma once
#include "jUtility.h"
#include "jVector.h"
#include "jTexture.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

class jRay;
enum class matType {EMIT = 0, DIFF = 1, SPEC = 2, REFR = 3};
extern const jRay reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3], matType type);

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
    jIRayTracableMaterial(jVec3f color, jVec3f emission, matType type) : _color(color), _emission(emission), _type(type) {}
    virtual ~jIRayTracableMaterial() {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const = 0;

    inline const jVec3f& get_emission() const { return _emission; }
    inline const jVec3f& get_color() const { return _color; }
    inline const matType& get_type() const { return _type; }
    /*virtual*/ inline const jVec3f& color_at(jfloat u, jfloat v) const
    {
        return _color;
    };
protected:
    jVec3f _color;
    jVec3f _emission;
    matType _type;
};

class jDiffuseMaterial : public jIRayTracableMaterial
{
public:
    jDiffuseMaterial(jVec3f diffuse_color, jTexture texture = jTexture()) : jIRayTracableMaterial(diffuse_color, jVec3f::zero(), matType::DIFF), _texture(texture) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const override;
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
    jSpecularMaterial(jVec3f specular_color) : jIRayTracableMaterial(specular_color, jVec3f::zero(), matType::SPEC) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const override;
};

class jRefractMaterial : public jIRayTracableMaterial
{
public:
    jRefractMaterial(jVec3f refract_color) : jIRayTracableMaterial(refract_color, jVec3f::zero(), matType::REFR) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const override;
};

class jEmitMaterial : public jIRayTracableMaterial
{
public:
    jEmitMaterial(jVec3f color , jVec3f emission) : jIRayTracableMaterial(color, emission, matType::EMIT) {}
    virtual const jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const override;
};

NAME_SPACE_END
NAME_SPACE_END