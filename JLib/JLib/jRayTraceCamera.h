#pragma once
#include <vector>
#include "jUtility.h"
#include "jRay.h"
#include "jVector.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

J_ALIGN(16) struct jRayTraceCamera
{
public:
    jRayTraceCamera(jVec3f eye_pos, jVec3f look_at, int width, int height);
    jRay get_ray(int x, int y, bool jitter, unsigned short(&Xi)[3]);

    const int& get_width() const { return _width; }
    const int& get_height() const { return _height; }
private:
    int _width;
    jfloat _width_recp;
    int _height;
    jfloat _height_recp;
    jfloat _ratio;
    jfloat _x_spacing;
    jfloat _x_spacing_half;
    jfloat _y_spacing;
    jfloat _y_spacing_half;
    jVec3f _position;
    jVec3f _direction;
    jVec3f _x_direction;
    jVec3f _y_direction;
};

NAME_SPACE_END
NAME_SPACE_END