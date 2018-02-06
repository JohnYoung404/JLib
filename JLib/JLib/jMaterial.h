#pragma once
#include "jVector.h"
#include "jTexture.h"

namespace jLib {
namespace jGraphic {

class jMaterial
{
public:
    jMaterial() : texture() {};
    jfloat ambient[3];
    jfloat diffuse[3];
    jfloat specular[3];
    jfloat transmittance[3];    //Í¸ÉäÂÊ
    jfloat emission[3];
    jfloat shininess;
    jfloat ior;                 //index of refraction ÕÛÉäÂÊ
    jfloat dissolve;            //1 == opaque; 0 == fully transparent
    jTexture texture;
};

}}