#pragma once
#include "jGrid.h"
#include "jVector.h"

namespace jGame
{

using jGridPos = jVector_base<2, int>;

class __quadruple_accessive_cell
{
    __quadruple_accessive_cell *left;
    __quadruple_accessive_cell *right;
    __quadruple_accessive_cell *top;
    __quadruple_accessive_cell *bottom;
};

class __octuple_accessive_cell
{

};

template<typename Type>
class jGraphGrid : public class jGrid<Type>
{

};

using jWeightedGrid = jGraphGrid<__quadruple_accessive_cell>;

}