#pragma once
#include <memory>
#include <vector>
#include "jSceneObj.h"
#include "jColor.h"

namespace jLib{
namespace jGraphic{

class jScene
{
    inline const jColor get_ambient() const { return _ambient; }
private:
    std::vector< std::shared_ptr<jSceneObj> > _sceneObjs;
    jColor _ambient;
};

}}