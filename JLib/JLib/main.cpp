#include "jDebug.h"
#include "jTestManager.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]

int main() {
    JCheckMemory();
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
    }
    jLib::jTestManager::instance().doAllTest();
    getchar();
    return 0;
}