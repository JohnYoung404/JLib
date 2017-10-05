#pragma once
#include "jVector.h"

namespace jGraphic {

	class jScreenPoint {

	private:
		jColor pointcolor_;
		jVector_base<2, int> point_;
        float depth_;
	};
}