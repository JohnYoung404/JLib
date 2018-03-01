#include "jRenderer.h"
#include "jPNG.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)

jRenderer::jRenderer(std::shared_ptr<jScene> scenePtr, std::shared_ptr<jRayTraceCamera> cameraPtr) : _scene(scenePtr), _camera(cameraPtr)
{
    _pixel_buffer.resize(_camera->get_width() * _camera->get_height());
}

void jRenderer::render(int samples /* = 4 */)
{
    int width = _camera->get_width();
    int height = _camera->get_height();
    jfloat samples_recp = jfloat(1) / samples;

    // Main Loop
#pragma omp parallel for schedule(dynamic, 1)       // OpenMP
    for (int y = 0; y < height; y++) {
#pragma warning( push )
#pragma warning( disable : 4838 )
        unsigned short Xi[3] = { 0,0,y*y*y };               // Stores seed for erand48
#pragma warning( pop ) 

        fprintf(stderr, "\rRendering (%i samples): %.2f%% ",      // Prints
            samples, (double)y / height * 100);                   // progress

        for (int x = 0; x < width; x++) {
            jVec3f col = jVec3f::zero();

            for (int a = 0; a < samples; a++) {
                jRay ray = _camera->get_ray(x, y, a > 0, Xi);
                col = col + _scene->trace_ray(ray, 0, Xi);
            }

            _pixel_buffer[(y)*width + x] = col * samples_recp;
        }
    }
}

namespace
{
    // Clamp double to min/max of 0/1
    inline double clamp(double x) { return x < 0 ? 0 : x>1 ? 1 : x; }
    // Clamp to between 0-255
    inline int toInt(double x) { return int(clamp(x) * 255 + .5); }
}

void jRenderer::save_image(const char *file_path) {
    int width = _camera->get_width();
    int height = _camera->get_height();

    std::vector<unsigned char> pixel_buffer;

    int pixel_count = width*height;

    for (int i = 0; i < pixel_count; i++) {
        pixel_buffer.push_back(toInt(_pixel_buffer[i].x()));
        pixel_buffer.push_back(toInt(_pixel_buffer[i].y()));
        pixel_buffer.push_back(toInt(_pixel_buffer[i].z()));
        pixel_buffer.push_back(255);
    }

    //Encode the image
    unsigned error = lodepng::encode(file_path, pixel_buffer, width, height);
    //if there's an error, display it
    if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    pixel_buffer.clear();
}

NAME_SPACE_END
NAME_SPACE_END