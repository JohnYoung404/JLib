#pragma once
#include "jTestBase.h"

namespace jGame {

template<typename Type>
class jGrid {
public:
	jGrid() = delete;
	jGrid(size_t row, size_t col)
		:_COL(col), _ROW(row)
	{
		_gridPtr = std::make_unique<ElemType[]>(col * row);
	}
	typedef Type ElemType;

	const size_t ROW() const { return _ROW; }
	const size_t ROW() { return _ROW; }
	const size_t COL() const { return _COL; }
	const size_t COL() { return _COL; }

	Type& at(size_t row, size_t col) { 
#ifdef _DEBUG
		BOOST_ASSERT(row < _ROW && col < _COL);
#endif
		return _gridPtr.get()[col * _ROW + row];
	}
	const Type& at(size_t row, size_t col) const { 
#ifdef _DEBUG
		BOOST_ASSERT(row < _ROW && col < _COL);
#endif
		return _gridPtr.get()[col * _ROW + row]; 
	}

	void fill(const Type &val)
	{
		std::for_each(_gridPtr.get(), _gridPtr.get() + _ROW * _COL, [&val] (auto &origVal) { origVal = val; });
	}

private:
	size_t _COL;
	size_t _ROW;
	std::unique_ptr<ElemType[]> _gridPtr;
};

template<typename T>
std::ostream& operator << (std::ostream &output, const jGrid<T> &grid)
{
	for (size_t i = 0; i < grid.COL(); ++i)
	{
		for (size_t j = 0; j < grid.ROW(); ++j)
		{
			output << grid.at(j, i) << " ";
		}
		output << "\n";
	}
	return output;
}

}

namespace jLib {
	class jGridTest final : public jITestable {
	public:
		virtual void test() override {
			using namespace jGame;
			jITestable::test();
			jGrid<int> intGrid(3, 5);
			intGrid.fill(2);
			std::cout << intGrid;
		}
	};
}