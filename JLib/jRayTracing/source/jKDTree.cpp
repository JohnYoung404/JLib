#include "jKDTree.h"

namespace jRayTracing{

jKDNode* jKDNode::build(std::vector<jTriangle*> &tris, int depth)
{
    jKDNode* aligned_buffer = (jKDNode*)_aligned_malloc(sizeof(jKDNode), 16);
    auto node = new (aligned_buffer) jKDNode();
    node->leaf = false;
    node->triangles = std::vector<jTriangle*>();
    node->left = nullptr;
    node->right = nullptr;
    jVec3f_SIMD _zero = jVec3f_SIMD{0, 0, 0};
    node->box = jAABBox(_zero, _zero);

    if (tris.size() == 0) return node;

    if (depth > 25 || tris.size() <= 6) {
        node->triangles = tris;
        node->leaf = true;
        node->box = tris[0]->get_bounding_box();

        for (size_t i = 1; i < tris.size(); i++) {
            node->box.expand(tris[i]->get_bounding_box());
        }
        aligned_buffer = (jKDNode*)_aligned_malloc(sizeof(jKDNode), 16);
        node->left = new (aligned_buffer) jKDNode();
        aligned_buffer = (jKDNode*)_aligned_malloc(sizeof(jKDNode), 16);
        node->right = new (aligned_buffer) jKDNode();
        node->left->triangles = std::vector<jTriangle*>();
        node->right->triangles = std::vector<jTriangle*>();

        return node;
    }

    node->box = tris[0]->get_bounding_box();
    jVec3f midpt = jVec3f::zero();
    jReal tris_recp = jReal(1) / tris.size();

    for (size_t i = 1; i < tris.size(); i++) {
        node->box.expand(tris[i]->get_bounding_box());
        midpt = midpt + (tris[i]->get_midpoint() * tris_recp);
    }

    std::vector<jTriangle*> left_tris;
    std::vector<jTriangle*> right_tris;
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
        
        aligned_buffer = (jKDNode*)_aligned_malloc(sizeof(jKDNode), 16);
        node->left = new (aligned_buffer) jKDNode();
        aligned_buffer = (jKDNode*)_aligned_malloc(sizeof(jKDNode), 16);
        node->right = new (aligned_buffer) jKDNode();
        node->left->triangles = std::vector<jTriangle*>();
        node->right->triangles = std::vector<jTriangle*>();

        return node;
    }

    node->left = build(left_tris, depth + 1);
    node->right = build(right_tris, depth + 1);

    return node;
}

bool jKDNode::hit(jKDNode* node, const jRay &ray, jReal &t, jReal &tmin, jVec3f &norm/*, jVec3f &color*/) const
{
    jReal dist;
    if (node->box.intersection(ray, dist)) {
        if (dist > tmin) return false;

        //size_t tri_idx;

        if (!node->leaf)
        {
            bool hitLeft = hit(node->left, ray, t, tmin, norm/*, color*/);
            bool hitRight = hit(node->right, ray, t, tmin, norm/*, color*/);

            return  hitLeft || hitRight;
        }
        else {
            bool hit_tri = false;
            auto triangles_size = node->triangles.size();
            for (size_t i = 0; i < triangles_size; i++) {
                if (node->triangles[i]->intersect(ray, t, tmin, norm)) {
                    hit_tri = true;
                    tmin = t;
                    //tri_idx = i;
                }
            }
            return hit_tri;
            //if (hit_tri) {
            //    //jVec3f p = ray.Origin() + ray.Direction() * tmin;
            //    //color = node->triangles[tri_idx]->get_colour_at(p);
            //    color = node->triangles[tri_idx]->get_color();
            //    return true;
            //}
        }
    }
    return false;
}

}