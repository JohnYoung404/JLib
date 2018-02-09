#include "jKDTree.h"

namespace jLib {
namespace jGraphic {

std::shared_ptr<jKDNode> jKDNode::build(std::vector<std::shared_ptr<jTriangle>> &tris, int depth)
{
    auto node = std::make_shared<jKDNode>();
    node->leaf = false;
    node->triangles = std::vector<std::shared_ptr<jTriangle>>();
    node->left = nullptr;
    node->right = nullptr;
    node->box = jAABBox();

    if (tris.size() == 0) return node;

    if (depth > 25 || tris.size() <= 6) {
        node->triangles = tris;
        node->leaf = true;
        node->box = tris[0]->get_bounding_box();

        for (size_t i = 1; i < tris.size(); i++) {
            node->box.expand(tris[i]->get_bounding_box());
        }

        node->left = std::make_shared<jKDNode>();
        node->right = std::make_shared<jKDNode>();
        node->left->triangles = std::vector<std::shared_ptr<jTriangle>>();
        node->right->triangles = std::vector<std::shared_ptr<jTriangle>>();

        return node;
    }

    node->box = tris[0]->get_bounding_box();
    jVec3f midpt = jVec3f::zero();
    jfloat tris_recp = jfloat(1) / tris.size();

    for (size_t i = 1; i < tris.size(); i++) {
        node->box.expand(tris[i]->get_bounding_box());
        midpt = midpt + (tris[i]->get_midpoint() * tris_recp);
    }

    std::vector<std::shared_ptr<jTriangle>> left_tris;
    std::vector<std::shared_ptr<jTriangle>> right_tris;
    int axis = node->box.get_longest_axis();

    for (size_t i = 0; i < tris.size(); i++) {
        switch (axis) {
        case 0:
            midpt.x() >= tris[i]->get_midpoint().x() ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
            break;
        case 1:
            midpt.y() >= tris[i]->get_midpoint().y() ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
            break;
        case 2:
            midpt.z() >= tris[i]->get_midpoint().z() ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
            break;
        }
    }

    if (tris.size() == left_tris.size() || tris.size() == right_tris.size()) {
        node->triangles = tris;
        node->leaf = true;
        node->box = tris[0]->get_bounding_box();

        for (size_t i = 1; i < tris.size(); i++) {
            node->box.expand(tris[i]->get_bounding_box());
        }

        node->left = std::make_shared<jKDNode>();
        node->right = std::make_shared<jKDNode>();
        node->left->triangles = std::vector<std::shared_ptr<jTriangle>>();
        node->right->triangles = std::vector<std::shared_ptr<jTriangle>>();

        return node;
    }

    node->left = build(left_tris, depth + 1);
    node->right = build(right_tris, depth + 1);

    return node;
}

bool jKDNode::hit(const std::shared_ptr<jKDNode> &node, const jRay &ray, jfloat &t, jfloat &tmin, jVec3f &norm, jVec3f &color) const
{
    jfloat dist;
    if (node->box.intersection(ray, dist)) {
        if (dist > tmin) return false;

        bool hit_tri = false;
        bool hitLeft = false;
        bool hitRight = false;

        size_t tri_idx;

        if (!node->leaf) 
        {
            if (node->left->triangles.size() > 0)
                hitLeft = hit(node->left, ray, t, tmin, norm, color);
            if (node->right->triangles.size() > 0)
                hitRight = hit(node->right, ray, t, tmin, norm, color);

            return  hitLeft||hitRight ;
        }
        else {
            auto triangles_size = node->triangles.size();
            for (size_t i = 0; i < triangles_size; i++) {
                if (node->triangles[i]->intersect(ray, t, tmin, norm)) {
                    hit_tri = true;
                    tmin = t;
                    tri_idx = i;
                }
            }
            if (hit_tri) {
                //jVec3f p = ray.Origin() + ray.Direction() * tmin;
                //color = node->triangles[tri_idx]->get_colour_at(p);
                color = node->triangles[tri_idx]->get_color();
                return true;
            }
        }
    }
    return false;
}

}}