#pragma once
#include <limits.h>

namespace jLib {

	inline bool intAddOK(int x, int y) {
		int sum = x + y;
		bool neg_over = x < 0 && y < 0 && sum >= 0;
		bool pos_over = x > 0 && y > 0 && sum < 0;
		return !neg_over && !pos_over;
	}

	inline bool intSubOK(int x, int y) {
		if (y == INT_MIN)
		{
			if (x > 0)	return false; else return true; //When y == INT_MIN, -y overflow and remains INT_MIN! 
		}
		else {
			return intAddOK(x, -y);
		}
	}

	inline bool intMultOK(int x, int y) {
		int p = x*y;
		return !x || p / x == y;	
	}

	inline bool unsignedIntAddOK(unsigned x, unsigned y) {
		unsigned sum = x + y;
		return sum >= x;
	}
}