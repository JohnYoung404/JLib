#include <fstream>
#include <cstdio>
#include <iosfwd>
#include <experimental/filesystem>
#include "jBitMap.h"

namespace jLib
{

namespace jMedia
{

bool jBitMap::LoadImage(const char* filePath) 
{
	std::ifstream ifs;
	ifs.open(filePath, std::ios::in | std::ios::binary);
	if (!ifs) {
		imgLoaded_ = false;
		return false;
	}

	fileHeaderPtr_ = std::make_shared<jBitMapStruct::jBitMapFileHeader>();
	infoHeaderPtr_ = std::make_shared<jBitMapStruct::jBitMapInfoHeader>();
	rgbMapPtr_ = std::make_shared<jBitMapStruct::jRGBMap>();
	imgData.clear();

	ifs.read((char*)fileHeaderPtr_.get(), sizeof(jBitMapStruct::jBitMapFileHeader));

	if (fileHeaderPtr_->bfType == 0x4D42) {     //0x4D42 is ascii code for "BM".
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

bool jBitMap::SaveImage(const char* filePath) 
{
	if (!imgLoaded_) {
		return false;
	}
	std::experimental::filesystem::path p = filePath;
	auto parentPath = p.parent_path();
	if (!std::experimental::filesystem::exists(parentPath))
	{
		std::experimental::filesystem::create_directories(parentPath);
	}
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
		ofs.write((char*)rgbMapPtr_.get(), sizeof(jBitMapStruct::jRGBMap) * rgbMapSize);
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

void jBitMap::CreateEmpty(int width, int height) 
{
	ClearImage();
	fileHeaderPtr_ = std::make_shared<jBitMapStruct::jBitMapFileHeader>();
	infoHeaderPtr_ = std::make_shared<jBitMapStruct::jBitMapInfoHeader>();
	fileHeaderPtr_->bfType = 0x4D42;
	fileHeaderPtr_->bfReserved1 = fileHeaderPtr_->bfReserved2 = 0;
	fileHeaderPtr_->bfOffBits = 54;
	fileHeaderPtr_->bfSize = 54 + 4 * width * height;

	infoHeaderPtr_->biSize = 40;
	infoHeaderPtr_->biBitCount = 32;
	infoHeaderPtr_->biWidth = width;
	infoHeaderPtr_->biHeight = height;
	infoHeaderPtr_->biPlanes = 1;
	infoHeaderPtr_->biClrImportant = 0;
	infoHeaderPtr_->biClrUsed = 0;
	infoHeaderPtr_->biCompression = 0;
	infoHeaderPtr_->biXPelsPerMeter = 88;
	infoHeaderPtr_->biYPelsPerMeter = 90;
	infoHeaderPtr_->biSizeImage = (width * 32 + 31) / 32 * 4 * height;

	imgData.resize(4 * width * height, 255);
	imgLoaded_ = true;
}

void jBitMap::ClearImage() 
{
	fileHeaderPtr_.reset();
	infoHeaderPtr_.reset();
	rgbMapPtr_.reset();
	imgData.clear();
	imgLoaded_ = false;
}

}

}