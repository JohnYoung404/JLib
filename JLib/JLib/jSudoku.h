#pragma once
#include <ctime>
#include <iostream>
#include <set>


namespace jLib {
	class jSudoku {
	public:
		unsigned char sudokuList[10][10];
		jSudoku() {
			srand((unsigned int)time(NULL));
			regenerate();
		}
		void regenerate();
	private:
		std::set<unsigned char> getValidValues(size_t posX, size_t posY);
		void processPos(int posX, int posY);
		bool done;
	};

	void jSudoku::regenerate() {
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j)
			{
				sudokuList[i][j] = 0;
			}
		done = false;
		processPos(1, 1);
	}

	void jSudoku::processPos(int posX, int posY) {
		std::set<unsigned char> validlist = getValidValues(posX, posY);
		while (!done)
		{
			int sz = validlist.size();
			if (sz == 0)
			{
				sudokuList[posX][posY] = 0;
				return;
			}
			std::set<unsigned char>::iterator itr = validlist.begin();
			int randVal = rand() % sz;
			for (int i = 0; i < randVal; ++i)
			{
				++itr;
			}
			unsigned char val = *itr;
			sudokuList[posX][posY] = val;
			validlist.erase(val);
			if (posX == 9 && posY == 9)
			{
				done = true;
				return;
			}
			int nextX = posX + 1;
			int nextY = posY;
			if (nextX > 9)
			{
				nextX = 1;
				nextY = nextY + 1;
			}
			processPos(nextX, nextY);
		}
		return;
	}

	std::set<unsigned char> jSudoku::getValidValues(size_t posX, size_t posY) {
		std::set<unsigned char> ret;
		for (unsigned char i = 1; i < 10; ++i)
		{
			ret.insert(i);
		}
		for (size_t i = 1; i < 10; ++i)
		{
			if (sudokuList[i][posY] != 0)
			{
				ret.erase(sudokuList[i][posY]);
			}
			if (sudokuList[posX][i] != 0)
			{
				ret.erase(sudokuList[posX][i]);
			}
		}
		int _x = (posX - 1) / 3 * 3, _y = (posY - 1) / 3 * 3;
		for (int i = _x + 1; i < _x + 4; ++i)
			for (int j = _y + 1; j < _y + 4; ++j)
			{
				if (sudokuList[i][j] != 0)
				{
					ret.erase(sudokuList[i][j]);
				}
			}
		return ret;
	}

}

std::ostream& operator << (std::ostream &output, jLib::jSudoku s) {
	for (size_t i = 1; i < 10; ++i)
	{
		for (size_t j = 1; j < 10; ++j)
		{
			output << static_cast<int>(s.sudokuList[i][j]) << " ";
		}
		output << std::endl;
	}
	return output;
}