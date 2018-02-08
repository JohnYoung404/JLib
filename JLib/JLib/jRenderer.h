#pragma once

#include "jScene.h"
#include "jRayTraceCamera.h"

namespace jLib {
namespace jGraphic {

class jRenderer
{
public:
    jRenderer(std::shared_ptr<jScene> scenePtr, std::shared_ptr<jRayTraceCamera> cameraPtr);
    void render(int samples = 4);
    void save_image(const char* file_path);
private:
    std::shared_ptr<jScene> _scene;
    std::shared_ptr<jRayTraceCamera> _camera;
    std::vector<jVec3f> _pixel_buffer;
};

}}