#pragma once

#include <vector>
#include "jRay.h"
#include "jVector.h"
#include "jAABBox.h"
#include "jTriangle.h"

namespace jLib {
namespace jGraphic {

class jKDNode
{
public:
    std::shared_ptr<jKDNode> build(std::vector<std::shared_ptr<jTriangle>> &tris, int depth);
    bool hit(const std::shared_ptr<jKDNode> &node, const jRay &ray, jfloat &t, jfloat &tmin, jVec3f &norm, jVec3f &color) const;

    jAABBox box;
    std::shared_ptr<jKDNode> left;
    std::shared_ptr<jKDNode> right;
    std::vector<std::shared_ptr<jTriangle>> triangles;
    bool leaf;
};

}}