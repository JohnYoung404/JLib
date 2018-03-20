// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/17/2018]
// Description : program entrance.

#include <iostream>
#include "jVec3f_SIMD.h"
#include <ctime>
#include "jSphere.h"
#include "jMesh.h"
#include "jRandom.h"
#include "jRenderer.h"

int main(int argc, char** argv)
{
    using namespace jRayTracing;

    time_t start, stop;
    time(&start);               // Start execution timer
    int samples = 20;            // Default samples per pixel

    auto cameraPtr = std::make_shared<jCamera>(jVec3f(0, -5, 2.5), jVec3f(0, 0, 1), 1280, 720);
    auto scenePtr = std::make_shared<jScene>();   // Create scene

    scenePtr->add(std::make_shared<jSphere>(jVec3f(0, 0, -1000), jReal(1000), std::make_shared<jDiffuseMaterial>(jVec3f(1, 1, 1))));
    scenePtr->add(std::make_shared<jSphere>(jVec3f(-1004, 0, 0), jReal(1000), std::make_shared<jDiffuseMaterial>(jVec3f(0.85, 0.4, 0.4))));
    scenePtr->add(std::make_shared<jSphere>(jVec3f(1004, 0, 0), jReal(1000), std::make_shared<jDiffuseMaterial>(jVec3f(0.4, 0.4, 0.85))));
    scenePtr->add(std::make_shared<jSphere>(jVec3f(0, 1006, 0), jReal(1000), std::make_shared<jDiffuseMaterial>(jVec3f(1, 1, 1))));

    scenePtr->add(std::make_shared<jSphere>(jVec3f(0, 0, 110), jReal(100), std::make_shared<jEmitMaterial>(jVec3f(1, 1, 1), jVec3f(2.2, 2.2, 2.2))));
    scenePtr->add(std::make_shared<jMesh>(jVec3f::zero(), "../models/dragon2.obj", std::make_shared<jDiffuseMaterial>(jVec3f(0.9, 0.9, 0.9))));//(jVec3f(0.93, 0.78, 0.06))));

    jRenderer renderer = jRenderer(scenePtr, cameraPtr);  // Create renderer with our scene and camera
    renderer.render(samples);                       // Render image to pixel buffer
    renderer.save_image("render.png");              // Save image

                                                    // Print duration information
    time(&stop);
    double diff = difftime(stop, start);
    int hrs = (int)diff / 3600;
    int mins = ((int)diff / 60) - (hrs * 60);
    int secs = (int)diff - (hrs * 3600) - (mins * 60);
    printf("\rRendering (%i samples): Complete!\nTime Taken: %i hrs, %i mins, %i secs\n\n", samples, hrs, mins, secs);
    //std::cout << jObjCounter<jVec3f>::ObjectCreated() << std::endl;
    //std::cout << jObjCounter<jVec3f>::ObjectAlive() << std::endl;
    //std::cout << jObjCounter<jRay>::ObjectCreated() << std::endl;
    //std::cout << jObjCounter<jRay>::ObjectAlive() << std::endl;
    getchar();
}