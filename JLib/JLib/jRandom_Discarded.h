#pragma once
#include <ctime>
#include <string>

//////////////////////////////////////////////////////////////////////////
// Too old, so Discarded, maybe restored later.
//////////////////////////////////////////////////////////////////////////
namespace jLib {
	class jRandom {
	public:
		jRandom() { srand(static_cast<unsigned int>(time(NULL))); }
		inline unsigned int randomUnsignedInt(unsigned int floor, unsigned int ceil);
		inline char randomPrintableChar();
		inline char randomAlphabetChar_lowwercase();
		inline std::string randomPrintableString(std::string::size_type length);
		inline std::string randomAlphabetString_lowwercase(std::string::size_type length);

		template<typename T, int N>
		inline void disruptArray(T(&buf)[N]);

		template<typename T>
		inline T reservoirSampling(T* listHead);         //randomly select an element in a list;

		template<size_t N>
		inline void nUniqueUnsignedInt(unsigned int(&buf)[N], unsigned int floor, unsigned int ceil);
	};

	unsigned int jRandom::randomUnsignedInt(unsigned int floor, unsigned int ceil) {
		unsigned int tmpRand_1 = rand() & 0xfff;
		unsigned int tmpRand_2 = rand() & 0xfff;
		unsigned int tmpRand_3 = rand() & 0xff;
		unsigned int tmpRand = (tmpRand_1 << 20) + (tmpRand_2 << 8) + tmpRand_3;
		unsigned int result = (ceil - floor < 0xffffffff) ? tmpRand % (ceil - floor + 1) + floor : tmpRand;
		return result;
	}

	char jRandom::randomPrintableChar() {
		return static_cast<char>(rand() % 95 + 32);
	}

	char jRandom::randomAlphabetChar_lowwercase() {
		return static_cast<char>(rand() % 26 + 97);
	}

	std::string jRandom::randomPrintableString(std::string::size_type length) {
		std::string ret;
		for (std::string::size_type i = 0; i < length; ++i)
		{
			ret.push_back(randomPrintableChar());
		}
		return ret;
	}

	std::string jRandom::randomAlphabetString_lowwercase(std::string::size_type length) {
		std::string ret;
		for (std::string::size_type i = 0; i < length; ++i)
		{
			ret.push_back(randomAlphabetChar_lowwercase());
		}
		return ret;
	}

	template<size_t N>
	void jRandom::nUniqueUnsignedInt(unsigned int(&buf)[N], unsigned int floor, unsigned int ceil) {
		bool unique;
		unsigned int tmp;
		if (ceil - floor < N - 1) throw std::range_error("Trying to fill a big container using a small range.");
		for (int j = 0; j < N; ++j)
		{
			unique = false;
			while (!unique)
			{
				unique = true;
				tmp = randomUnsignedInt(floor, ceil);
				for (int k = 0; k < j; ++k)
				{
					if (buf[k] == tmp)
					{
						unique = false;
						break;
					}
				}
			}
			buf[j] = tmp;
		}
		return;
	}

	template<typename T, int N>
	void jRandom::disruptArray(T(&buf)[N]) {
		int i, randIndex;
		T tmp;
		for (i = 0; i < N; ++i) {
			randIndex = randomUnsignedInt(0, N - 1);
			tmp = buf[randIndex];
			buf[randIndex] = buf[i];
			buf[i] = tmp;
		}
	}

	template<typename T>
	T jRandom::reservoirSampling(T* listHead) {
		T ret = listHead;
		T* node = listHead;
		int i = 2;
		while (node)
		{
			int j = randomUnsignedInt(0, UINT_MAX) % i;
			if (j == 0)
			{
				ret = node;
			}
			i++;
			node = node->next;				//list node should have a next pointer; 
		}
		return ret;
	}
}