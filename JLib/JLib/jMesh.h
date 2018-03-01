#pragma once
#include "jUtility.h"
#include "jSceneObj.h"
#include "jMaterial.h"
#include "jTriangle.h"
#include "jKDTree.h"
#include "../extern/tiny_obj_loader/tiny_obj_loader.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

class jMesh : public jSceneObj
{
public:
    jMesh(jVec3f pos, const char* file_path, std::shared_ptr<jIRayTracableMaterial> material);
    virtual jRayObjectItersection get_intersection(const jRay& ray) override;
private:
    std::shared_ptr<jIRayTracableMaterial> _materialPtr;
    std::shared_ptr<jKDNode> _node;
    //jVec3f _color;
    //jVec3f _emission;
    //matType _type;

    std::vector<tinyobj::shape_t> _shapes;
    std::vector<tinyobj::material_t> _materials;
    std::vector<std::shared_ptr<jIRayTracableMaterial>> _matPtrs;
    std::vector<std::shared_ptr<jTriangle>> tris;
};

NAME_SPACE_END
NAME_SPACE_END