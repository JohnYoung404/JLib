#pragma once
#include <tuple>
#include "jGraph.h"
#include "jGrid.h"
#include "jVector.h"

namespace jGame
{

using jPosNode = std::tuple<int, int>;

class jPositionGraph : public jGraphLib::jGraph<jPosNode>
{
public:
    jPositionGraph(int initWidth, int initHeight) : _width(initWidth), _height(initHeight) { }
    std::vector<jPosNode> neibours(jPosNode InputNode) override
    {

    }
private:
    int _width, _height;
};


}