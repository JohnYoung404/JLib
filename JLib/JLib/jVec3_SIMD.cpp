#include <iostream>
#include "jVec3_SIMD.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jContainer)

extern std::ostream& operator<< (std::ostream& os, const jVec3f_SIMD &outVec) {
    for (int i = 0; i < 3; ++i)
    {
        std::cout << outVec[i] << " ";
    }
    std::cout << std::endl;
    return os;
}

extern std::ostream& operator<< (std::ostream& os, const jVec3d_SIMD &outVec) {
    for (int i = 0; i < 3; ++i)
    {
        std::cout << outVec[i] << " ";
    }
    std::cout << std::endl;
    return os;
}

NAME_SPACE_END
NAME_SPACE_END