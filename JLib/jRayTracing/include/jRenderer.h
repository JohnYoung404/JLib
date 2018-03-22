#pragma once
#include "jCommon.h"
#include "jScene.h"
#include "jCamera.h"

namespace jRayTracing{

class jRenderer 
{
public:
    jRenderer(jScene* scenePtr, jCamera* cameraPtr);
    void render(int samples = 4);
    void save_image(const char* file_path);
private:
    jScene* _scene;
    jCamera* _camera;
    std::vector<jVec3f> _pixel_buffer;
};

}