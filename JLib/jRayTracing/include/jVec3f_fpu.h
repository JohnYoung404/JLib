#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/17/2018]
// Description : Float-precision vector contains 3 elements.

#include <array>
#include "jCommon.h"

namespace jRayTracing
{

class jVec3f_fpu
{
public:
    std::array<float, 3> _arr;
    
public:
    constexpr explicit jVec3f_fpu(float InX = 0.0f, float InY = 0.0f, float InZ = 0.0f) : _arr{ InX, InY, InZ } { }
	constexpr jVec3f_fpu(const jVec3f_fpu &rhs) noexcept : _arr(rhs._arr) { }
	constexpr jVec3f_fpu(jVec3f_fpu && rhs) noexcept : _arr(std::move(rhs._arr)) { }
	jVec3f_fpu& operator=(const jVec3f_fpu &rhs) { _arr = rhs._arr; return *this; }
	jVec3f_fpu& operator=(jVec3f_fpu &&rhs) { _arr = std::move(rhs._arr); return *this; }

public:
    J_FORCE_INLINE static constexpr jVec3f_fpu zero() { return jVec3f_fpu(); }

public:
    J_FORCE_INLINE float& operator[](int ComponentIndex) { return _arr[ComponentIndex]; }
    J_FORCE_INLINE float  operator[](int ComponentIndex) const { return _arr[ComponentIndex]; }
    J_FORCE_INLINE float x() const { return _arr[0]; }
    J_FORCE_INLINE float y() const { return _arr[1]; }
    J_FORCE_INLINE float z() const { return _arr[2]; }
    J_FORCE_INLINE float& x() { return _arr[0]; }
    J_FORCE_INLINE float& y() { return _arr[1]; }
    J_FORCE_INLINE float& z() { return _arr[2]; }

public:
    jVec3f_fpu operator-() const;
    jVec3f_fpu& neg_org();

    jVec3f_fpu Reciprocal_cpy() const;
    jVec3f_fpu& Reciprocal_org();

    jVec3f_fpu  operator+ (const jVec3f_fpu& V) const;
    jVec3f_fpu& add_org(const jVec3f_fpu& V);

    jVec3f_fpu  operator- (const jVec3f_fpu& V) const;
    jVec3f_fpu& sub_org(const jVec3f_fpu& V);

    jVec3f_fpu  operator*(float Scale) const;
    jVec3f_fpu& scalar_mul_org(float Scale);

    jVec3f_fpu  operator/(float Scale) const;
    jVec3f_fpu& scalar_div_org(float Scale);

    jVec3f_fpu  operator/(const jVec3f_fpu& V) const;
    jVec3f_fpu& div_org(const jVec3f_fpu& V);

    jVec3f_fpu  cwise_mult_cpy(const jVec3f_fpu& V) const;
    jVec3f_fpu& cwise_mult_org(const jVec3f_fpu& V);

    jVec3f_fpu  cross_cpy(const jVec3f_fpu& V) const;
    jVec3f_fpu& cross_org(const jVec3f_fpu& V);

    jVec3f_fpu  normalize_cpy() const;
    jVec3f_fpu& normalize_org();

    float dot(const jVec3f_fpu& V) const;

    friend J_FORCE_INLINE jVec3f_fpu operator*(float Scale, const jVec3f_fpu& V)
    {
        return V.operator*(Scale);
    }
};

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::operator-() const
{
    return jVec3f_fpu{-x(), -y(), -z()};
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::neg_org()
{
    x() = -x(); y() = -y(); z() = -z();
    return *this;
}

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::Reciprocal_cpy() const
{
    return jVec3f_fpu{ 1.f / x(), 1.f / y(), 1.f / z() };
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::Reciprocal_org()
{
    x() = 1.f / x(); y() = 1.f / y(); z() = 1.f / z();
    return *this;
}

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::operator+ (const jVec3f_fpu& V) const
{
    return jVec3f_fpu{ x() + V.x(), y() + V.y(), z() + V.z() };
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::add_org(const jVec3f_fpu& V)
{
    x() += V.x(); y() += V.y(); z() += V.z();
    return *this;
}

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::operator- (const jVec3f_fpu& V) const
{
    return jVec3f_fpu{ x() - V.x(), y() - V.y(), z() - V.z() };
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::sub_org(const jVec3f_fpu& V)
{
    x() -= V.x(); y() -= V.y(); z() -= V.z();
    return *this;
}

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::operator* (float Scale) const
{
    return jVec3f_fpu{ x() * Scale, y() * Scale, z() * Scale };
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::scalar_mul_org(float Scale)
{
    x() *= Scale; y() *= Scale; z() *= Scale;
    return *this;
}

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::operator/ (float Scale) const
{
    return jVec3f_fpu{ x() / Scale, y() / Scale, z() / Scale };
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::scalar_div_org(float Scale)
{
    x() /= Scale; y() /= Scale; z() /= Scale;
    return *this;
}

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::operator/ (const jVec3f_fpu& V) const
{
    return jVec3f_fpu{ x() / V.x(), y() / V.y(), z() / V.z() };
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::div_org(const jVec3f_fpu& V)
{
    x() /= V.x(); y() /= V.y(); z() /= V.z();
    return *this;
}

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::cwise_mult_cpy(const jVec3f_fpu& V) const
{
    return jVec3f_fpu{ x() * V.x(), y() * V.y(), z() * V.z() };
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::cwise_mult_org(const jVec3f_fpu& V)
{
    x() *= V.x(); y() *= V.y(); z() *= V.z();
    return *this;
}

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::cross_cpy(const jVec3f_fpu& V) const
{
    return jVec3f_fpu{ y() * V.z() - z() * V.y(), z() * V.x() - x() * V.z(), x() * V.y() - y() * V.x() };
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::cross_org(const jVec3f_fpu& V)
{
    float tmp_X = y() * V.z() - z() * V.y();
    float tmp_Y = z() * V.x() - x() * V.z();
    float tmp_Z = x() * V.y() - y() * V.x();
    x() = tmp_X, y() = tmp_Y, z() = tmp_Z;
    return *this;
}

J_FORCE_INLINE jVec3f_fpu jVec3f_fpu::normalize_cpy() const
{
    return *this / std::sqrt(x() * x() + y() * y() + z() * z());
}

J_FORCE_INLINE jVec3f_fpu& jVec3f_fpu::normalize_org()
{
    return this->scalar_div_org(std::sqrt(x() * x() + y() * y() + z() * z()));
}

J_FORCE_INLINE float jVec3f_fpu::dot(const jVec3f_fpu& V) const
{
    return x() * V.x() + y() * V.y() + z() * V.z();
}

}