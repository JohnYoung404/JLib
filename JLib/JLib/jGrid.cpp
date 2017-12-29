#include "jGrid.h"

namespace jGame
{

template<typename T>
std::ostream& operator << (std::ostream &output, const jGrid<T> &grid)
{
	for (size_t i = 0; i < grid.ROW(); ++i)
	{
		for (size_t j = 0; j < grid.COL(); ++j)
		{
			output << grid.at(j, i) << " ";
		}
		output << "\n";
	}
	return output;
}

}