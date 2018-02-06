#include "jPNG.h"
#include <iostream>

namespace jLib {
namespace jMedia {

bool jPNG::LoadImage(const char* filename)
{
    _data.clear();
    unsigned error = lodepng::decode(_data, _width, _height, filename);
    if (error) { std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl << std::endl; return false; }
    _imgLoaded = true;
    return true;
}

bool jPNG::SaveImage(const char* filename)
{
    unsigned error = lodepng::encode(filename, _data, Width(), Height());
    if (error) { std::cerr << "encode error " << error << ": " << lodepng_error_text(error) << std::endl << std::endl; return false; }
    return true;
}

void jPNG::CreateEmpty(int width, int height)
{
    _width = width;
    _height = height;
    _imgLoaded = true;
    _data.resize(_width * _height * Channel(), 255);
}

}}
