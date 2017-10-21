#pragma once
#include "jTestBase.h"

namespace jLib {
namespace Constable {

	class Point {
	public:
		constexpr Point(float x_val, float y_val) noexcept : x_(x_val), y_(y_val) {}
		constexpr float X() const noexcept { return x_; }
		constexpr float Y() const noexcept { return y_; }

		constexpr static Point Origin() {
			return Point(0, 0);
		}
	private:
		float x_, y_;
	};

	constexpr Point midPoint(const Point& p1, const Point& p2) noexcept {
		return Point(((p1.X() + p2.X()) / 2), ((p1.Y() + p2.Y()) / 2));
	}
}
}

namespace jLib {
	class jConstableTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			constexpr Constable::Point p(1.0f, 2.0f);
			constexpr Constable::Point q(3.0f, 0.0f);
			constexpr auto mid = Constable::midPoint(p, q);
			std::cout << mid.X() << ", " << mid.Y() << "\n";

			constexpr auto orig = Constable::Point::Origin();
			std::cout << orig.X() << ", " << orig.Y() << "\n";	// simply equals:  std::cout << 0 << "," << 0 << "\n";

			Constable::Point non_const_point = Constable::midPoint(p, q);
			std::cout << non_const_point.X() << ", " << non_const_point.Y() << "\n";  //non_const_point is not known until runtime, so will access its x value and y value.
		}
	};
}