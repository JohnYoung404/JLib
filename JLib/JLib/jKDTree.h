#pragma once
#include <vector>
#include "jUtility.h"
#include "jRay.h"
#include "jVector.h"
#include "jAABBox.h"
#include "jTriangle.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

class jKDNode
{
public:
    std::shared_ptr<jKDNode> build(std::vector<std::shared_ptr<jTriangle>> &tris, int depth);
    bool hit(const std::shared_ptr<jKDNode> &node, const jRay &ray, jfloat &t, jfloat &tmin, jVec3f &norm/*, jVec3f &color*/) const;

    jAABBox box;
    std::shared_ptr<jKDNode> left;
    std::shared_ptr<jKDNode> right;
    std::vector<std::shared_ptr<jTriangle>> triangles;
    bool leaf;
};

NAME_SPACE_END
NAME_SPACE_END