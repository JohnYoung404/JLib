#pragma once
#include <boost/assert.hpp>
#include "../extern/lodepng/lodepng.h"
#include "jColor.h"

namespace jLib{
namespace jMedia {

class jPNG
{
public:
    enum channel { R = 0, G = 1, B = 2, A = 3 };
    jPNG() :_width(0), _height(0) {};
    bool LoadImage(const char* filename);
    bool SaveImage(const char* filename);
    void CreateEmpty(int width, int height);
    inline const int Width() const {
        return static_cast<int>(_width);
    }
    inline const int Height() const {
        return static_cast<int>(_height);
    }
    inline const int Channel() const {
        return 4;
    }

    inline uint8_t& at(int horiIndex, int vertIndex, int channel) {
#ifdef _DEBUG
        BOOST_ASSERT(horiIndex < Width() && horiIndex >= 0 && vertIndex >= 0 && vertIndex < Height() && channel < Channel() && channel >= 0);
#endif
        return *(_data.begin() + (Height() - 1 - vertIndex) * Width() * Channel() + horiIndex * Channel() + channel);
    }

    inline const uint8_t& at(int horiIndex, int vertIndex, int channel) const {
#ifdef _DEBUG
        BOOST_ASSERT(horiIndex < Width() && horiIndex >= 0 && vertIndex >= 0 && vertIndex < Height() && channel < Channel() && channel >= 0);
#endif
        
        return *(_data.begin() + (Height() - 1 - vertIndex) * Width() * Channel() + horiIndex * Channel() + channel);
    }

    inline void SetPixel(int horiIndex, int vertIndex, const jLib::jGraphic::jColor &color)
    {
        if (Channel() == 3 || Channel() == 4)
        {
            at(horiIndex, vertIndex, jPNG::B) = color.B();
            at(horiIndex, vertIndex, jPNG::G) = color.G();
            at(horiIndex, vertIndex, jPNG::R) = color.R();
            if (Channel() == 4) at(horiIndex, vertIndex, jPNG::A) = color.A();
        }
    }

    inline const jLib::jGraphic::jColor GetPixel(int horiIndex, int vertIndex) const
    {
        jGraphic::jColor ret;
        if (Channel() == 3 || Channel() == 4)
        {
            ret.B() = at(horiIndex, vertIndex, jPNG::B);
            ret.G() = at(horiIndex, vertIndex, jPNG::G);
            ret.R() = at(horiIndex, vertIndex, jPNG::R);
            ret.A() = 255;
            if (Channel() == 4) ret.A() = at(horiIndex, vertIndex, jPNG::A);
        }
        return ret;
    }

private:
    unsigned int _width, _height;
    std::vector<unsigned char> _data;
    bool _imgLoaded;
};

}}
