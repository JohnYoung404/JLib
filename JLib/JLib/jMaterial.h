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
    jfloat transmittance[3];    //͸����
    jfloat emission[3];
    jfloat shininess;
    jfloat ior;                 //index of refraction ������
    jfloat dissolve;            //1 == opaque; 0 == fully transparent
    jTexture texture;
};

}}