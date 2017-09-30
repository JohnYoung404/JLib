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

//BMP structure infomation : http://www.cnblogs.com/xiekeli/archive/2012/05/09/2491191.html

namespace jGraphic {

#pragma pack(1) // For MSVC,disable struct Pack,or short will take 32bit mem as int32_t
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
			return imgData[vertIndex * infoHeaderPtr_->biWidth * Channel() + horiIndex * Channel() + channel];
		}

	private:
		std::shared_ptr<jBitMapStruct::jBitMapFileHeader> fileHeaderPtr_;
		std::shared_ptr<jBitMapStruct::jBitMapInfoHeader> infoHeaderPtr_;
		std::shared_ptr<jBitMapStruct::jRGBMap> rgbMapPtr_;
		std::vector<uint8_t> imgData;

		bool imgLoaded_;
	};

	bool jBitMap::LoadImage(const char* filePath) {
		std::ifstream ifs;
		ifs.open(filePath,  std::ios::in | std::ios::binary);
		if (!ifs) {
			imgLoaded_ = false;
			return false;
		}

		fileHeaderPtr_ = std::make_shared<jBitMapStruct::jBitMapFileHeader>(jBitMapStruct::jBitMapFileHeader());
		infoHeaderPtr_ = std::make_shared<jBitMapStruct::jBitMapInfoHeader>(jBitMapStruct::jBitMapInfoHeader());
		rgbMapPtr_ = std::make_shared<jBitMapStruct::jRGBMap>(jBitMapStruct::jRGBMap());

		ifs.read((char*)fileHeaderPtr_.get(), sizeof(jBitMapStruct::jBitMapFileHeader));

		if (fileHeaderPtr_->bfType == 0x4D42) {
			int channels = 0;
			ifs.read((char*)infoHeaderPtr_.get(), sizeof(jBitMapStruct::jBitMapInfoHeader));
			if (infoHeaderPtr_->biBitCount == 8)
			{
				channels = 1;
				ifs.read((char*)rgbMapPtr_.get(), rgbMapSize * sizeof(jBitMapStruct::jRGBMap));
			}
			else if (infoHeaderPtr_->biBitCount == 24) {
				channels = 3;
			}
			else if (infoHeaderPtr_->biBitCount == 32)
			{
				channels = 4;
			}
			int linelength = infoHeaderPtr_->biWidth * channels;
			int offset = linelength % 4;
			if (offset > 4) offset = 4 - offset;
			uint8_t pixVal;
			for (int i = 0; i < infoHeaderPtr_->biHeight; ++i)
			{
				for (int j = 0; j < linelength; ++j)
				{
					ifs.read((char*)&pixVal, sizeof(uint8_t));
					imgData.push_back(pixVal);
				}
				for (int k = 0; k < offset; k++)
				{
					ifs.read((char*)&pixVal, sizeof(uint8_t));
				}
			}
			imgLoaded_ = true;
			return true;
		}
		else {
			imgLoaded_ = false;
			return false;
		}
		ifs.close();
	}

	bool jBitMap::SaveImage(const char* filePath) {
		std::ofstream ofs;
		ofs.open(filePath, std::ios::out | std::ios::binary);
		if (!ofs) {
			return false;
		}

		ofs.write((char*)fileHeaderPtr_.get(), sizeof(jBitMapStruct::jBitMapFileHeader));
		ofs.write((char*)infoHeaderPtr_.get(), sizeof(jBitMapStruct::jBitMapInfoHeader));

		int channels = 0;
		if (infoHeaderPtr_->biBitCount == 8)
		{
			channels = 1;
			ofs.write((char*)rgbMapPtr_.get() , sizeof(jBitMapStruct::jRGBMap) * rgbMapSize);
		}
		else if (infoHeaderPtr_->biBitCount == 24)
		{
			channels = 3;
		}
		else if (infoHeaderPtr_->biBitCount == 32)
		{
			channels = 4;
		}
		int offset = 0;
		int linelength = infoHeaderPtr_->biWidth * channels;
		offset = (channels * infoHeaderPtr_->biWidth) % 4;
		if (offset > 0)
		{
			offset = 4 - offset;
		}
		uint8_t pixVal;
		auto iter = imgData.begin();
		for (int i = 0; i < infoHeaderPtr_->biHeight; i++)
		{
			for (int j = 0; j < linelength; j++)
			{
				pixVal = *iter;
				ofs.write((char*)&pixVal, sizeof(uint8_t));
				iter += 1;
			}
			pixVal = 0;
			for (int k = 0; k < offset; k++)
			{
				ofs.write((char*)pixVal, sizeof(uint8_t));
			}
		}
		ofs.close();
		return true;
	}

}



