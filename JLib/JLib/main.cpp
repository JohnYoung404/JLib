#include <iostream>
#include <vector>
#include "jLib.h"
#include "jScreenPoint.h"
#include "jImage.h"
#include "jLine.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]

int main() {
	{
		using namespace jGraphic;
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
		jGraphic::jBitMap m;
		m.LoadImage("test.bmp");
        jLine theLine = jLine(jPoint3D{ 0.0f, 0.0f, 0.0f }, jPoint3D{450.0f, 450.0f, 100.0f}, jColor::Black());
        jLine theLine2 = jLine(jPoint3D{ 0.0f, 450.0f, 0.0f }, jPoint3D{ 450.0f, 0.0f, 100.0f }, jColor::Black());
        jLine theLine3 = jLine(jPoint3D{ 0.0f, 200.0f, 0.0f }, jPoint3D{ 450.0f, 0.0f, 100.0f }, jColor::Black());
        jLine theLine4 = jLine(jPoint3D{ 0.0f, 450.0f, 0.0f }, jPoint3D{ 200.0f, 0.0f, 100.0f }, jColor::Black());
        m.CreateEmpty(600, 600);
        for (int i = 0; i < m.Width(); ++i)
        {
            for (int j = 0; j < m.Height(); ++j)
            {
                m.RefOfPos(i, j, 0) = 255; //b
                m.RefOfPos(i, j, 1) = 255; //g
                m.RefOfPos(i, j, 2) = 255; //r
                m.RefOfPos(i, j, 3) = 255; //a
            }
        }
        jCanvas theCanvas = jCanvas(m);
        theLine.drawOn(theCanvas);
        theLine2.drawOn(theCanvas);
        theLine4.drawOn(theCanvas);
        theLine3.drawOn(theCanvas);
		m.SaveImage("C:\\Users\\Administrator\\Desktop\\test\\test.bmp");
        std::cout << "done";
	}
	JCheckMemory();
    getchar();
}