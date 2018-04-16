#include "jMaterial.h"
#include "jRandom.h"
#include "jMath.h"
#include "jRay.h"


namespace jRayTracing{

const jRay reflected_ray(const jRay &input, const jVec3f &hitPos, const jVec3f &norm, unsigned short(&Xi)[3], matType type)
{
    if (type == matType::REFR)
    {
        jReal refractRatio = jReal(1.5); // refract ratio of glass.
        jReal roughness = jReal(0.01);
        jReal cos_theta = norm.dot(input.Direction());
        if (cos_theta < 0)
        {
            jReal sin_theta = std::sqrt(1 - cos_theta * cos_theta);    //sin_theta可用叉积求出...
            jReal sin_theta_refr = sin_theta / refractRatio;
            jReal cos_theta_refr = std::sqrt(1 - sin_theta_refr * sin_theta_refr);
            jReal extent_ratio = cos_theta / (cos_theta_refr * refractRatio);
            J_ALIGN(16) jVec3f Axis = input.Direction() - norm * cos_theta;
            Axis.x() = Axis.x() * extent_ratio;
            Axis.y() = Axis.y() * extent_ratio;
            Axis.z() = Axis.z() * extent_ratio;
            J_ALIGN(16) jVec3f refractRay = Axis + norm * cos_theta;
            refractRay = jVec3f(
                refractRay.x(), //+ (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
                refractRay.y(), //+ (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
                refractRay.z()  //+ (jMath::jRandom::jerand48(Xi) - 0.5)*roughness
            ).normalize_org();
            return jRay(hitPos, refractRay);
        }
        else
        {
            jReal sin_theta = std::sqrt(1 - cos_theta * cos_theta);
            jReal sin_theta_refr = sin_theta * refractRatio;
            if (sin_theta_refr >= 1)
            {
                return jRay(hitPos, (input.Direction() - norm * 2 * norm.dot(input.Direction())).normalize_org());
            }
            else
            {
                jReal cos_theta_refr = std::sqrt(1 - sin_theta_refr * sin_theta_refr);
                jReal extent_ratio = refractRatio * cos_theta / cos_theta_refr;
                J_ALIGN(16) jVec3f Axis = input.Direction() - norm * cos_theta;
                Axis.x() = Axis.x() * extent_ratio;
                Axis.y() = Axis.y() * extent_ratio;
                Axis.z() = Axis.z() * extent_ratio;
                jVec3f refractRay = Axis + norm * cos_theta;
                refractRay = jVec3f(
                    refractRay.x(), //+ (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
                    refractRay.y(), //+ (jMath::jRandom::jerand48(Xi) - 0.5)*roughness,
                    refractRay.z() //+ (jMath::jRandom::jerand48(Xi) - 0.5)*roughness
                ).normalize_org();
                return jRay(hitPos, refractRay);
            }
        }
    }
    if (type == matType::DIFF)
    {
        jVec3f nl = norm.dot(input.Direction()) < 0 ? norm : norm * jReal(-1);
        jReal r1 = jReal(2 * M_PI * jerand48(Xi)), r2 = jerand48(Xi), r2s = std::sqrt(r2);
        jVec3f w = nl, u = (fabs(w.x()) > jReal(0.1) ? jVec3f(0, 1) : jVec3f(1)).cross_org(w).normalize_org(), v = w.cross_cpy(u);
        jVec3f d = ((u.scalar_mul_org(jReal(cos(r1)*r2s))).add_org(v .scalar_mul_org(jReal(sin(r1)*r2s))).add_org(w.scalar_mul_org((std::sqrt(1 - r2))))).normalize_org();
        return jRay(hitPos, d);
    }
    if (type == matType::SPEC)
    {
        jReal roughness = 0;//jReal(0.8);
        jVec3f reflected = input.Direction() - norm * jReal(2) * norm.dot(input.Direction());
        reflected = jVec3f(
            reflected.x() + (jerand48(Xi) - 0.5f)*roughness,
            reflected.y() + (jerand48(Xi) - 0.5f)*roughness,
            reflected.z() + (jerand48(Xi) - 0.5f)*roughness
        ).normalize_org();

        return jRay(hitPos, reflected);
    }
    if (type == matType::EMIT)
    {
        return jRay(jVec3f(0, 0, 0), jVec3f(0, 0, 0));
    }
    return jRay(jVec3f(1, 1, 1), jVec3f(0, 0, 0));
}

}