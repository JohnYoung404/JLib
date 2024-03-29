#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [4/16/2018]
// Description : Renderer that manages rendering process.

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