#include "jColor.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jGraphic)
    
jColor ColorLerp(jColor from, jColor to, float interpolator) 
{
	float ret_a = from.a_ + interpolator * (to.a_ - from.a_);
	float ret_r = from.r_ + interpolator * (to.r_ - from.r_);
	float ret_g = from.g_ + interpolator * (to.g_ - from.g_);
	float ret_b = from.b_ + interpolator * (to.b_ - from.b_);
	jColor ret = jColor((jColor::Byte)ret_a, (jColor::Byte)ret_r, (jColor::Byte)ret_g, (jColor::Byte)ret_b);
	return ret;
}

constexpr bool operator==(jColor lhs, jColor rhs)
{
    return (lhs.a_ == rhs.a_) && (lhs.r_ == rhs.r_) && (lhs.g_ == rhs.g_) && (lhs.b_ == rhs.b_);
}

NAME_SPACE_END
NAME_SPACE_END