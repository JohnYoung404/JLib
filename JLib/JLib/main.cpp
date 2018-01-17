#include "jDebug.h"
#include "jTestManager.h"

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/24/2017]

int main() {
    JCheckMemory();
    jLib::jTestManager::instance().doAllTest();
    getchar();
    return 0;
}