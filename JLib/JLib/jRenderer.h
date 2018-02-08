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

#include "time.h"
#include "jSphere.h"
#include "jMesh.h"

namespace jLib {
    class jRendererTest final : public jITestable {
    public:
        virtual void test() override {
            jITestable::test();
            using namespace jGraphic;

            time_t start, stop;
            time(&start);               // Start execution timer
            int samples = 20;            // Default samples per pixel

            jRayTraceCamera camera = jRayTraceCamera(jVec3f(0, -5, 2.5), jVec3f(0, 0, 1), 1280, 720);     // Create camera
            jScene scene;                                              // Create scene

            scene.add(std::make_shared<jSphere>(jVec3f(0, 0, -1000), jfloat(1000), std::make_shared<jDiffuseMaterial>(jVec3f(1, 1, 1))));
            scene.add(std::make_shared<jSphere>(jVec3f(-1004, 0, 0), jfloat(1000), std::make_shared<jDiffuseMaterial>(jVec3f(0.85, 0.4, 0.4))));
            scene.add(std::make_shared<jSphere>(jVec3f(1004, 0, 0), jfloat(1000), std::make_shared<jDiffuseMaterial>(jVec3f(0.4, 0.4, 0.85))));
            scene.add(std::make_shared<jSphere>(jVec3f(0, 1006, 0), jfloat(1000), std::make_shared<jDiffuseMaterial>(jVec3f(1, 1, 1))));

            scene.add(std::make_shared<jSphere>(jVec3f(0, 0, 110), jfloat(100), std::make_shared<jEmitMaterial>(jVec3f(1, 1, 1), jVec3f(2.2, 2.2, 2.2))));
            scene.add(std::make_shared<jMesh>(jVec3f::zero(), "../models/dragon2.obj", std::make_shared<jRefractMaterial>(jVec3f(0.9, 0.9, 0.9))));
            //scene.add(dynamic_cast<Object*>(new Sphere(Vec(-1004, 0, 0), 1000, Material(DIFF, Vec(0.85, 0.4, 0.4)))));
            //scene.add(dynamic_cast<Object*>(new Sphere(Vec(1004, 0, 0), 1000, Material(DIFF, Vec(0.4, 0.4, 0.85)))));
            //scene.add(dynamic_cast<Object*>(new Sphere(Vec(0, 1006, 0), 1000, Material())));
            //scene.add(dynamic_cast<Object*>(new Sphere(Vec(0, 0, 110), 100, Material(EMIT, Vec(1, 1, 1), Vec(2.2, 2.2, 2.2)))));
            ////scene.add( dynamic_cast<Object*>(new Mesh(Vec(), "../obj/dragon2.obj", Material(REFR, Vec(0.93, 0.78, 0.06)))) );
            //scene.add(dynamic_cast<Object*>(new Mesh(Vec(), "../obj/dragon2.obj", Material(REFR, Vec(0.9, 0.9, 0.9)))));
            //
            //
            //Renderer renderer = Renderer(&scene, &camera);  // Create renderer with our scene and camera
            //renderer.render(samples);                       // Render image to pixel buffer
            //renderer.save_image("render.png");              // Save image
            //
            //                                                // Print duration information
            //time(&stop);
            //double diff = difftime(stop, start);
            //int hrs = (int)diff / 3600;
            //int mins = ((int)diff / 60) - (hrs * 60);
            //int secs = (int)diff - (hrs * 3600) - (mins * 60);
            //printf("\rRendering (%i samples): Complete!\nTime Taken: %i hrs, %i mins, %i secs\n\n", samples, hrs, mins, secs);
            //return 0;
        }
    };
}