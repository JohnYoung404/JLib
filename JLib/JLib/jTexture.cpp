#include "jTexture.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

jTexture::jTexture(const char* filename)
{
    _loaded = _img.LoadImage(filename);
    _width = _img.horiBound();
    _height = _img.vertBound();
}

jColor jTexture::GetPixel(int coor_x, int coor_y) const
{
    if (!_loaded) return jColor::White();
    return _img.getPixel(coor_x, coor_y);
}

jVec3f jTexture::GetPixel(jfloat u, jfloat v) const
{
    if (!_loaded) return jVec3f::zero();
    int x = static_cast<int>((fmod(fabs(u), 1.0)) * (_width - 1));
    int y = static_cast<int>((1. - fmod(fabs(v), 1.0)) * (_height - 1));
    return jVec3f((jfloat)_img.getPixel(x, y).R() / jfloat(255), (jfloat)_img.getPixel(x, y).G() / jfloat(255), (jfloat)_img.getPixel(x, y).B() / jfloat(255) );
}

NAME_SPACE_END
NAME_SPACE_END