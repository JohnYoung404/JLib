#include "jTexture.h"

namespace jLib {
namespace jGraphic {

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

jColor jTexture::GetPixel(jfloat u, jfloat v) const
{
    if (!_loaded) return jColor::White();
    int x = static_cast<int>((fmod(fabs(u), 1.0)) * (_width - 1));
    int y = static_cast<int>((1. - fmod(fabs(v), 1.0)) * (_height - 1));
    return _img.getPixel(x, y);
}

}}