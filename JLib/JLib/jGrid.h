#pragma once
#include <iterator>
#include <algorithm>
#include <memory>
#include "boost/assert.hpp"


namespace jGame {

template<typename Type>
class jGrid {
public:
	jGrid() = delete;
	jGrid(size_t col, size_t row)
		:_COL(col), _ROW(row)
	{
		_gridPtr = std::make_unique<ElemType[]>(col * row);
	}
	typedef Type ElemType;

	const size_t ROW() const { return _ROW; }
	const size_t COL() const { return _COL; }

	class column_iterator;
	class row_iterator;
	class col_itr_pair;
	class row_itr_pair;

	//未实现const_iterator 和 const 版本的col_at/row_at
	col_itr_pair col_at(int col)
	{
#ifdef _DEBUG
		BOOST_ASSERT(col < _COL && col >= 0);
#endif
		column_iterator _beg(_gridPtr.get() + col, _COL);
		column_iterator _end(_gridPtr.get() + col + _COL * _ROW, _COL);
		return col_itr_pair(_beg, _end);
	}

	row_itr_pair row_at(int row)
	{
#ifdef _DEBUG
		BOOST_ASSERT(row < _ROW && row >= 0);
#endif
		row_iterator _beg(_gridPtr.get() + row * _COL, _ROW);
		row_iterator _end(_gridPtr.get() + row * _COL + _COL, _ROW);
		return row_itr_pair(_beg, _end);
	}

	Type& at(size_t col, size_t row) { 
#ifdef _DEBUG
		BOOST_ASSERT(row < _ROW && col < _COL && row >=0 && col >= 0);
#endif
		return _gridPtr.get()[row * _COL + col];
	}

	const Type& at(size_t col, size_t row) const { 
#ifdef _DEBUG
		BOOST_ASSERT(row < _ROW && col < _COL && row >= 0 && col >= 0);
#endif
		return _gridPtr.get()[row * _COL + col];
	}


	void fill(const Type &val)
	{
		std::for_each(_gridPtr.get(), _gridPtr.get() + _ROW * _COL, [&val] (auto &origVal) { origVal = val; });
	}

	void reset()
	{
		fill(Type());
	}

	template<typename Func>
	void for_each(Func &f)
	{
		std::for_each(_gridPtr.get(), _gridPtr.get() + _ROW * _COL, [&f](auto &Val) { f(Val); });
	}

	template<typename Func>
	void for_each(Func &f) const
	{
		std::for_each(_gridPtr.get(), _gridPtr.get() + _ROW * _COL, [&f](const auto &Val) { f(Val); });
	}

private:
	size_t _COL;
	size_t _ROW;
	std::unique_ptr<ElemType[] > _gridPtr;
};

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