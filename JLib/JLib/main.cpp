#include <iostream>
#include <vector>
#include "jLib.h"
#include "jScreenPoint.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]

int main() {
	{
		jGraphic::jMat_4<float> jm = {
			1, 2,  3 , 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16
		};
		std::cout << jGraphic::jMat_4<float>::Identity() * jGraphic::jMat_4<float>::Identity();
	}
    getchar();
}

