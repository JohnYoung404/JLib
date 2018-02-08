#pragma once
#include <cfloat>
#include <algorithm>
#include "jVector.h"
#include "jRay.h"

namespace jLib {
namespace jGraphic {

class jAABBox
{
public:
    jAABBox(jVec3f bl_ = jVec3f(), jVec3f tr_ = jVec3f()) {
        bl = bl_, tr = tr_;
    }

    // Expand to fit box
    void expand(const jAABBox &box) {
        if (box.bl.x() < bl.x()) bl.x() = box.bl.x();
        if (box.bl.y() < bl.y()) bl.y() = box.bl.y();
        if (box.bl.z() < bl.z()) bl.z() = box.bl.z();
                                                  
        if (box.tr.x() > tr.x()) tr.x() = box.tr.x();
        if (box.tr.y() > tr.y()) tr.y() = box.tr.y();
        if (box.tr.z() > tr.z()) tr.z() = box.tr.z();
    }

    // Expand to fit point
    void expand(const jVec3f &vec) {
        if (vec.x() < bl.x()) bl.x() = vec.x();
        if (vec.y() < bl.y()) bl.y() = vec.y();
        if (vec.z() < bl.z()) bl.z() = vec.z();
    }

    // Returns longest axis: 0, 1, 2 for x, y, z respectively
    int get_longest_axis() {
        jVec3f diff = tr - bl;
        if (diff.x() > diff.y() && diff.x() > diff.z()) return 0;
        if (diff.y() > diff.x() && diff.y() > diff.z()) return 1;
        return 2;
    }

    // Check if ray intersects with box. Returns true/false and stores distance in t
    bool intersection(const jRay &r, jfloat &t) {
        jfloat tx1 = (bl.x() - r.Origin().x())*r.InvDirection().x();
        jfloat tx2 = (tr.x() - r.Origin().x())*r.InvDirection().x();

        jfloat tmin = std::min(tx1, tx2);
        jfloat tmax = std::max(tx1, tx2);

        jfloat ty1 = (bl.y() - r.Origin().y())*r.InvDirection().y();
        jfloat ty2 = (tr.y() - r.Origin().y())*r.InvDirection().y();

        tmin = std::max(tmin, std::min(ty1, ty2));
        tmax = std::min(tmax, std::max(ty1, ty2));

        jfloat tz1 = (bl.z() - r.Origin().z())*r.InvDirection().z();
        jfloat tz2 = (tr.z() - r.Origin().z())*r.InvDirection().z();

        tmin = std::max(tmin, std::min(tz1, tz2));
        tmax = std::min(tmax, std::max(tz1, tz2));
        t = tmin;

        return tmax >= tmin;
    }
private:
    jVec3f bl;     // Bottom left (min)
    jVec3f tr;     // Top right   (max)
};

}}