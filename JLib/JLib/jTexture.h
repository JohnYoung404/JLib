#pragma once
#include "jColor.h"
#include "jCanvas.h"
#include "jVector.h"
#include "jUtility.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

class jTexture
{
public:
    jTexture() : _loaded(false) {};
    jTexture(const char* filename);

    jColor GetPixel(int coor_x, int coor_y) const;
    jVec3f GetPixel(jfloat u, jfloat v) const;

    inline bool IsLoaded() const { return _loaded; }
private:
    unsigned _width;
    unsigned _height;
    jCanvas _img;
    bool _loaded;
};

NAME_SPACE_END
NAME_SPACE_END