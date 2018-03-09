#pragma once
#include <xmmintrin.h>  //SSE
#include <immintrin.h>  //AVX
#include <array>
#include "jUtility.h"
#include <DirectXMath.h>

#define jSHUFFLE_PARAM(x, y, z, w) ((x) | ((y) << 2) | ((z) << 4) | ((w) << 6))

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jContainer)

// float precision
#pragma pack(push)
#pragma pack(16)
class jVec3f_SIMD
{
public:
    constexpr jVec3f_SIMD(float x_ = 0, float y_ = 0, float z_ = 0) : _arr{ x_, y_, z_, 0 } {}
    constexpr jVec3f_SIMD(const jVec3f_SIMD &rhs) : _arr(rhs._arr) {}
    constexpr jVec3f_SIMD(jVec3f_SIMD && rhs) noexcept : _arr(std::move(rhs._arr)) {}
    jVec3f_SIMD& operator= (const jVec3f_SIMD &rhs)
    {
        _arr = rhs._arr;
        return *this;
    }
    jVec3f_SIMD& operator= (jVec3f_SIMD && rhs) noexcept
    {
        _arr = std::move(rhs._arr);
        return *this;
    }
    jforceinline static constexpr const jVec3f_SIMD zero() { return jVec3f_SIMD(); }
    jforceinline const float& x() const { return _arr[0]; }
    jforceinline const float& y() const { return _arr[1]; }
    jforceinline const float& z() const { return _arr[2]; }
    jforceinline float& x() { return _arr[0]; }
    jforceinline float& y() { return _arr[1]; }
    jforceinline float& z() { return _arr[2]; }

    const float & at(size_t pos) const { return _arr.at(pos); }
    float & at(size_t pos) { return _arr.at(pos); }
    const float & operator[](size_t pos) const { return _arr[pos]; }
    float & operator[](size_t pos) { return _arr[pos]; }

    inline const float square_length() const
    {
        return (*this) * (*this);
    }
    const jVec3f_SIMD normalize() const 
    { 
        return *this / sqrt(_dot(*this)); 
    }                

    float dot(const jVec3f_SIMD &rhs) const
    {
        return _dot(rhs);
    }
    jVec3f_SIMD mult(const jVec3f_SIMD &rhs) const
    {
        jVec3f_SIMD ret = *this;
        return ret._cwise_mult(rhs);
    }
    jVec3f_SIMD cross(const jVec3f_SIMD &rhs) const
    {
        jVec3f_SIMD ret = *this;
        return ret._cross(rhs);
    }
    jforceinline friend jVec3f_SIMD operator+(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs);
    jforceinline friend jVec3f_SIMD operator-(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs);
    jforceinline friend float operator*(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs);
    jforceinline friend jVec3f_SIMD operator*(const jVec3f_SIMD &vec, float scarlar);
    jforceinline friend jVec3f_SIMD operator*(float scarlar, const jVec3f_SIMD &vec);
    jforceinline friend jVec3f_SIMD operator/(const jVec3f_SIMD &vec, float scarlar);
    jforceinline friend jVec3f_SIMD mult(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs);
    jforceinline friend float dot(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs);
    jforceinline friend jVec3f_SIMD cross(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs);
private:
    std::array<float, 4> _arr;
    jVec3f_SIMD& operator+=(const jVec3f_SIMD &rhs)
    {
        __m128 a = _mm_load_ps(_arr._Elems);
        __m128 b = _mm_load_ps(rhs._arr._Elems);
        __m128 c = _mm_add_ps(a, b);
        _mm_store_ps(_arr._Elems, c);
        return *this;
    }
    jVec3f_SIMD& operator-=(const jVec3f_SIMD &rhs)
    {
        __m128 a = _mm_load_ps(_arr._Elems);
        __m128 b = _mm_load_ps(rhs._arr._Elems);
        __m128 c = _mm_sub_ps(a, b);
        _mm_store_ps(_arr._Elems, c);
        return *this;
    }
    float _dot(const jVec3f_SIMD &rhs) const
    {
        jAlign(16) float temp[4];
        __m128 a = _mm_load_ps(_arr._Elems);
        __m128 b = _mm_load_ps(rhs._arr._Elems);
        __m128 c = _mm_mul_ps(a, b);
        _mm_store_ps(temp, c);
        return temp[0] + temp[1] + temp[2];
    }
    jVec3f_SIMD& _cwise_mult(const jVec3f_SIMD &rhs)
    {
        __m128 a = _mm_load_ps(_arr._Elems);
        __m128 b = _mm_load_ps(rhs._arr._Elems);
        __m128 c = _mm_mul_ps(a, b);
        _mm_store_ps(_arr._Elems, c);
        return *this;
    }
    jVec3f_SIMD& _scarlar_mult(float scarlar)
    {
        jAlign(16) float temp[] = { scarlar, scarlar, scarlar, 0 };
        __m128 a = _mm_load_ps(_arr._Elems);
        __m128 b = _mm_load_ps(temp);
        __m128 c = _mm_mul_ps(a, b);
        _mm_store_ps(_arr._Elems, c);
        return *this;
    }
    jVec3f_SIMD& _scarlar_div(float scarlar)
    {
        jAlign(16) float temp[] = { scarlar, scarlar, scarlar, 1.f };
        __m128 a = _mm_load_ps(_arr._Elems);
        __m128 b = _mm_load_ps(temp);
        __m128 c = _mm_div_ps(a, b);
        _mm_store_ps(_arr._Elems, c);
        return *this;
    }
    jVec3f_SIMD& _cross(const jVec3f_SIMD &rhs)
    {
        __m128 a = _mm_load_ps(_arr._Elems);
        __m128 a1 = a;
        _mm_shuffle_ps(a, a, jSHUFFLE_PARAM(1, 2, 0, 3));
        _mm_shuffle_ps(a1, a1, jSHUFFLE_PARAM(2, 0, 1, 3));
        __m128 b = _mm_load_ps(rhs._arr._Elems);
        __m128 b1 = b;
        _mm_shuffle_ps(b, b, jSHUFFLE_PARAM(2, 0, 1, 3));
        _mm_shuffle_ps(b1, b1, jSHUFFLE_PARAM(1, 2, 0, 3));

        __m128 a_mul_b = _mm_mul_ps(a, b);
        __m128 a1_mul_b1 = _mm_mul_ps(a1, b1);

        __m128 c = _mm_sub_ps(a_mul_b, a1_mul_b1);
        _mm_store_ps(_arr._Elems, c);
        return *this;
    }
};
#pragma pack(pop)

extern std::ostream& operator<< (std::ostream& os, const jVec3f_SIMD &outVec);

jVec3f_SIMD operator+(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs)
{
    jVec3f_SIMD ret = lhs;
    ret += rhs;
    return ret;
}

jVec3f_SIMD operator-(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs)
{
    jVec3f_SIMD ret = lhs;
    ret -= rhs;
    return ret;
}

float operator*(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs)
{
    return lhs._dot(rhs);
}

jVec3f_SIMD operator*(const jVec3f_SIMD &vec, float scarlar)
{
    jVec3f_SIMD ret = vec;
    return ret._scarlar_mult(scarlar);
}

jVec3f_SIMD operator*(float scarlar, const jVec3f_SIMD &vec)
{
    jVec3f_SIMD ret = vec;
    return ret._scarlar_mult(scarlar);
}

jVec3f_SIMD operator/(const jVec3f_SIMD &vec, float scarlar)
{
    jVec3f_SIMD ret = vec;
    return ret._scarlar_div(scarlar);
}

float dot(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs)
{
    return lhs._dot(rhs);
}

jVec3f_SIMD mult(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs)
{
    jVec3f_SIMD ret = lhs;
    return ret._cwise_mult(rhs);
}

jVec3f_SIMD cross(const jVec3f_SIMD &lhs, const jVec3f_SIMD &rhs)
{
    jVec3f_SIMD ret = lhs;
    return ret._cross(rhs);
}

// double precision
class jVec3d_SIMD
{
public:
    jVec3d_SIMD(double x_ = 0, double y_ = 0, double z_ = 0) : _arr{ x_, y_, z_ } {}
    jVec3d_SIMD(const jVec3d_SIMD &rhs) : _arr(rhs._arr) {}
    jVec3d_SIMD(jVec3d_SIMD && rhs) noexcept : _arr(std::move(rhs._arr)) {}
    jVec3d_SIMD& operator= (const jVec3d_SIMD &rhs)
    {
        _arr = rhs._arr;
        return *this;
    }
    jVec3d_SIMD& operator= (jVec3d_SIMD && rhs) noexcept
    {
        _arr = std::move(rhs._arr);
        return *this;
    }
    jforceinline static const jVec3d_SIMD zero() { return jVec3d_SIMD(); }
    jforceinline const double& x() const { return _arr[0]; }
    jforceinline const double& y() const { return _arr[1]; }
    jforceinline const double& z() const { return _arr[2]; }
    jforceinline double& x() { return _arr[0]; }
    jforceinline double& y() { return _arr[1]; }
    jforceinline double& z() { return _arr[2]; }

    jforceinline const double & at(size_t pos) const { return _arr.at(pos); }
    jforceinline double & at(size_t pos) { return _arr.at(pos); }
    jforceinline const double & operator[](size_t pos) const { return _arr[pos]; }
    jforceinline double & operator[](size_t pos) { return _arr[pos]; }

    jforceinline const double square_length() const
    {
        return (*this) * (*this);
    }
    jforceinline const jVec3d_SIMD normalize() const
    {
        return *this / sqrt(_dot(*this));
    }

    jforceinline double dot(const jVec3d_SIMD &rhs) const
    {
        return _dot(rhs);
    }
    jforceinline jVec3d_SIMD mult(const jVec3d_SIMD &rhs) const
    {
        jVec3d_SIMD ret = *this;
        return ret._cwise_mult(rhs);
    }
    jforceinline jVec3d_SIMD cross(const jVec3d_SIMD &rhs) const
    {
        jVec3d_SIMD ret = *this;
        return ret._cross(rhs);
    }
    jforceinline friend jVec3d_SIMD operator+(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs);
    jforceinline friend jVec3d_SIMD operator-(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs);
    jforceinline friend double operator*(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs);
    jforceinline friend jVec3d_SIMD operator*(const jVec3d_SIMD &vec, double scarlar);
    jforceinline friend jVec3d_SIMD operator*(double scarlar, const jVec3d_SIMD &vec);
    jforceinline friend jVec3d_SIMD operator/(const jVec3d_SIMD &vec, double scarlar);
    jforceinline friend jVec3d_SIMD mult(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs);
    jforceinline friend double dot(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs);
    jforceinline friend jVec3d_SIMD cross(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs);
private:
    jAlign(32) std::array<double, 4> _arr;
    jVec3d_SIMD& operator+=(const jVec3d_SIMD &rhs)
    {
        __m256d a = _mm256_load_pd(_arr._Elems);
        __m256d b = _mm256_load_pd(rhs._arr._Elems);
        __m256d c = _mm256_add_pd(a, b);
        _mm256_store_pd(_arr._Elems, c);
        return *this;
    }
    jVec3d_SIMD& operator-=(const jVec3d_SIMD &rhs)
    {
        __m256d a = _mm256_load_pd(_arr._Elems);
        __m256d b = _mm256_load_pd(rhs._arr._Elems);
        __m256d c = _mm256_sub_pd(a, b);
        _mm256_store_pd(_arr._Elems, c);
        return *this;
    }
    double _dot(const jVec3d_SIMD &rhs) const
    {
        jAlign(32) double temp[4];
        __m256d a = _mm256_load_pd(_arr._Elems);
        __m256d b = _mm256_load_pd(rhs._arr._Elems);
        __m256d c = _mm256_mul_pd(a, b);
        _mm256_store_pd(temp, c);
        return temp[0] + temp[1] + temp[2];
    }
    jVec3d_SIMD& _cwise_mult(const jVec3d_SIMD &rhs)
    {
        __m256d a = _mm256_load_pd(_arr._Elems);
        __m256d b = _mm256_load_pd(rhs._arr._Elems);
        __m256d c = _mm256_mul_pd(a, b);
        _mm256_store_pd(_arr._Elems, c);
        return *this;
    }
    jVec3d_SIMD& _scarlar_mult(double scarlar)
    {
        jAlign(32) double temp[] = { scarlar, scarlar, scarlar, 0 };
        __m256d a = _mm256_load_pd(_arr._Elems);
        __m256d b = _mm256_load_pd(temp);
        __m256d c = _mm256_mul_pd(a, b);
        _mm256_store_pd(_arr._Elems, c);
        return *this;
    }
    jVec3d_SIMD& _scarlar_div(double scarlar)
    {
        jAlign(32) double temp[] = { scarlar, scarlar, scarlar, 0 };
        __m256d a = _mm256_load_pd(_arr._Elems);
        __m256d b = _mm256_load_pd(temp);
        __m256d c = _mm256_div_pd(a, b);
        _mm256_store_pd(_arr._Elems, c);
        return *this;
    }
    jVec3d_SIMD& _cross(const jVec3d_SIMD &rhs)
    {
        auto tmp_x = y() * rhs.z() - z() * rhs.y();
        auto tmp_y = z() * rhs.x() - x() * rhs.z();
        auto tmp_z = x() * rhs.y() - y() * rhs.x();
        //__m256d a = _mm256_load_pd(_arr._Elems);
        //__m256d a1 = a;
        //constexpr int x = jSHUFFLE_PARAM(2, 2, 2, 2);
        //_mm256_shuffle_pd(a, a, x);
        //_mm256_shuffle_pd(a1, a1, jSHUFFLE_PARAM(2, 0, 1, 3));
        //__m256d b = _mm256_load_pd(rhs._arr._Elems);
        //__m256d b1 = b;
        //_mm256_shuffle_pd(b, b, jSHUFFLE_PARAM(2, 0, 1, 3));
        //_mm256_shuffle_pd(b1, b1, jSHUFFLE_PARAM(1, 2, 0, 3));
        //
        //__m256d a_mul_b = _mm256_mul_pd(a, b);
        //__m256d a1_mul_b1 = _mm256_mul_pd(a1, b1);
        //
        //__m256d c = _mm256_sub_pd(a_mul_b, a1_mul_b1);
        //_mm256_store_pd(_arr._Elems, c);
        return jVec3d_SIMD(tmp_x, tmp_y, tmp_z);
    }
};

extern std::ostream& operator<< (std::ostream& os, const jVec3d_SIMD &outVec);

jVec3d_SIMD operator+(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs)
{
    jVec3d_SIMD ret = lhs;
    ret += rhs;
    return ret;
}

jVec3d_SIMD operator-(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs)
{
    jVec3d_SIMD ret = lhs;
    ret -= rhs;
    return ret;
}

double operator*(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs)
{
    return lhs._dot(rhs);
}

jVec3d_SIMD operator*(const jVec3d_SIMD &vec, double scarlar)
{
    jVec3d_SIMD ret = vec;
    return ret._scarlar_mult(scarlar);
}

jVec3d_SIMD operator*(double scarlar, const jVec3d_SIMD &vec)
{
    jVec3d_SIMD ret = vec;
    return ret._scarlar_mult(scarlar);
}

jVec3d_SIMD operator/(const jVec3d_SIMD &vec, double scarlar)
{
    jVec3d_SIMD ret = vec;
    return ret._scarlar_div(scarlar);
}

double dot(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs)
{
    return lhs._dot(rhs);
}

jVec3d_SIMD mult(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs)
{
    jVec3d_SIMD ret = lhs;
    return ret._cwise_mult(rhs);
}

jVec3d_SIMD cross(const jVec3d_SIMD &lhs, const jVec3d_SIMD &rhs)
{
    jVec3d_SIMD ret = lhs;
    return ret._cross(rhs);
}

NAME_SPACE_END
NAME_SPACE_END