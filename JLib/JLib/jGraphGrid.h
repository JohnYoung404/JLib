#pragma once
#include <tuple>
#include "jGraph.h"
#include "jGrid.h"
#include "jVector.h"

namespace jGame
{

using jGridPos = std::tuple<int, int>;

template<typename Type>
class jGraphGrid : public class jGrid<Type>
{
public:
	bool legal_pos();

};


}