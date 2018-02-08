#include <iostream>
#include "jMesh.h"

namespace jLib {
namespace jGraphic {

jMesh::jMesh(jVec3f pos, const char* file_path, std::shared_ptr<jIRayTracableMaterial> material) : jSceneObj(pos), _materialPtr(material)
{
    std::string mtlbasepath;
    std::string inputfile = file_path;
    size_t div_pos = inputfile.find_last_of("/");
    mtlbasepath = inputfile.substr(0, div_pos + 1);

    std::cout << "Loading " << file_path << "..." << std::endl;
    // Attempt to load mesh
    std::string err = tinyobj::LoadObj(_shapes, _materials, inputfile.c_str(), mtlbasepath.c_str());

    if (!err.empty()) {
        std::cerr << err << std::endl;
        exit(1);
    }
    std::cout << " - Generating k-d tree...\n" << std::endl;

    size_t shapes_size, indices_size, materials_size;
    shapes_size = _shapes.size();
    materials_size = _materials.size();

    // Load materials/textures from obj
    // TODO: Only texture is loaded at the moment, need to implement material types and colours
    for (int i = 0; i < materials_size; i++) {
        std::string texture_path = "";

        if (!_materials[i].diffuse_texname.empty()) {
            if (_materials[i].diffuse_texname[0] == '/') texture_path = _materials[i].diffuse_texname;
            texture_path = mtlbasepath + _materials[i].diffuse_texname;
            _matPtrs.push_back(std::make_shared<jRefractMaterial>(_materialPtr->get_color()));
        }
        else {
            _matPtrs.push_back(std::make_shared<jRefractMaterial>(_materialPtr->get_color()));
        }

    }

    // Load triangles from obj
    for (int i = 0; i < shapes_size; i++) {
        indices_size = _shapes[i].mesh.indices.size() / 3;
        for (size_t f = 0; f < indices_size; f++) {

            // Triangle vertex coordinates
            jVec3f v0_ = jVec3f(
                _shapes[i].mesh.positions[_shapes[i].mesh.indices[3 * f] * 3],
                _shapes[i].mesh.positions[_shapes[i].mesh.indices[3 * f] * 3 + 1],
                _shapes[i].mesh.positions[_shapes[i].mesh.indices[3 * f] * 3 + 2]
            ) + get_pos();

            jVec3f v1_ = jVec3f(
                _shapes[i].mesh.positions[_shapes[i].mesh.indices[3 * f + 1] * 3],
                _shapes[i].mesh.positions[_shapes[i].mesh.indices[3 * f + 1] * 3 + 1],
                _shapes[i].mesh.positions[_shapes[i].mesh.indices[3 * f + 1] * 3 + 2]
            ) + get_pos();

            jVec3f v2_ = jVec3f(
                _shapes[i].mesh.positions[_shapes[i].mesh.indices[3 * f + 2] * 3],
                _shapes[i].mesh.positions[_shapes[i].mesh.indices[3 * f + 2] * 3 + 1],
                _shapes[i].mesh.positions[_shapes[i].mesh.indices[3 * f + 2] * 3 + 2]
            ) + get_pos();

            jVec3f t0_, t1_, t2_;

            //Attempt to load triangle texture coordinates
            if (_shapes[i].mesh.indices[3 * f + 2] * 2 + 1 < _shapes[i].mesh.texcoords.size()) {
                t0_ = jVec3f(
                    _shapes[i].mesh.texcoords[_shapes[i].mesh.indices[3 * f] * 2],
                    _shapes[i].mesh.texcoords[_shapes[i].mesh.indices[3 * f] * 2 + 1],
                    0
                );

                t1_ = jVec3f(
                    _shapes[i].mesh.texcoords[_shapes[i].mesh.indices[3 * f + 1] * 2],
                    _shapes[i].mesh.texcoords[_shapes[i].mesh.indices[3 * f + 1] * 2 + 1],
                    0
                );

                t2_ = jVec3f(
                    _shapes[i].mesh.texcoords[_shapes[i].mesh.indices[3 * f + 2] * 2],
                    _shapes[i].mesh.texcoords[_shapes[i].mesh.indices[3 * f + 2] * 2 + 1],
                    0
                );
            }
            else {
                t0_ = jVec3f::zero();
                t1_ = jVec3f::zero();
                t2_ = jVec3f::zero();
            }

            if (_shapes[i].mesh.material_ids[f] < _matPtrs.size())
                tris.push_back(std::make_shared<jTriangle>(v0_, v1_, v2_, t0_, t1_, t2_, _matPtrs[_shapes[i].mesh.material_ids[f]]));
            else
                tris.push_back(std::make_shared<jTriangle>(v0_, v1_, v2_, t0_, t1_, t2_, _materialPtr));
        }
    }

    // Clean up
    _shapes.clear();
    _materials.clear();
    _node = jKDNode().build(tris, 0);
    std::cout << std::endl;
    //bvh = BVH(&tris);
}

jRayObjectItersection jMesh::get_intersection(const jRay& ray)
{
    jfloat t = 0, tmin = INFINITY;
    jVec3f normal = jVec3f::zero();
    jVec3f colour = jVec3f::zero();
    bool hit = _node->hit(_node, ray, t, tmin, normal, colour);
    //bool hit = bvh.getIntersection(ray, t, tmin, normal);
    return jRayObjectItersection(hit, tmin, normal, _materialPtr);
}

}}