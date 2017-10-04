#pragma once
#include "jVector.h"

namespace jGraphic {

	class jScreenPoint {

	private:
		jColor pointcolor_;
		jPoint2D<int> point_;
        float depth_;
	};
}