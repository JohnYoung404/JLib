#include <iostream>
#include "jLib.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]

int main() {

    jMat_4<double> j = {
        1, 2 ,3, 4,
        2, 2, 3, 4,
        3, 2, 3, 4,
        4, 2, 3, 4
    };

    jMat_4<double> k = {
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4,
        1, 2, 3, 4
    };

    std::cout << jMat_4<double>::Zero() * j + k * jMat_4<double>::I();

    getchar();
}

