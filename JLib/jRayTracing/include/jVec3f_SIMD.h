#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/18/2018]
// Description : 3-d Vector, accelerated with SIMD.

#include "jCommon.h"
#include <array>

namespace jRayTracing
{

J_ALIGN(16) struct jVec3f_SIMD
{
public:
    float _VEC[4];

public:
    explicit jVec3f_SIMD(float InX = 0.0f, float InY = 0.0f, float InZ = 0.0f);

public:
    float& operator[](int ComponentIndex);
    float  operator[](int ComponentIndex) const;
    J_FORCE_INLINE float x() const { return _VEC[0]; };
    J_FORCE_INLINE float y() const { return _VEC[1]; };
    J_FORCE_INLINE float z() const { return _VEC[2]; };
    J_FORCE_INLINE float& x() { return _VEC[0]; };
    J_FORCE_INLINE float& y() { return _VEC[1]; };
    J_FORCE_INLINE float& z() { return _VEC[2]; };

public:
    jVec3f_SIMD operator-() const;
    jVec3f_SIMD& neg_org();

    jVec3f_SIMD  operator+ (const jVec3f_SIMD& V) const;
    jVec3f_SIMD& add_org(const jVec3f_SIMD& V);

    jVec3f_SIMD  operator- (const jVec3f_SIMD& V) const;
    jVec3f_SIMD& sub_org(const jVec3f_SIMD& V);

    jVec3f_SIMD  operator*(float Scale) const;
    jVec3f_SIMD& scalar_mul_org(float Scale);

    jVec3f_SIMD  operator/(float Scale) const;
    jVec3f_SIMD& scalar_div_org(float Scale);

    jVec3f_SIMD  operator/(const jVec3f_SIMD& V) const;
    jVec3f_SIMD& div_org(const jVec3f_SIMD& V);

    jVec3f_SIMD  cwise_mult_cpy(const jVec3f_SIMD& V) const;
    jVec3f_SIMD& cwise_mult_org(const jVec3f_SIMD& V);

    jVec3f_SIMD  cross_cpy(const jVec3f_SIMD& V) const;
    jVec3f_SIMD& cross_org(const jVec3f_SIMD& V);

    jVec3f_SIMD  normalize_cpy() const;
    jVec3f_SIMD& normalize_org();

    float dot(const jVec3f_SIMD& V) const;

    friend J_FORCE_INLINE jVec3f_SIMD operator*(float Scale, const jVec3f_SIMD& V)
    {
        return V.operator*(Scale);
    }
};


//////////////////////////////////////////////////////////////////////////
// Inline Functions.
//////////////////////////////////////////////////////////////////////////

J_FORCE_INLINE jVec3f_SIMD::jVec3f_SIMD(float InX, float InY, float InZ) : _VEC{ InX, InY, InZ}{}

J_FORCE_INLINE float& jVec3f_SIMD::operator[](int ComponentIndex)
{
    return _VEC[ComponentIndex];
}

J_FORCE_INLINE float jVec3f_SIMD::operator[](int ComponentIndex) const
{
    return _VEC[ComponentIndex];
}

J_FORCE_INLINE jVec3f_SIMD jVec3f_SIMD::operator-() const
{
    J_ALIGN(16) float Ret[4];
    VectorRegister vr = VectorLoadAligned(Ret);
    VectorRegister neg_vr = VectorNegate(vr);
    VectorStoreAligned(neg_vr, Ret);
    return jVec3f_SIMD(Ret[0], Ret[1], Ret[2]);
}

J_FORCE_INLINE jVec3f_SIMD& jVec3f_SIMD::neg_org()
{
    VectorRegister vr = VectorLoadAligned(_VEC);
    VectorRegister neg_vr = VectorNegate(vr);
    VectorStoreAligned(neg_vr, _VEC);
    return *this;
}

J_FORCE_INLINE jVec3f_SIMD jVec3f_SIMD::operator+ (const jVec3f_SIMD& V) const
{
    J_ALIGN(16) float Ret[4];
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorAdd(vr_a, vr_b);
    VectorStoreAligned(vr_r, Ret);
    return jVec3f_SIMD(Ret[0], Ret[1], Ret[2]);
}

J_FORCE_INLINE jVec3f_SIMD& jVec3f_SIMD::add_org (const jVec3f_SIMD& V)
{
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorAdd(vr_a, vr_b);
    VectorStoreAligned(vr_r, _VEC);
    return *this;
}

J_FORCE_INLINE jVec3f_SIMD jVec3f_SIMD::operator- (const jVec3f_SIMD& V) const
{
    J_ALIGN(16) float Ret[4];
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorSubtract(vr_a, vr_b);
    VectorStoreAligned(vr_r, Ret);
    return jVec3f_SIMD(Ret[0], Ret[1], Ret[2]);
}

J_FORCE_INLINE jVec3f_SIMD& jVec3f_SIMD::sub_org(const jVec3f_SIMD& V)
{
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorSubtract(vr_a, vr_b);
    VectorStoreAligned(vr_r, _VEC);
    return *this;
}

J_FORCE_INLINE jVec3f_SIMD jVec3f_SIMD::operator* (float Scale) const
{
    J_ALIGN(16) float Ret[4] = {Scale, Scale, Scale, 0};
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(Ret);
    VectorRegister vr_r = VectorMultiply(vr_a, vr_b);
    VectorStoreAligned(vr_r, Ret);
    return jVec3f_SIMD(Ret[0], Ret[1], Ret[2]);
}

J_FORCE_INLINE jVec3f_SIMD& jVec3f_SIMD::scalar_mul_org (float Scale)
{
    J_ALIGN(16) float S[4] = { Scale, Scale, Scale, 0 };
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(S);
    VectorRegister vr_r = VectorMultiply(vr_a, vr_b);
    VectorStoreAligned(vr_r, _VEC);
    return *this;
}

J_FORCE_INLINE jVec3f_SIMD jVec3f_SIMD::operator/ (float Scale) const
{
    J_ALIGN(16) float Ret[4] = { Scale, Scale, Scale, 0 };
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(Ret);
    VectorRegister vr_r = VectorDivide(vr_a, vr_b);
    VectorStoreAligned(vr_r, Ret);
    return jVec3f_SIMD(Ret[0], Ret[1], Ret[2]);
}

J_FORCE_INLINE jVec3f_SIMD& jVec3f_SIMD::scalar_div_org(float Scale)
{
    J_ALIGN(16) float S[4] = { Scale, Scale, Scale, 0 };
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(S);
    VectorRegister vr_r = VectorDivide(vr_a, vr_b);
    VectorStoreAligned(vr_r, _VEC);
    return *this;
}

J_FORCE_INLINE jVec3f_SIMD jVec3f_SIMD::operator/ (const jVec3f_SIMD& V) const
{
    J_ALIGN(16) float Ret[4];
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorDivide(vr_a, vr_b);
    VectorStoreAligned(vr_r, Ret);
    return jVec3f_SIMD(Ret[0], Ret[1], Ret[2]);
}

J_FORCE_INLINE jVec3f_SIMD& jVec3f_SIMD::div_org(const jVec3f_SIMD& V)
{
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorDivide(vr_a, vr_b);
    VectorStoreAligned(vr_r, _VEC);
    return *this;
}

J_FORCE_INLINE jVec3f_SIMD jVec3f_SIMD::cwise_mult_cpy(const jVec3f_SIMD& V) const
{
    J_ALIGN(16) float Ret[4];
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorMultiply(vr_a, vr_b);
    VectorStoreAligned(vr_r, Ret);
    return jVec3f_SIMD(Ret[0], Ret[1], Ret[2]);
}

J_FORCE_INLINE jVec3f_SIMD& jVec3f_SIMD::cwise_mult_org(const jVec3f_SIMD& V)
{
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorMultiply(vr_a, vr_b);
    VectorStoreAligned(vr_r, _VEC);
    return *this;
}

J_FORCE_INLINE jVec3f_SIMD jVec3f_SIMD::cross_cpy(const jVec3f_SIMD& V) const
{
    J_ALIGN(16) float Ret[4];
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorCross(vr_a, vr_b);
    VectorStoreAligned(vr_r, Ret);
    return jVec3f_SIMD(Ret[0], Ret[1], Ret[2]);
}

J_FORCE_INLINE jVec3f_SIMD& jVec3f_SIMD::cross_org(const jVec3f_SIMD& V)
{
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorCross(vr_a, vr_b);
    VectorStoreAligned(vr_r, _VEC);
    return *this;
}

J_FORCE_INLINE jVec3f_SIMD jVec3f_SIMD::normalize_cpy() const
{
    J_ALIGN(16) jVec3f_SIMD Ret;
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorSet_W0(vr_a);
    VectorRegister vr_r = VectorNormalize(vr_b);
    VectorStoreAligned(vr_r, Ret._VEC);
    return Ret;
}

J_FORCE_INLINE jVec3f_SIMD& jVec3f_SIMD::normalize_org()
{
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorSet_W0(vr_a);
    VectorRegister vr_r = VectorNormalize(vr_b);
    VectorStoreAligned(vr_r, _VEC);
    return *this;
}

J_FORCE_INLINE float jVec3f_SIMD::dot(const jVec3f_SIMD& V) const
{
    VectorRegister vr_a = VectorLoadAligned(_VEC);
    VectorRegister vr_b = VectorLoadAligned(V._VEC);
    VectorRegister vr_r = VectorDot3(vr_a, vr_b);
    return vr_r.m128_f32[0];
}

}