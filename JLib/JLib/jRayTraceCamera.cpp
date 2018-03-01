#include "jRayTraceCamera.h"
#include "jRandom.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

jRayTraceCamera::jRayTraceCamera(jVec3f eye_pos, jVec3f look_at, int width, int height)
{
    _width = width;
    _width_recp = jfloat(1) / _width;
    _height = height;
    _height_recp = jfloat(1) / _height;
    _ratio = (jfloat)_width / _height;

    _position = eye_pos;
    _direction = (look_at - _position).normalize();
    _x_direction = jVec3f(0, 0, 1).cross(_direction * jfloat(-1)).normalize();
    _y_direction = _x_direction.cross(_direction).normalize();

    _x_spacing = (jfloat(2) * _ratio) / (jfloat)_width;
    _y_spacing = jfloat(2) / (jfloat)_height;
    _x_spacing_half = _x_spacing * jfloat(0.5);
    _y_spacing_half = _y_spacing * jfloat(0.5);
}

jRay jRayTraceCamera::get_ray(int x, int y, bool jitter, unsigned short (&Xi)[3])
{
    jfloat x_jitter;
    jfloat y_jitter;

    // If jitter == true, jitter point for anti-aliasing
    if (jitter) {
        x_jitter = (jMath::jRandom::jerand48(Xi) * _x_spacing) - _x_spacing_half;
        y_jitter = (jMath::jRandom::jerand48(Xi) * _y_spacing) - _y_spacing_half;

    }
    else {
        x_jitter = 0;
        y_jitter = 0;
    }

    jVec3f pixel = _position + _direction * jfloat(2);
    pixel = pixel - _x_direction*_ratio + _x_direction*(x * 2 * _ratio)*_width_recp + jVec3f(x_jitter, 0, 0);
    pixel = pixel + _y_direction - _y_direction * jfloat((y * 2.0)*_height_recp + y_jitter);

    return jRay(_position, (pixel - _position).normalize());
}

NAME_SPACE_END
NAME_SPACE_END