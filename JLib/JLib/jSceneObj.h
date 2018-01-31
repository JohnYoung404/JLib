#pragma once
#include "jVector.h"

namespace jLib {
namespace jGraphic {

class jSceneObj
{
public: 
    virtual const jContainer::jVec3f& GetPos() const
    {
        return _pos;
    }
private:
    jContainer::jVec3f _pos;
};

}}