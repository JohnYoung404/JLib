#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/18/2018]
// Description : AABB box to accelerate intersection.

#include <cfloat>
#include <algorithm>
#include "jCommon.h"
#include "jRay.h"
#include "jVec3f_SIMD.h"

namespace jRayTracing
{

J_ALIGN(16) class jAABBox
{
public:
    jAABBox(const jVec3f &bl_ = jVec3f::zero(), const jVec3f &tr_ = jVec3f::zero()) : bl(bl_), tr(tr_) {}

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
    int get_longest_axis() const {
        jVec3f diff = tr - bl;
        if (diff.x() > diff.y() && diff.x() > diff.z()) return 0;
        if (diff.y() > diff.x() && diff.y() > diff.z()) return 1;
        return 2;
    }

    bool test_area_code(const jRay &r) const
    {
        jVec3f orig = r.Origin();

        jReal offset_x_tr = tr.x() - orig.x();
        jReal offset_x_bl = bl.x() - orig.x();
        jReal offset_y_tr = tr.y() - orig.y();
        jReal offset_y_bl = bl.y() - orig.y();
        jReal offset_z_tr = tr.z() - orig.z();
        jReal offset_z_bl = bl.z() - orig.z();

        unsigned char code_x = offset_x_tr < 0 ? 01 : offset_x_bl > 0 ? 10 : 00;
        unsigned char code_y = offset_y_tr < 0 ? 01 : offset_y_bl > 0 ? 10 : 00;
        unsigned char code_z = offset_z_tr < 0 ? 01 : offset_z_bl > 0 ? 10 : 00;

        if ((code_x || code_y || code_z) && (code_x == r.code_x || code_y == r.code_y || code_z == r.code_z)) return false;
        return true;
    }

    // Check if ray intersects with box. Returns true/false and stores distance in t
    bool intersection(const jRay &r, jReal &t) const
    {

        jVec3f orig = r.Origin();

        jReal offset_x_tr = tr.x() - orig.x();
        jReal offset_x_bl = bl.x() - orig.x();
        jReal offset_y_tr = tr.y() - orig.y();
        jReal offset_y_bl = bl.y() - orig.y();
        jReal offset_z_tr = tr.z() - orig.z();
        jReal offset_z_bl = bl.z() - orig.z();

        unsigned char code_x = offset_x_tr < 0 ? 01 : offset_x_bl > 0 ? 10 : 00;
        unsigned char code_y = offset_y_tr < 0 ? 01 : offset_y_bl > 0 ? 10 : 00;
        unsigned char code_z = offset_z_tr < 0 ? 01 : offset_z_bl > 0 ? 10 : 00;

        if ((code_x || code_y || code_z) && (code_x == r.code_x || code_y == r.code_y || code_z == r.code_z)) return false;

        jReal tx1 = (offset_x_bl)*r.InvDirection().x();
        jReal tx2 = (offset_x_tr)*r.InvDirection().x();

        jReal ty1 = (offset_y_bl)*r.InvDirection().y();
        jReal ty2 = (offset_y_tr)*r.InvDirection().y();

        jReal tz1 = (offset_z_bl)*r.InvDirection().z();
        jReal tz2 = (offset_z_tr)*r.InvDirection().z();

        auto &minmax_x = std::minmax(tx1, tx2);
        auto &minmax_y = std::minmax(ty1, ty2);
        auto &minmax_z = std::minmax(tz1, tz2);

        jReal tmin = minmax_x.first > minmax_y.first && minmax_x.first > minmax_z.first ? minmax_x.first : minmax_y.first > minmax_z.first ? minmax_y.first : minmax_z.first;
        jReal tmax = minmax_x.second < minmax_y.second && minmax_x.second < minmax_z.second ? minmax_x.second : minmax_y.second < minmax_z.second ? minmax_y.second : minmax_z.second;
        t = tmin;

        return tmax >= tmin;
    }
private:
    jVec3f bl;     // Bottom left (min)
    jVec3f tr;     // Top right   (max)
};

}