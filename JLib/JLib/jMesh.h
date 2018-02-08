#pragma once
#include "jSceneObj.h"
#include "jMaterial.h"
#include "jTriangle.h"
#include "jKDTree.h"
#include "../extern/tiny_obj_loader/tiny_obj_loader.h"

namespace jLib {
namespace jGraphic {

class jMesh : public jSceneObj
{
public:
    jMesh(jVec3f pos, const char* file_path, std::shared_ptr<jIRayTracableMaterial> material);
    virtual jRayObjectItersection get_intersection(const jRay& ray) override;
private:
    std::shared_ptr<jIRayTracableMaterial> _materialPtr;
    std::shared_ptr<jKDNode> _node;

    std::vector<tinyobj::shape_t> _shapes;
    std::vector<tinyobj::material_t> _materials;
    std::vector<std::shared_ptr<jIRayTracableMaterial>> _matPtrs;
    std::vector<std::shared_ptr<jTriangle>> tris;
};

}}