#include <iostream>
#include <vector>
#include "jImage.h"
#include "jLine2D.h"
#include "jCircle.h"
#include "jMath.h"
#include "jIntString.h"
#include "jBitInt.h"
#include "jHeap.h"
#include "jSort.h"
#include "jSudoku.h"
#include "jHash.h"
#include "jAVLTree.h"
#include "jGraph.h"
#include "jDebug.h"
#include "jStringUtil.h"
#include "jRange.h"
#include "jTestManager.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]


int main() {
	{
		//using namespace jGraphic;
		//jMat_base<4, float> a = jMat_base<4, float>::Zero();
		//jMat_4<float> t = {
		//	1, 2, 3, 4,
		//	1, 1, 0, 2,
		//	3, 0, 9, 6,
		//	1, 2, 3, 7
		//};
		//std::cout << inverse(t) * a;
		//jCamera c;
		//std::cout << c.EyePos() << c.FowardVec();
		//jBitMap m;
        //m.CreateEmpty(1920, 1080);
		//
		//for (int i = 0; i < 1920; ++i)
		//{
		//	for (int j = 0; j < 1080; ++j) {
		//		float hori_off = (float)i / 1920;
		//		float vert_off = (float)j / 1080;
		//		float val = jPerlinNoise::stb_perlin_ridge_noise3(hori_off, vert_off, 0.619f, 2.0f, 0.92f, 0.874f, 6, 0, 0, 0);
		//		m.RefOfPos(i, j, 0) = 255;
		//		m.RefOfPos(i, j, 1) = 255 * val < 255 ? 255* val : 255;
		//		m.RefOfPos(i, j, 2) = 255 * val < 255 ? 255* val : 255;
		//		m.RefOfPos(i, j, 3) = 255;
		//	}
		//}
		//
        //jCanvas theCanvas = jCanvas(m);
        //jLine2D theLine  = jLine2D(jPoint2D{ 0.0f, 0.0f},    jPoint2D{450.0f, 450.0f}, jColor::Black());
        //jLine2D theLine2 = jLine2D(jPoint2D{ 0.0f, 450.0f }, jPoint2D{ 450.0f, 0.0f }, jColor::Red());
        //jLine2D theLine3 = jLine2D(jPoint2D{ 0.0f, 200.0f }, jPoint2D{ 450.0f, 0.0f }, jColor::Blue());
        //jLine2D theLine4 = jLine2D(jPoint2D{ 0.0f, 450.0f }, jPoint2D{ 200.0f, 0.0f }, jColor::Green());
        //jCircle theCircle = jCircle(jPoint2D{200, 200}, jColor::Red(), 150);
        //theLine.drawOn(theCanvas);
        //theLine2.drawOn(theCanvas);
        //theLine4.drawOn(theCanvas);
        //theLine3.drawOn(theCanvas);
        //theCircle.drawOn(theCanvas);
		//m.SaveImage("C:\\Users\\Administrator\\Desktop\\test\\test.bmp");
        //std::cout << "done";
		//std::string s;

		//jLib::jIntString jis("1011110100", 10);
		//jLib::jBigInt k = "464132132164163132135464121";
		//jLib::jBigInt T = "1313463131536461";
		//std::cout << (k / T);
		//int arr[] = { 1, 2, 3, 4 , 2, 3, 4 , 6, 7, 8};
		//jLib::putMaxKValueInFront(arr, 5);
		//jLib::jSort::countingsort(arr);

		//std::string s = "Helllo, world.";
		//auto l = jLib::jStringUtil::split(s, "ll");

		jLib::jTestManager::instance().doAllTest();

		//jLib::jTestManager::instance().addTest(std::shared_ptr<jLib::jITestable>(new jLib::jRangeTest()));
	}
	JCheckMemory();
    getchar();
    return 0;
}