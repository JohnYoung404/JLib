#pragma once
#include "jCommon.h"
#include "jScene.h"
#include "jCamera.h"

namespace jRayTracing{

class jRenderer 
{
public:
    jRenderer(std::shared_ptr<jScene> scenePtr, std::shared_ptr<jCamera> cameraPtr);
    void render(int samples = 4);
    void save_image(const char* file_path);
private:
    std::shared_ptr<jScene> _scene;
    std::shared_ptr<jCamera> _camera;
    std::vector<jVec3f> _pixel_buffer;
};

}