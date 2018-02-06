// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/30/2017]
// Description : Simple Bitmap Process.
#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <boost/assert.hpp>
#include "jColor.h"

//BMP structure information : http://www.cnblogs.com/xiekeli/archive/2012/05/09/2491191.html
namespace jLib
{

namespace jMedia {

#pragma pack(1) // For MSVC,disable struct Pack,or short will take 32 bits memory as int32_t
namespace jBitMapStruct {

	struct jBitMapFileHeader
	{
		uint16_t bfType;
		uint32_t bfSize;
		uint16_t bfReserved1;
		uint16_t bfReserved2;
		uint32_t bfOffBits;
	};

	struct jBitMapInfoHeader
	{
		uint32_t biSize;
		int32_t biWidth;
		int32_t biHeight;
		uint16_t biPlanes;
		uint16_t biBitCount;
		uint32_t biCompression;
		uint32_t biSizeImage;
		int32_t biXPelsPerMeter;
		int32_t biYPelsPerMeter;
		uint32_t biClrUsed;
		uint32_t biClrImportant;
	};

	struct jRGBMap
	{
		uint8_t rgbBlue;
		uint8_t rgbGreen;
		uint8_t rgbRed;
		uint8_t rgbReserved;
	};

}
#pragma pack()

class jBitMap
{
	enum { rgbMapSize = 256 };
public:
	jBitMap() : fileHeaderPtr_(nullptr), infoHeaderPtr_(nullptr), rgbMapPtr_(nullptr) {}

	enum channel{ B = 0, G = 1, R = 2, A = 3 };

	bool LoadImage(const char* filePath);
	bool SaveImage(const char* filePath);
	void CreateEmpty(int width, int height);
	void ClearImage();

	inline void Clear() {
		fileHeaderPtr_.reset();
		infoHeaderPtr_.reset();
		rgbMapPtr_.reset();
		imgData.clear();
	}

	inline const int Width() const {
		if (infoHeaderPtr_.get() != nullptr) {
			return infoHeaderPtr_->biWidth;
		}
		return 0;
	}

	inline const int Height() const {
		if (infoHeaderPtr_.get() != nullptr) {
			return infoHeaderPtr_->biHeight;
		}
		return 0;
	}

	inline const int Channel() const {
		if (infoHeaderPtr_.get() != nullptr) {
			return infoHeaderPtr_->biBitCount >> 3;
		}
		return 0;
	}

	inline uint8_t& at(int horiIndex, int vertIndex, int channel) {
#ifdef _DEBUG
		BOOST_ASSERT(horiIndex < Width() && horiIndex >= 0 && vertIndex >= 0 && vertIndex < Height() && channel < Channel() && channel >= 0);
#endif
		return imgData[vertIndex * infoHeaderPtr_->biWidth * Channel() + horiIndex * Channel() + channel];
	}

	inline const uint8_t& at(int horiIndex, int vertIndex, int channel) const {
#ifdef _DEBUG
		BOOST_ASSERT(horiIndex < Width() && horiIndex >= 0 && vertIndex >= 0 && vertIndex < Height() && channel < Channel() && channel >= 0);
#endif
		return imgData[vertIndex * infoHeaderPtr_->biWidth * Channel() + horiIndex * Channel() + channel];
	}

    inline void SetPixel(int horiIndex, int vertIndex, const jLib::jGraphic::jColor &color)
    {
        if (Channel() == 3 || Channel() == 4)
        {
            at(horiIndex, vertIndex, jMedia::jBitMap::B) = color.B();
            at(horiIndex, vertIndex, jMedia::jBitMap::G) = color.G();
            at(horiIndex, vertIndex, jMedia::jBitMap::R) = color.R();
            if (Channel() == 4) at(horiIndex, vertIndex, jMedia::jBitMap::A) = color.A();
        }
    }

    inline const jLib::jGraphic::jColor GetPixel(int horiIndex, int vertIndex) const
    {
        jGraphic::jColor ret;
        if (Channel() == 3 || Channel() == 4)
        {
            ret.B() = at(horiIndex, vertIndex, jMedia::jBitMap::B);
            ret.G() = at(horiIndex, vertIndex, jMedia::jBitMap::G);
            ret.R() = at(horiIndex, vertIndex, jMedia::jBitMap::R);
            ret.A() = 255;
            if (Channel() == 4) ret.A() = at(horiIndex, vertIndex, jMedia::jBitMap::A);
        }
        return ret;
    }
private:
	std::shared_ptr<jBitMapStruct::jBitMapFileHeader> fileHeaderPtr_;
	std::shared_ptr<jBitMapStruct::jBitMapInfoHeader> infoHeaderPtr_;
	std::shared_ptr<jBitMapStruct::jRGBMap> rgbMapPtr_;
	std::vector<uint8_t> imgData;
	bool imgLoaded_;
};

}

}

#include "jTestBase.h"
namespace jLib {
	class jBitMapTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			jMedia::jBitMap m;
			m.CreateEmpty(1920, 1080);
			for (int i = 0; i < 1920; ++i)
			{
				for (int j = 0; j < 1080; ++j) {
					float hori_off = (float)i / 1920;
					float vert_off = (float)j / 1080;
                    m.SetPixel(i, j, jGraphic::jColor(255, 255, 0, 0));
				}
			}
			m.SaveImage("jBitMapTest/create_plain_red_img.bmp");
			std::cout << "Created a plain red image." << std::endl;

			m.LoadImage("srcImg/test.bmp");
			for (int i = 0; i < m.Width(); ++i)
			{
				for (int j = 0; j < m.Height(); ++j) {
                    auto flipped_color = m.GetPixel(i, j);
                    flipped_color.R() = 255 - flipped_color.R();
                    flipped_color.G() = 255 - flipped_color.G();
                    flipped_color.B() = 255 - flipped_color.B();
                    m.SetPixel(i, j, flipped_color);
				}
			}
			m.SaveImage("jBitMapTest/rgb_filp_of_test_img.bmp");
			std::cout << "Flip RGB of the test image." << std::endl;
		}
	};
}
