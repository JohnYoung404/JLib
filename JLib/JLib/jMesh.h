#pragma once
#include "jSceneObj.h"
#include "jMaterial.h"

namespace jLib {
namespace jGraphic {

class jMesh : public jSceneObj
{
public:
    jMesh(jVec3f pos, jMaterial material) : jSceneObj(pos), _material(material) {};
private:
    jMaterial _material;
};

}}