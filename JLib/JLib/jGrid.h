#pragma once
#include <iterator>
#include <algorithm>
#include <memory>
#include <boost/assert.hpp>

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

	inline const size_t ROW() const { return _ROW; }
	inline const size_t COL() const { return _COL; }

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

namespace jGame
{
	template <typename Type>
	class jGrid<Type>::column_iterator : public std::iterator<std::random_access_iterator_tag, Type>
	{
	private:
		Type *_pos;
		size_t _col;
	public:
		explicit column_iterator(Type *Inpos, size_t Incol) : _pos(Inpos), _col(Incol) {}
		column_iterator& operator++() { _pos += _col; return *this; }
		column_iterator& operator--() { _pos -= _col; return *this; }
		column_iterator operator++(int) const { auto ret = *this; return ++ret; }
		column_iterator operator--(int) const { auto ret = *this; return --ret; }
		ptrdiff_t operator-(column_iterator rhs) const
		{
			return _pos - rhs._pos;
		}
		column_iterator operator+(ptrdiff_t _offset) const
		{
			auto ret = *this;
			ret._pos += _offset * _COL;
			return  ret;
		}
		column_iterator operator-(ptrdiff_t _offset) const
		{
			auto ret = *this;
			ret._pos -= _offset * _COL;
			return  ret;
		}
		bool operator==(column_iterator other) const { return _pos == other._pos; }
		bool operator!=(column_iterator other) const { return _pos != other._pos; }
		bool operator<(column_iterator other) const { return _pos < other._pos; }
		reference operator *() const { return *_pos; }
	};

	template <typename Type>
	class jGrid<Type>::row_iterator : public std::iterator<std::random_access_iterator_tag, Type>
	{
	private:
		Type *_pos;
		size_t _row;
	public:
		explicit row_iterator(Type *Inpos, size_t Inrow) : _pos(Inpos), _row(Inrow) {}
		row_iterator& operator++() { _pos += 1; return *this; }
		row_iterator& operator--() { _pos -= 1; return *this; }
		row_iterator operator++(int) { auto ret = *this; return ++ret; }
		row_iterator operator--(int) { auto ret = *this; return --ret; }
		ptrdiff_t operator-(row_iterator rhs)
		{
			return _pos - rhs._pos;
		}
		row_iterator operator+(ptrdiff_t _offset)
		{
			auto ret = *this;
			ret._pos += _offset;
			return  ret;
		}
		row_iterator operator-(ptrdiff_t _offset)
		{
			auto ret = *this;
			ret._pos -= _offset;
			return  ret;
		}
		bool operator==(row_iterator other) const { return _pos == other._pos; }
		bool operator!=(row_iterator other) const { return _pos != other._pos; }
		bool operator<(row_iterator other) const { return _pos < other._pos; }
		reference operator *() const { return *_pos; }
	};

	template <typename Type>
	class jGrid<Type>::col_itr_pair
	{
	public:
		explicit col_itr_pair(column_iterator InBeg, column_iterator InEnd) : _beg(InBeg), _end(InEnd) {}
		column_iterator begin() const { return _beg; }
		column_iterator end() const { return _end; }
	private:
		column_iterator _beg, _end;
	};

	template <typename Type>
	class jGrid<Type>::row_itr_pair
	{
	public:
		explicit row_itr_pair(row_iterator InBeg, row_iterator InEnd) : _beg(InBeg), _end(InEnd) {}
		row_iterator begin() const { return _beg; }
		row_iterator end() const { return _end; }
	private:
		row_iterator _beg, _end;
	};
}

#include "jTestBase.h"

namespace jLib {
	class jGridTest final : public jITestable {
	public:
		virtual void test() override {
			using namespace jGame;
			jITestable::test();
			jGrid<int> intGrid(3, 5);
			intGrid.fill(2);
			intGrid.for_each([](auto &val) {val += 1; });
			for (auto &val : intGrid.col_at(1))
			{
				val += 1;
			}
			for (auto &val : intGrid.row_at(2))
			{
				val += 1;
			}
			std::sort(intGrid.row_at(4).begin(), intGrid.row_at(4).end(), std::less<int>());
			std::cout << intGrid;
		}
	};
}