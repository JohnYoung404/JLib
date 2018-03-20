#pragma once

#include "jCommon.h"
#include <vector>
#include "jRay.h"
#include "jVec3f_SIMD.h"
#include "jAABBox.h"
#include "jTriangle.h"

namespace jRayTracing{

class jKDNode
{
public:
    std::shared_ptr<jKDNode> build(std::vector<std::shared_ptr<jTriangle>> &tris, int depth);
    bool hit(const std::shared_ptr<jKDNode> &node, const jRay &ray, jReal &t, jReal &tmin, jVec3f &norm/*, jVec3f &color*/) const;

    jAABBox box;
    std::shared_ptr<jKDNode> left;
    std::shared_ptr<jKDNode> right;
    std::vector<std::shared_ptr<jTriangle>> triangles;
    bool leaf;
};

}