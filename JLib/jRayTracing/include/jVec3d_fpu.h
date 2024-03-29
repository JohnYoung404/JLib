#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/17/2018]
// Description : Double-precision vector contains 3 elements.

#include <array>
#include "jCommon.h"

namespace jRayTracing
{

class jVec3d_fpu
{
public:
	std::array<double, 3> _arr;

public:
	constexpr explicit jVec3d_fpu(double InX = 0.0f, double InY = 0.0f, double InZ = 0.0f) : _arr{ InX, InY, InZ } { }
	constexpr jVec3d_fpu(const jVec3d_fpu &rhs) noexcept : _arr(rhs._arr) { }
	constexpr jVec3d_fpu(jVec3d_fpu && rhs) noexcept : _arr(std::move(rhs._arr)) { }
	jVec3d_fpu& operator=(const jVec3d_fpu &rhs) noexcept { _arr = rhs._arr; return *this; }
	jVec3d_fpu& operator=(jVec3d_fpu &&rhs) noexcept { _arr = std::move(rhs._arr); return *this; }

public:
	J_FORCE_INLINE static constexpr jVec3d_fpu zero() { return jVec3d_fpu(); }

public:
	J_FORCE_INLINE double& operator[](int ComponentIndex) { return _arr[ComponentIndex]; }
	J_FORCE_INLINE double  operator[](int ComponentIndex) const { return _arr[ComponentIndex]; }
	J_FORCE_INLINE double x() const { return _arr[0]; }
	J_FORCE_INLINE double y() const { return _arr[1]; }
	J_FORCE_INLINE double z() const { return _arr[2]; }
	J_FORCE_INLINE double& x() { return _arr[0]; }
	J_FORCE_INLINE double& y() { return _arr[1]; }
	J_FORCE_INLINE double& z() { return _arr[2]; }

public:
	jVec3d_fpu operator-() const;
	jVec3d_fpu& neg_org();

	jVec3d_fpu Reciprocal_cpy() const;
	jVec3d_fpu& Reciprocal_org();

	jVec3d_fpu  operator+ (const jVec3d_fpu& V) const;
	jVec3d_fpu& add_org(const jVec3d_fpu& V);

	jVec3d_fpu  operator- (const jVec3d_fpu& V) const;
	jVec3d_fpu& sub_org(const jVec3d_fpu& V);

	jVec3d_fpu  operator*(double Scale) const;
	jVec3d_fpu& scalar_mul_org(double Scale);

	jVec3d_fpu  operator/(double Scale) const;
	jVec3d_fpu& scalar_div_org(double Scale);

	jVec3d_fpu  operator/(const jVec3d_fpu& V) const;
	jVec3d_fpu& div_org(const jVec3d_fpu& V);

	jVec3d_fpu  cwise_mult_cpy(const jVec3d_fpu& V) const;
	jVec3d_fpu& cwise_mult_org(const jVec3d_fpu& V);

	jVec3d_fpu  cross_cpy(const jVec3d_fpu& V) const;
	jVec3d_fpu& cross_org(const jVec3d_fpu& V);

	jVec3d_fpu  normalize_cpy() const;
	jVec3d_fpu& normalize_org();

	double dot(const jVec3d_fpu& V) const;

	friend J_FORCE_INLINE jVec3d_fpu operator*(double Scale, const jVec3d_fpu& V)
	{
		return V.operator*(Scale);
	}
};

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::operator-() const
{
	return jVec3d_fpu{ -x(), -y(), -z() };
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::neg_org()
{
	x() = -x(); y() = -y(); z() = -z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::Reciprocal_cpy() const
{
	return jVec3d_fpu{ 1.f / x(), 1.f / y(), 1.f / z() };
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::Reciprocal_org()
{
	x() = 1.f / x(); y() = 1.f / y(); z() = 1.f / z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::operator+ (const jVec3d_fpu& V) const
{
	return jVec3d_fpu{ x() + V.x(), y() + V.y(), z() + V.z() };
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::add_org(const jVec3d_fpu& V)
{
	x() += V.x(); y() += V.y(); z() += V.z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::operator- (const jVec3d_fpu& V) const
{
	return jVec3d_fpu{ x() - V.x(), y() - V.y(), z() - V.z() };
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::sub_org(const jVec3d_fpu& V)
{
	x() -= V.x(); y() -= V.y(); z() -= V.z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::operator* (double Scale) const
{
	return jVec3d_fpu{ x() * Scale, y() * Scale, z() * Scale };
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::scalar_mul_org(double Scale)
{
	x() *= Scale; y() *= Scale; z() *= Scale;
	return *this;
}

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::operator/ (double Scale) const
{
	return jVec3d_fpu{ x() / Scale, y() / Scale, z() / Scale };
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::scalar_div_org(double Scale)
{
	x() /= Scale; y() /= Scale; z() /= Scale;
	return *this;
}

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::operator/ (const jVec3d_fpu& V) const
{
	return jVec3d_fpu{ x() / V.x(), y() / V.y(), z() / V.z() };
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::div_org(const jVec3d_fpu& V)
{
	x() /= V.x(); y() /= V.y(); z() /= V.z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::cwise_mult_cpy(const jVec3d_fpu& V) const
{
	return jVec3d_fpu{ x() * V.x(), y() * V.y(), z() * V.z() };
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::cwise_mult_org(const jVec3d_fpu& V)
{
	x() *= V.x(); y() *= V.y(); z() *= V.z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::cross_cpy(const jVec3d_fpu& V) const
{
	return jVec3d_fpu{ y() * V.z() - z() * V.y(), z() * V.x() - x() * V.z(), x() * V.y() - y() * V.x() };
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::cross_org(const jVec3d_fpu& V)
{
	double tmp_X = y() * V.z() - z() * V.y();
	double tmp_Y = z() * V.x() - x() * V.z();
	double tmp_Z = x() * V.y() - y() * V.x();
	x() = tmp_X, y() = tmp_Y, z() = tmp_Z;
	return *this;
}

J_FORCE_INLINE jVec3d_fpu jVec3d_fpu::normalize_cpy() const
{
	return *this / std::sqrt(x() * x() + y() * y() + z() * z());
}

J_FORCE_INLINE jVec3d_fpu& jVec3d_fpu::normalize_org()
{
	return this->scalar_div_org(std::sqrt(x() * x() + y() * y() + z() * z()));
}

J_FORCE_INLINE double jVec3d_fpu::dot(const jVec3d_fpu& V) const
{
	return x() * V.x() + y() * V.y() + z() * V.z();
}

}