#pragma once
#include <vector>
#include "jCommon.h"
#include "jRay.h"
#include "jVec3f_SIMD.h"

namespace jRayTracing{

J_ALIGN(16) class jCamera
{
public:
    jCamera(const jVec3f &eye_pos, const jVec3f &look_at, int width, int height);
    jRay get_ray(int x, int y, bool jitter, unsigned short(&Xi)[3]);

    const int& get_width() const { return _width; }
    const int& get_height() const { return _height; }
private:
    int _width;
    jReal _width_recp;
    int _height;
    jReal _height_recp;
    jReal _ratio;
    jReal _x_spacing;
    jReal _x_spacing_half;
    jReal _y_spacing;
    jReal _y_spacing_half;
    jVec3f _position;
    jVec3f _direction;
    jVec3f _x_direction;
    jVec3f _y_direction;
};

}