// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/30/2017]
// Description : Simple Bitmap Process.
#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <boost/assert.hpp>
#include "jGrid.h"

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
		BOOST_ASSERT(horiIndex < Width() && horiIndex >= 0 && vertIndex >= 0 && vertIndex < Height());
#endif
		return imgData[vertIndex * infoHeaderPtr_->biWidth * Channel() + horiIndex * Channel() + channel];
	}

	inline const uint8_t& at(int horiIndex, int vertIndex, int channel) const {
#ifdef _DEBUG
		BOOST_ASSERT(horiIndex < Width() && horiIndex >= 0 && vertIndex >= 0 && vertIndex < Height());
#endif
		return imgData[vertIndex * infoHeaderPtr_->biWidth * Channel() + horiIndex * Channel() + channel];
	}
private:
	jBitMap(const jBitMap &rhs) = delete;
	jBitMap& operator=(const jBitMap &rhs) = delete;
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
					m.at(i, j, jMedia::jBitMap::B) = 0;
					m.at(i, j, jMedia::jBitMap::G) = 0;
					m.at(i, j, jMedia::jBitMap::R) = 255;
					m.at(i, j, jMedia::jBitMap::A) = 255;
				}
			}
			m.SaveImage("jBitMapTest/create_plain_red_img.bmp");
			std::cout << "Created a plain red image." << std::endl;

			m.LoadImage("srcImg/test.bmp");
			for (int i = 0; i < m.Width(); ++i)
			{
				for (int j = 0; j < m.Height(); ++j) {
					m.at(i, j, jMedia::jBitMap::B) = 255 - m.at(i, j, jMedia::jBitMap::B);
					m.at(i, j, jMedia::jBitMap::G) = 255 - m.at(i, j, jMedia::jBitMap::G);
					m.at(i, j, jMedia::jBitMap::R) = 255 - m.at(i, j, jMedia::jBitMap::R);
					m.at(i, j, jMedia::jBitMap::A) = 255;
				}
			}
			m.SaveImage("jBitMapTest/rgb_filp_of_test_img.bmp");
			std::cout << "Flip RGB of the test image." << std::endl;
		}
	};
}
