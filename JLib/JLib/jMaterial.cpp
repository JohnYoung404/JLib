#include <boost/assert.hpp>
#include "jMaterial.h"
#include "jRandom.h"
#include "jMath.h"
#include "jRay.h"


namespace jLib{
namespace jGraphic{

const jRay reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3], matType type)
{
    if (type == matType::REFR)
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
        else {
            jVec3f Axis = input.Direction() - norm * dot(norm, input.Direction());
            Axis.x() = Axis.x() * refractRatio;
            Axis.y() = Axis.y() * refractRatio;
            Axis.z() = Axis.z() * refractRatio;
            jVec3f refractRay = Axis + norm * dot(norm, input.Direction());
            if (dot(refractRay, norm) >= 0)
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
    else if (type == matType::DIFF)
    {
        jVec3f nl = dot(norm, input.Direction()) < 0 ? norm : norm * jfloat(-1);
        double r1 = 2 * M_PI * erand48(Xi), r2 = erand48(Xi), r2s = sqrt(r2);
        jVec3f w = nl, u = cross((fabs(w.x()) > jfloat(0.1) ? jVec3f(0, 1) : jVec3f(1)), w).normalize(), v = cross(w, u);
        jVec3f d = (u * jfloat(cos(r1)*r2s) + v * jfloat(sin(r1)*r2s) + w * jfloat(sqrt(1 - r2))).normalize();
        return jRay(hitPos, d);
    }
    else if (type == matType::EMIT)
    {
        return jRay(jVec3f::zero(), jVec3f::zero());
    }
    else
    {
        return jRay(jVec3f(1, 1, 1), jVec3f::zero());
    }
}

const jRay jDiffuseMaterial::get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const
{
    jVec3f nl = dot(norm, input.Direction()) < 0 ? norm : norm * jfloat(-1);
    double r1 = 2 * M_PI * erand48(Xi), r2 = erand48(Xi), r2s = sqrt(r2);
    jVec3f w = nl, u = cross((fabs(w.x()) > jfloat(0.1) ? jVec3f(0, 1) : jVec3f(1)), w).normalize(), v = cross(w, u);
    jVec3f d = (u * jfloat(cos(r1)*r2s) + v * jfloat(sin(r1)*r2s) + w * jfloat(sqrt(1 - r2))).normalize();
    return jRay(hitPos, d);
}

const jRay jSpecularMaterial::get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const
{
    jfloat roughness = jfloat(0.8);
    jVec3f reflected = input.Direction() - norm * jfloat(2) * dot(norm, input.Direction());
    reflected = jVec3f(
        reflected.x() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
        reflected.y() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
        reflected.z() + (jMath::jRandom::jerand48(Xi) - 0.5)*roughness
    ).normalize();

    return jRay(hitPos, reflected);
}

const jRay jRefractMaterial::get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const
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
    else {
        jVec3f Axis = input.Direction() - norm * dot(norm, input.Direction());
        Axis.x() = Axis.x() * refractRatio;
        Axis.y() = Axis.y() * refractRatio;
        Axis.z() = Axis.z() * refractRatio;
        jVec3f refractRay = Axis + norm * dot(norm, input.Direction());
        if (dot(refractRay, norm) >= 0)
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

const jRay jEmitMaterial::get_reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3]) const
{
#ifdef _Debug
    BOOST_ASSERT_MSG(true, "Control flow shouldn't reach here.");
#endif
    return jRay(jVec3f::zero(), jVec3f::zero());
}

}}