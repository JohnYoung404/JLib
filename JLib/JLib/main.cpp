#include <iostream>
#include <vector>
#include "jLib.h"
#include "jScreenPoint.h"
#include "jImage.h"

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
		jGraphic::jBitMap m;
		m.LoadImage("test2.bmp");
		for (int i = 0; i < m.Width(); ++i)
		{
			for (int j = 0; j < m.Height(); ++j)
			{
				m.RefOfPos(i, j, 2) = 255;
			}
		}
		m.SaveImage("C:\\Users\\Administrator\\Desktop\\test\\haha.bmp");
	}
	JCheckMemory();
    getchar();
}