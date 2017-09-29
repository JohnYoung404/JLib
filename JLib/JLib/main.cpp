#include <iostream>
#include <vector>
#include "jLib.h"
#include "jScreenPoint.h"
#include "jMatrix.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]

int main() {
	{
		using namespace jGraphic;
		jMat_base<7, float> jm = jMat_base<7, float>::Identity();
		jMat_base<5, float> t = {
			1, 2, 3, 4, 4,
			1, 1, 0, 2, 3,
			3, 0, 9, 6, 1,
			1, 2, 3, 7, 4,
			2, 3, 4, 5, 5
		};
		std::cout <<  inverse(t) * t;
	}
    getchar();
}