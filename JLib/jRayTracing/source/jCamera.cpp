#include "jCamera.h"
#include "jRandom.h"

namespace jRayTracing{

jCamera::jCamera(const jVec3f &eye_pos, const jVec3f &look_at, int width, int height)
	: _width(width)
	, _width_recp(jReal(1) / _width)
	, _height(height)
	, _height_recp(jReal(1) / _height)
	, _ratio((jReal)_width / _height)
	, _position(eye_pos)
	, _direction((look_at - eye_pos).normalize_org())
	, _x_direction(jVec3f(0, 0, 1).cross_org(_direction * jReal(-1)).normalize_org())
	, _y_direction(_x_direction.cross_cpy(_direction).normalize_org())
	, _x_spacing((jReal(2) * _ratio) / (jReal)_width)
	, _y_spacing(jReal(2) / (jReal)_height)
	, _x_spacing_half(_x_spacing / jReal(2))
	, _y_spacing_half(_y_spacing / jReal(2))
{
}

jRay jCamera::get_ray(int x, int y, bool jitter, unsigned short(&Xi)[3])
{
    jReal x_jitter;
    jReal y_jitter;

    // If jitter == true, jitter point for anti-aliasing
    if (jitter) {
        x_jitter = (jerand48(Xi) * _x_spacing) - _x_spacing_half;
        y_jitter = (jerand48(Xi) * _y_spacing) - _y_spacing_half;

    }
    else {
        x_jitter = 0;
        y_jitter = 0;
    }

    jVec3f pixel = _position + _direction * jReal(2);
    pixel = pixel.sub_org(_x_direction*_ratio).add_org(_x_direction*(x * 2 * _ratio)*_width_recp).add_org(jVec3f(x_jitter, 0, 0));
    pixel = pixel.add_org(_y_direction) .sub_org( _y_direction * jReal((y * 2.0)*_height_recp + y_jitter) );

    return jRay(_position, (pixel - _position).normalize_org());
}

}