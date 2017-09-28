#include <iostream>
#include <vector>
#include "jLib.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]

int main() {

	jVec_3<float> jv = { 0, 1, 0};
	jVec_3<float> jv2 = { 0, 1, 1};
	std::cout << theta(jv, jv2) << jv[2];
    getchar();
}

