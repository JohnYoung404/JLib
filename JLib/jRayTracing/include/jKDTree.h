#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [4/16/2018]
// Description : KD-tree to accelerate intersection.

#include "jCommon.h"
#include <vector>
#include "jRay.h"
#include "jVec3f_SIMD.h"
#include "jAABBox.h"
#include "jTriangle.h"

namespace jRayTracing{

J_ALIGN(16) class jKDNode
{
public:
    jKDNode* build(std::vector<jTriangle*> &tris, int depth);
    bool hit(jKDNode* node, const jRay &ray, jReal &t, jReal &tmin, jVec3f &norm/*, jVec3f &color*/) const;

    jAABBox box;
    jKDNode* left;
    jKDNode* right;
    std::vector<jTriangle*> triangles;
    bool leaf;
};

}