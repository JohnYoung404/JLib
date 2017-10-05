#include <iostream>
#include <vector>
#include "jLib.h"
#include "jScreenPoint.h"
#include "jImage.h"
#include "jLine2D.h"
#include "jCircle.h"

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
		jBitMap m;
        m.CreateEmpty(600, 600);
        jCanvas theCanvas = jCanvas(m);
        jLine2D theLine  = jLine2D(jPoint2D{ 0.0f, 0.0f},    jPoint2D{450.0f, 450.0f}, jColor::Black());
        jLine2D theLine2 = jLine2D(jPoint2D{ 0.0f, 450.0f }, jPoint2D{ 450.0f, 0.0f }, jColor::Red());
        jLine2D theLine3 = jLine2D(jPoint2D{ 0.0f, 200.0f }, jPoint2D{ 450.0f, 0.0f }, jColor::Blue());
        jLine2D theLine4 = jLine2D(jPoint2D{ 0.0f, 450.0f }, jPoint2D{ 200.0f, 0.0f }, jColor::Green());
        jCircle theCircle = jCircle(jPoint2D{200, 200}, jColor::Red(), 150);
        theLine.drawOn(theCanvas);
        theLine2.drawOn(theCanvas);
        theLine4.drawOn(theCanvas);
        theLine3.drawOn(theCanvas);
        theCircle.drawOn(theCanvas);
		m.SaveImage("C:\\Users\\Administrator\\Desktop\\test\\test.bmp");
        std::cout << "done";
	}
	JCheckMemory();
    getchar();
}