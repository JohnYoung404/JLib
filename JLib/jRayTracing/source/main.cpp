// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/17/2018]
// Description : program entrance.

#include <iostream>
#include "jVec3f_SIMD.h"

int main(int argc, char** argv)
{
    using namespace jRayTracing;
    J_ALIGN(16) jVec3f_SIMD v_a = jVec3f_SIMD{ 1, 2, 3 };
    J_ALIGN(16) jVec3f_SIMD v_b = jVec3f_SIMD{ 3.1f, 2.3f, 1.9f };
    v_a.Reciprocal_org();
    v_b.cross_org(v_a);
    auto t = v_a.normalize_cpy();
    v_a.normalize_org();
    getchar();
    return 0;
}