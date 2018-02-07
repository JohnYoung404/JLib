#pragma once
#include "jSceneObj.h"
#include "jMaterial.h"

namespace jLib {
namespace jGraphic {

class jMesh : public jSceneObj
{
public:
    jMesh(jVec3f pos, std::shared_ptr<jIRayTracableMaterial> matPtr) : jSceneObj(pos), _materialPtr(matPtr) {};
private:
    std::shared_ptr<jIRayTracableMaterial> _materialPtr;
};

}}