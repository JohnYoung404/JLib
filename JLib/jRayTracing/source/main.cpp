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

    auto cameraInstance = jCamera(jVec3f(0, -5, 2.5), jVec3f(0, 0, 1), 1280, 720);
    auto sceneInstance = jScene();   // Create scene

    jSphere sphere_1 = jSphere(jVec3f(0, 0, -1000), jReal(1000), std::make_shared<jDiffuseMaterial>(jVec3f(1, 1, 1)));
    jSphere sphere_2 = jSphere(jVec3f(-1004, 0, 0), jReal(1000), std::make_shared<jDiffuseMaterial>(jVec3f(0.85, 0.4, 0.4)));
    jSphere sphere_3 = jSphere(jVec3f(1004, 0, 0), jReal(1000), std::make_shared<jDiffuseMaterial>(jVec3f(0.4, 0.4, 0.85)));
    jSphere sphere_4 = jSphere(jVec3f(0, 1006, 0), jReal(1000), std::make_shared<jDiffuseMaterial>(jVec3f(1, 1, 1)));
    jSphere sphere_5 = jSphere(jVec3f(0, 0, 110), jReal(100), std::make_shared<jEmitMaterial>(jVec3f(1, 1, 1), jVec3f(2.2, 2.2, 2.2)));
    jDiffuseMaterial diff_mat = jDiffuseMaterial(jVec3f(0.9, 0.9, 0.9));
    jMesh mesh_1 = jMesh(jVec3f::zero(), "../models/dragon2.obj", &diff_mat);

    sceneInstance.add(&sphere_1);
    sceneInstance.add(&sphere_2);
    sceneInstance.add(&sphere_3);
    sceneInstance.add(&sphere_4);
    sceneInstance.add(&sphere_5);
    sceneInstance.add(&mesh_1);

    //sceneInstance.add(std::make_shared<jMesh>(jVec3f::zero(), "../models/dragon2.obj", std::make_shared<jDiffuseMaterial>(jVec3f(0.9, 0.9, 0.9))));//(jVec3f(0.93, 0.78, 0.06))));

    jRenderer renderer = jRenderer(&sceneInstance, &cameraInstance);  // Create renderer with our scene and camera
    renderer.render(samples);                       // Render image to pixel buffer
    renderer.save_image("render.png");              // Save image

                                                    // Print duration information
    time(&stop);
    double diff = difftime(stop, start);
    int hrs = (int)diff / 3600;
    int mins = ((int)diff / 60) - (hrs * 60);
    int secs = (int)diff - (hrs * 3600) - (mins * 60);
    printf("\rRendering (%i samples): Complete!\nTime Taken: %i hrs, %i mins, %i secs\n\n", samples, hrs, mins, secs);
    getchar();
}