#pragma once
#include <memory>
#include <vector>
#include "jSceneObj.h"

namespace jLib{
namespace jGraphic{

class jScene
{
private:
    std::vector< std::shared_ptr<jSceneObj> > _sceneObjs;
};

}}