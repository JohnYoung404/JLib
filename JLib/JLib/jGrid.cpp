#include "jGrid.h"
#include "jTestBase.h"

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
class jGrid<Type>:: row_iterator : public std::iterator<std::random_access_iterator_tag, Type>
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