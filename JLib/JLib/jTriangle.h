#pragma once
#include <memory>
#include "jAABBox.h"
#include "jMaterial.h"
#include "jVector.h"

namespace jLib{
namespace jGraphic{

struct jTriangle {
    jVec3f v0, v1, v2;     // Vertex world space coordinates
    jVec3f e1, e2;         // Edge 1 and edge 2 of triangle
    jVec3f n, t0, t1, t2;  // Triangle normal and texture coordinates
    std::shared_ptr<jIRayTracableMaterial> materialPtr;       // Pointer to material

    
    jTriangle(jVec3f v0_, jVec3f v1_, jVec3f v2_, jVec3f t0_ = jVec3f(), jVec3f t1_ = jVec3f(), jVec3f t2_ = jVec3f(), std::shared_ptr<jIRayTracableMaterial> m_ = nullptr) {
        v0 = v0_, v1 = v1_, v2 = v2_, e1 = v1 - v0, e2 = v2 - v0, n = e1.cross(e2).normalize();
        t0 = t0_, t1 = t1_, t2 = t2_;
        materialPtr = m_;
    }

    // Returns axis aligned bounding box that contains the triangle
    jAABBox get_bounding_box() {
        jVec3f bl = jVec3f(
            v0.x() < v1.x() && v0.x() < v2.x() ? v0.x() : v1.x() < v2.x() ? v1.x() : v2.x(),
            v0.y() < v1.y() && v0.y() < v2.y() ? v0.y() : v1.y() < v2.y() ? v1.y() : v2.y(),
            v0.z() < v1.z() && v0.z() < v2.z() ? v0.z() : v1.z() < v2.z() ? v1.z() : v2.z()
        );
        jVec3f tr = jVec3f(
            v0.x() > v1.x() && v0.x() > v2.x() ? v0.x() : v1.x() > v2.x() ? v1.x() : v2.x(),
            v0.y() > v1.y() && v0.y() > v2.y() ? v0.y() : v1.y() > v2.y() ? v1.y() : v2.y(),
            v0.z() > v1.z() && v0.z() > v2.z() ? v0.z() : v1.z() > v2.z() ? v1.z() : v2.z()
        );

        return jAABBox(bl, tr);
    }

    // Returns the midpoint of the triangle
    jVec3f get_midpoint() {
        return (v0 + v1 + v2) / jfloat(3);
    }

    // Checks if ray intersects with triangle. Returns true/false.
    bool intersect(const jRay &ray, jfloat &t, jfloat tmin, jVec3f &norm) const {

        jfloat u, v, t_temp = 0;

        jVec3f pvec = ray.Direction().cross(e2);
        jfloat det = e1.dot(pvec);
        if (det == 0) return false;
        jfloat invDet = jfloat(1) / det;
        jVec3f tvec = ray.Origin() - v0;
        u = tvec.dot(pvec) * invDet;
        if (u < 0 || u > 1) return false;
        jVec3f qvec = tvec.cross(e1);
        v = ray.Direction().dot(qvec) * invDet;
        if (v < 0 || u + v > 1) return false;
        t_temp = e2.dot(qvec) * invDet; // Set distance along ray to intersection
        if (t_temp < tmin) {
            if (t_temp > jfloat(1e-9)) {    // Fairly arbritarily small value, scared to change
                t = t_temp;         // it as it works.
                norm = n;
                return true;
            }
        }
        return false;
    }

    // Returns barycentric coordinates of point p on the triangle
    jVec3f barycentric(jVec3f p) {
        jVec3f v2_ = p - v0;
        jfloat d00 = e1.dot(e1);
        jfloat d01 = e1.dot(e2);
        jfloat d11 = e2.dot(e2);
        jfloat d20 = v2_.dot(e1);
        jfloat d21 = v2_.dot(e2);
        jfloat d = d00*d11 - d01*d01;
        jfloat v = (d11*d20 - d01*d21) / d;
        jfloat w = (d00*d21 - d01*d20) / d;
        jfloat u = 1 - v - w;
        return jVec3f(u, v, w);
    }

    // Returns the colour at point p on the triangle
    jVec3f get_colour_at(jVec3f p) {
        if (materialPtr == nullptr) return jVec3f(1, 0, 1);

        jVec3f b = barycentric(p);
        jVec3f c = jVec3f::zero();
        c = c + (t0 * b.x());
        c = c + (t1 * b.y());
        c = c + (t2 * b.z());

        return materialPtr->color_at(c.x(), c.y());
    }

    jVec3f get_color ()
    {
        return materialPtr->get_color();
    }

};

}}