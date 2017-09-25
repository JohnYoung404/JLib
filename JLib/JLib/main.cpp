#include <iostream>
#include <vector>
#include "jLib.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]

int main() {
    std::vector<float> a;
    a.resize(100);
    float b[100];
    for (int i = 0; i < 100; ++i)
    {
        a[i] = (float)rand()/(i + 1);
        b[i] = a[i];
    }
    float result = 0;
    {
        JLOG();
        for (volatile int i = 0; i < 100000000; ++i)
        {
            sumOfArray<100>(a.begin());
        }
    }
    std::cout << sumOfArray<100>(a.begin()) << std::endl;
    {
        JLOG();
        for (volatile int i = 0; i < 100000000; ++i)
        {
            result = 0;
            for (int j = 0; j < 100; ++j)
            {
                result = result + a[j];
            }
        }
    }
    //std::cout << result << std::endl;
    getchar();
}

