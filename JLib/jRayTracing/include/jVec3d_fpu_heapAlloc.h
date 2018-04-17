#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/17/2018]
// Description : Double-precision vector contains 3 elements, alloc on heap.

#include <array>
#include "jCommon.h"
#include <boost/pool/singleton_pool.hpp>
#include <iostream>
#include <omp.h>

namespace jRayTracing
{

struct pool_tag {};
using spl = boost::singleton_pool<pool_tag, sizeof(double) * 3>;	// as slow as hell, because of lock.

extern thread_local boost::pool<> vecPool;

class jVec3d_fpu_heapAlloc
{
public:
	double * _arr;

public:
	explicit jVec3d_fpu_heapAlloc(double InX = 0.0f, double InY = 0.0f, double InZ = 0.0f)
	{ 
		//_arr = (double*)spl::malloc();
		//_arr = (double*)malloc(3 * sizeof(double));
		_arr = (double*)vecPool.malloc();
		_arr[0] = InX;
		_arr[1] = InY;
		_arr[2] = InZ;
	}
	jVec3d_fpu_heapAlloc(const jVec3d_fpu_heapAlloc &rhs) noexcept
	{
		//_arr = (double*)spl::malloc();
		//_arr = (double*)malloc(3 * sizeof(double));
		_arr = (double*)vecPool.malloc();
		std::memcpy(_arr, rhs._arr, 3 * sizeof(double));
	}
	jVec3d_fpu_heapAlloc(jVec3d_fpu_heapAlloc && rhs) noexcept
	{ 
		_arr = rhs._arr;
		rhs._arr = nullptr;
	}
	jVec3d_fpu_heapAlloc& operator=(const jVec3d_fpu_heapAlloc &rhs) noexcept
	{ 
		if (this != &rhs)
		{
			std::memcpy(_arr, rhs._arr, 3 * sizeof(double));
		}
		return *this; 
	}
	jVec3d_fpu_heapAlloc& operator=(jVec3d_fpu_heapAlloc &&rhs) noexcept 
	{ 
		if (this != &rhs)
		{
			_arr = rhs._arr;
			rhs._arr = nullptr;
		}
		return *this; 
	}
	~jVec3d_fpu_heapAlloc()
	{
		if (_arr != nullptr)
		{
			//spl::free(_arr);
			//free(_arr);
			vecPool.free(_arr);
		}
	}

public:
	J_FORCE_INLINE static jVec3d_fpu_heapAlloc zero() { return jVec3d_fpu_heapAlloc(); }

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
	jVec3d_fpu_heapAlloc operator-() const;
	jVec3d_fpu_heapAlloc& neg_org();

	jVec3d_fpu_heapAlloc Reciprocal_cpy() const;
	jVec3d_fpu_heapAlloc& Reciprocal_org();

	jVec3d_fpu_heapAlloc  operator+ (const jVec3d_fpu_heapAlloc& V) const;
	jVec3d_fpu_heapAlloc& add_org(const jVec3d_fpu_heapAlloc& V);

	jVec3d_fpu_heapAlloc  operator- (const jVec3d_fpu_heapAlloc& V) const;
	jVec3d_fpu_heapAlloc& sub_org(const jVec3d_fpu_heapAlloc& V);

	jVec3d_fpu_heapAlloc  operator*(double Scale) const;
	jVec3d_fpu_heapAlloc& scalar_mul_org(double Scale);

	jVec3d_fpu_heapAlloc  operator/(double Scale) const;
	jVec3d_fpu_heapAlloc& scalar_div_org(double Scale);

	jVec3d_fpu_heapAlloc  operator/(const jVec3d_fpu_heapAlloc& V) const;
	jVec3d_fpu_heapAlloc& div_org(const jVec3d_fpu_heapAlloc& V);

	jVec3d_fpu_heapAlloc  cwise_mult_cpy(const jVec3d_fpu_heapAlloc& V) const;
	jVec3d_fpu_heapAlloc& cwise_mult_org(const jVec3d_fpu_heapAlloc& V);

	jVec3d_fpu_heapAlloc  cross_cpy(const jVec3d_fpu_heapAlloc& V) const;
	jVec3d_fpu_heapAlloc& cross_org(const jVec3d_fpu_heapAlloc& V);

	jVec3d_fpu_heapAlloc  normalize_cpy() const;
	jVec3d_fpu_heapAlloc& normalize_org();

	double dot(const jVec3d_fpu_heapAlloc& V) const;

	friend J_FORCE_INLINE jVec3d_fpu_heapAlloc operator*(double Scale, const jVec3d_fpu_heapAlloc& V)
	{
		return V.operator*(Scale);
	}
};

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::operator-() const
{
	return jVec3d_fpu_heapAlloc{ -x(), -y(), -z() };
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::neg_org()
{
	x() = -x(); y() = -y(); z() = -z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::Reciprocal_cpy() const
{
	return jVec3d_fpu_heapAlloc{ 1.f / x(), 1.f / y(), 1.f / z() };
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::Reciprocal_org()
{
	x() = 1.f / x(); y() = 1.f / y(); z() = 1.f / z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::operator+ (const jVec3d_fpu_heapAlloc& V) const
{
	return jVec3d_fpu_heapAlloc{ x() + V.x(), y() + V.y(), z() + V.z() };
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::add_org(const jVec3d_fpu_heapAlloc& V)
{
	x() += V.x(); y() += V.y(); z() += V.z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::operator- (const jVec3d_fpu_heapAlloc& V) const
{
	return jVec3d_fpu_heapAlloc{ x() - V.x(), y() - V.y(), z() - V.z() };
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::sub_org(const jVec3d_fpu_heapAlloc& V)
{
	x() -= V.x(); y() -= V.y(); z() -= V.z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::operator* (double Scale) const
{
	return jVec3d_fpu_heapAlloc{ x() * Scale, y() * Scale, z() * Scale };
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::scalar_mul_org(double Scale)
{
	x() *= Scale; y() *= Scale; z() *= Scale;
	return *this;
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::operator/ (double Scale) const
{
	return jVec3d_fpu_heapAlloc{ x() / Scale, y() / Scale, z() / Scale };
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::scalar_div_org(double Scale)
{
	x() /= Scale; y() /= Scale; z() /= Scale;
	return *this;
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::operator/ (const jVec3d_fpu_heapAlloc& V) const
{
	return jVec3d_fpu_heapAlloc{ x() / V.x(), y() / V.y(), z() / V.z() };
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::div_org(const jVec3d_fpu_heapAlloc& V)
{
	x() /= V.x(); y() /= V.y(); z() /= V.z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::cwise_mult_cpy(const jVec3d_fpu_heapAlloc& V) const
{
	return jVec3d_fpu_heapAlloc{ x() * V.x(), y() * V.y(), z() * V.z() };
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::cwise_mult_org(const jVec3d_fpu_heapAlloc& V)
{
	x() *= V.x(); y() *= V.y(); z() *= V.z();
	return *this;
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::cross_cpy(const jVec3d_fpu_heapAlloc& V) const
{
	return jVec3d_fpu_heapAlloc{ y() * V.z() - z() * V.y(), z() * V.x() - x() * V.z(), x() * V.y() - y() * V.x() };
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::cross_org(const jVec3d_fpu_heapAlloc& V)
{
	double tmp_X = y() * V.z() - z() * V.y();
	double tmp_Y = z() * V.x() - x() * V.z();
	double tmp_Z = x() * V.y() - y() * V.x();
	x() = tmp_X, y() = tmp_Y, z() = tmp_Z;
	return *this;
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc jVec3d_fpu_heapAlloc::normalize_cpy() const
{
	return *this / std::sqrt(x() * x() + y() * y() + z() * z());
}

J_FORCE_INLINE jVec3d_fpu_heapAlloc& jVec3d_fpu_heapAlloc::normalize_org()
{
	return this->scalar_div_org(std::sqrt(x() * x() + y() * y() + z() * z()));
}

J_FORCE_INLINE double jVec3d_fpu_heapAlloc::dot(const jVec3d_fpu_heapAlloc& V) const
{
	return x() * V.x() + y() * V.y() + z() * V.z();
}

}