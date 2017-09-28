#pragma once


namespace jGraphic {

	typedef unsigned char Byte;

	class jColor
	{
	public:
		jColor(Byte a = 0, Byte r = 0, Byte g = 0, Byte b = 0) : a_(a), r_(r), g_(g), b_(b){}

		inline static const jColor Black(){
			return jColor(255, 0, 0, 0);
		}
		inline static const jColor White() {
			return jColor(255, 255, 255, 255);
		}
		inline static const jColor Red() {
			return jColor(255, 255, 0, 0);
		}
		inline static const jColor Green() {
			return jColor(255, 0, 255, 0);
		}
		inline static const jColor Blue() {
			return jColor(255, 0, 255, 255);
		}

		friend bool operator==(jColor lhs, jColor rhs);

		friend jColor ColorLerp(jColor from, jColor to, float interpolator);
	private:
		Byte a_, r_, g_, b_;
	};

	jColor ColorLerp(jColor from, jColor to, float interpolator) {
		float ret_a = from.a_ + interpolator * (to.a_ - from.a_);
		float ret_r = from.r_ + interpolator * (to.r_ - from.r_);
		float ret_g = from.g_ + interpolator * (to.g_ - from.g_);
		float ret_b = from.b_ + interpolator * (to.b_ - from.b_);
		jColor ret = jColor((Byte)ret_a, (Byte)ret_r, (Byte)ret_g, (Byte)ret_b);
		return ret;
	}

	bool operator==(jColor lhs, jColor rhs) {
		return (lhs.a_ == rhs.a_) && (lhs.r_ == rhs.r_) && (lhs.g_ == rhs.g_) && (lhs.b_ == rhs.b_);
	}
}
