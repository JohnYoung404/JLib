#pragma once
#include <boost/assert.hpp>
#include "jVector.h"
#include "jTexture.h"
#include "jRay.h"
#include "jRandom.h"
#include "jMath.h"

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
    virtual jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short(&Xi)[3]) = 0;
    virtual const jVec3f get_emission() = 0;
    virtual const bool is_emit() = 0;
    virtual const jVec3f get_color() = 0;
};

class jDiffuseMaterial : public jIRayTracableMaterial
{
public:
    jDiffuseMaterial(jVec3f diffuse_color, jTexture texture = jTexture()) : _color(diffuse_color), _texture(texture) {}
    virtual jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short(&Xi)[3]) override
    {
        jVec3f nl = dot(norm, input.Direction()) < 0 ? norm : norm * jfloat(-1);
        double r1 = 2 * M_PI * erand48(Xi), r2 = erand48(Xi), r2s = sqrt(r2);
        jVec3f w = nl, u = cross((fabs(w.x()) > jfloat(0.1) ? jVec3f(0, 1) : jVec3f(1)), w).normalize(), v = cross(w, u);
        jVec3f d = (u * jfloat(cos(r1)*r2s) + v * jfloat(sin(r1)*r2s) + w * jfloat(sqrt(1 - r2))).normalize();

        return jRay(hitPos, d);
    }
    virtual const jVec3f get_emission() override { return jVec3f::zero(); };
    virtual const jVec3f get_color() override { return _color; };
    virtual const bool is_emit() override { return false; }
private:
    jVec3f _color;
    jTexture _texture;
};

class jSpecularMaterial : public jIRayTracableMaterial
{
public:
    jSpecularMaterial(jVec3f specular_color) : _color(specular_color) {}
    virtual jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short (&Xi)[3]) override
    {
        double roughness = 0.8;
        jVec3f reflected = input.Direction() - norm * jfloat(2) * dot(norm, input.Direction());
        reflected = jVec3f(
            reflected.x() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
            reflected.y() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
            reflected.z() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness
        ).normalize();

        return jRay(hitPos, reflected);
    }
    virtual const jVec3f get_emission() override { return jVec3f::zero();}
    virtual const jVec3f get_color() override { return _color; }
    virtual const bool is_emit() override { return false; }
private:
    jVec3f _color;
};

class jRefractMaterial : public jIRayTracableMaterial
{
    jRefractMaterial(jVec3f refract_color) : _color(refract_color){}
    virtual jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short(&Xi)[3]) override
    {
        jfloat refractRatio = jfloat(1.8); // refract ratio of glass.
        jfloat roughness = jfloat(0.01);

        if (dot(norm, input.Direction()) < 0)
        {
            jVec3f Axis = input.Direction() - norm * dot(norm, input.Direction());
            Axis.x() = Axis.x() / refractRatio;
            Axis.y() = Axis.y() / refractRatio;
            Axis.z() = Axis.z() / refractRatio;
            jVec3f refractRay = Axis + norm * dot(norm, input.Direction());
            refractRay = jVec3f(
                refractRay.x() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
                refractRay.y() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
                refractRay.z() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness
            ).normalize();
            return jRay(hitPos, refractRay);
        }
        else if (dot(norm, input.Direction()) > 0) {
            jVec3f Axis = input.Direction() - norm * dot(norm, input.Direction());
            Axis.x() = Axis.x() * refractRatio;
            Axis.y() = Axis.y() * refractRatio;
            Axis.z() = Axis.z() * refractRatio;
            jVec3f refractRay = Axis + norm * dot(norm, input.Direction());
            if (dot(refractRay, norm)>= 0)
            {
                refractRay = jVec3f(
                    refractRay.x() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
                    refractRay.y() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
                    refractRay.z() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness
                ).normalize();
                return jRay(hitPos, refractRay);
            }
            else
            {
                jVec3f n2 = jVec3f::zero() - norm;
                jVec3f reflected = input.Direction() - n2 * jfloat(2) * dot(n2, input.Direction());
                reflected = jVec3f(
                    reflected.x() + (erand48(Xi) - 0.5)*roughness,
                    reflected.y() + (erand48(Xi) - 0.5)*roughness,
                    reflected.z() + (erand48(Xi) - 0.5)*roughness
                ).normalize();
                return jRay(hitPos, reflected);
            }
        }
    }
    virtual const jVec3f get_emission() override { return jVec3f::zero(); }
    virtual const jVec3f get_color() override { return _color; }
    virtual const bool is_emit() override { return false; }
private:
    jVec3f _color;
};

class jEmitMaterial : public jIRayTracableMaterial
{
    jEmitMaterial(jVec3f emission) : _emission(emission) {}
    virtual jRay get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f norm, unsigned short(&Xi)[3]) override
    {
#ifdef _Debug
        BOOST_ASSERT_MSG(true, "Control flow shouldn't reach here.");
#endif
        return jRay(jVec3f::zero(), jVec3f::zero());
    }
    virtual const jVec3f get_emission() override { return _emission; }
    virtual const jVec3f get_color() override { return jVec3f::zero(); }
    virtual const bool is_emit() override { return true; }
private:
    jVec3f _emission;
};

}}