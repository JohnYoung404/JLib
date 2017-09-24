#include <iostream>
#include "jLib.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]

int main() {
    float a[] = { 1.4f, 2.8f, 3.7f, 4.7f, 5.6f, 6.2f, 70.1f, 86.3f, 9.72f, 10.894452f, 11.11f, 12.9461f, 13.5f, 14.14f, 15.15f};
    float result = 0;
    {
        JLOG();
        for (volatile int i = 0; i < 100000000; ++i)
        {
            sumOfArray<15>(a);
        }
    }
    {
        JLOG();
        for (volatile int i = 0; i < 100000000; ++i)
        {
            for (volatile int j = 0; j < 15; ++j)
            {
                result += a[j];
            }
        }
    }
    getchar();
}