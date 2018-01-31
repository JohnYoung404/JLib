#pragma once
#include "jSceneObj.h"
#include "jMaterial.h"

namespace jLib {
namespace jGraphic {

class jSphere : public jSceneObj
{
public:
    jSphere(jVec3f pos, jfloat radius, jMaterial material) : jSceneObj(pos), _radius(radius), _material(material) {};
private:
    jfloat _radius;
    jMaterial _material;
};

}}