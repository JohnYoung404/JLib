// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/30/2017]
// Description : Simple Bitmap Process.
#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <fstream>
#include <cstdio>
#include <iosfwd>
#include "boost/assert.hpp"

//BMP structure information : http://www.cnblogs.com/xiekeli/archive/2012/05/09/2491191.html

namespace jGraphic {

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
	jBitMap() : fileHeaderPtr_(nullptr) , infoHeaderPtr_(nullptr), rgbMapPtr_(nullptr) {}

	bool LoadImage(const char* filePath);
	bool SaveImage(const char* filePath);
    void CreateEmpty(int width, int height);
    void ClearImage();

	bool Clear() {
		fileHeaderPtr_.reset();
		infoHeaderPtr_.reset();
		rgbMapPtr_.reset();
		imgData.clear();
	}

	inline const int Width() {
		if (infoHeaderPtr_.get() != nullptr) {
			return infoHeaderPtr_->biWidth;
		}
		return 0;
	}

	inline const int Height() {
		if (infoHeaderPtr_.get() != nullptr) {
			return infoHeaderPtr_->biHeight;
		}
		return 0;
	}

	inline const int Channel() {
		if (infoHeaderPtr_.get() != nullptr) {
			return infoHeaderPtr_->biBitCount >> 3;
		}
		return 0;
	}

	inline uint8_t& RefOfPos(int horiIndex, int vertIndex, int channel) {
#ifdef _DEBUG
        BOOST_ASSERT(horiIndex < Width() && horiIndex >= 0 && vertIndex >= 0 && vertIndex < Height());
#endif
		return imgData[vertIndex * infoHeaderPtr_->biWidth * Channel() + horiIndex * Channel() + channel];
	}

private:
	std::shared_ptr<jBitMapStruct::jBitMapFileHeader> fileHeaderPtr_;
	std::shared_ptr<jBitMapStruct::jBitMapInfoHeader> infoHeaderPtr_;
	std::shared_ptr<jBitMapStruct::jRGBMap> rgbMapPtr_;
	std::vector<uint8_t> imgData;

	bool imgLoaded_;
};

}



