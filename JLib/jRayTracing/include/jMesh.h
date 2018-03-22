#pragma once
#include "jCommon.h"
#include "jSceneObj.h"
#include "jMaterial.h"
#include "jTriangle.h"
#include "jKDTree.h"
#include "../extern/tiny_obj_loader/tiny_obj_loader.h"

namespace jRayTracing{

J_ALIGN(16) class jMesh : public jSceneObj
{
public:
    jMesh(const jVec3f &pos, const char* file_path, jIMaterial* material);
    virtual jRayObjectItersection get_intersection(const jRay& ray) override;
private:
    jIMaterial* _materialPtr;
    jKDNode* _node;
    //jVec3f _color;
    //jVec3f _emission;
    //matType _type;

    std::vector<tinyobj::shape_t> _shapes;
    std::vector<tinyobj::material_t> _materials;
    //std::vector<jIMaterial*> _matPtrs;
    std::vector<jTriangle*> tris;
};

}