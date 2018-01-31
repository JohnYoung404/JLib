#pragma once
#include <memory>
#include "jSceneObj.h"

namespace jLib{
namespace jGraphic{

class jScene
{
private:
    std::shared_ptr<jSceneObj> _sceneObjs;
};

}}