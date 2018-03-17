#pragma once

// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
// Modified by John Young
// Contact : JohnYoung404@outlook.com
// Date : [3/17/2018]
// Modification : DirectXMath Wrapper. Remove Interfaces of byte/int/unaligned/bitwise version.

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

typedef DirectX::XMVECTOR VectorRegister;
#define J_FORCE_INLINE          __forceinline
/**
* Returns a bitwise equivalent vector based on 4 DWORDs.
*
* @param X		1st unsigned int component
* @param Y		2nd unsigned int component
* @param Z		3rd unsigned int component
* @param W		4th unsigned int component
* @return		Bitwise equivalent vector with 4 floats
*/
J_FORCE_INLINE VectorRegister MakeVectorRegister(unsigned int X, unsigned int Y, unsigned int Z, unsigned int W)
{
    using namespace DirectX;
    return DirectX::XMVectorSetInt(X, Y, Z, W);
}

/**
* Returns a vector based on 4 FLOATs.
*
* @param X		1st float component
* @param Y		2nd float component
* @param Z		3rd float component
* @param W		4th float component
* @return		Vector of the 4 FLOATs
*/
J_FORCE_INLINE VectorRegister MakeVectorRegister(float X, float Y, float Z, float W)
{
    return DirectX::XMVectorSet(X, Y, Z, W);
}

/*=============================================================================
*	Intrinsics:
*============================================================================*/

/**
* Returns a vector with all zeros.
*
* @return		VectorRegister(0.0f, 0.0f, 0.0f, 0.0f)
*/
#define VectorZero()				DirectX::XMVectorZero()

/**
* Returns a vector with all ones.
*
* @return		VectorRegister(1.0f, 1.0f, 1.0f, 1.0f)
*/
#define VectorOne()					DirectX::g_XMOne.v

/**
* Loads 4 FLOATs from aligned memory.
*
* @param Ptr	Aligned memory pointer to the 4 FLOATs
* @return		VectorRegister(Ptr[0], Ptr[1], Ptr[2], Ptr[3])
*/
#define VectorLoadAligned( Ptr )		DirectX::XMLoadFloat4A( (const DirectX::XMFLOAT4A*)(Ptr) )	

/**
* Stores a vector to aligned memory.
*
* @param Vec	Vector to store
* @param Ptr	Aligned memory pointer
*/
#define VectorStoreAligned( Vec, Ptr )	DirectX::XMStoreFloat4A((DirectX::XMFLOAT4A*)(Ptr), Vec )

/**
* Creates a vector out of three FLOATs and leaves W undefined.
*
* @param X		1st float component
* @param Y		2nd float component
* @param Z		3rd float component
* @return		VectorRegister(X, Y, Z, undefined)
*/
#define VectorSetFloat3( X, Y, Z )		MakeVectorRegister( X, Y, Z, 0.0f )

/**
* Creates a vector out of four FLOATs.
*
* @param X		1st float component
* @param Y		2nd float component
* @param Z		3rd float component
* @param W		4th float component
* @return		VectorRegister(X, Y, Z, W)
*/
#define VectorSet( X, Y, Z, W )			MakeVectorRegister( X, Y, Z, W )

/**
* Performs non-temporal store of a vector to aligned memory without polluting the caches
*
* @param Vec	Vector to store
* @param Ptr	Aligned memory pointer
*/
#define VectorStoreAlignedStreamed( Vec, Ptr )	XM_STREAM_PS( (float*)(Ptr), Vec )

/**
* Returns an component from a vector.
*
* @param Vec				Vector register
* @param ComponentIndex	Which component to get, X=0, Y=1, Z=2, W=3
* @return					The component as a float
*/
J_FORCE_INLINE float VectorGetComponent(VectorRegister Vec, unsigned int ComponentIndex)
{
    switch (ComponentIndex)
    {
    case 0:
        return DirectX::XMVectorGetX(Vec);
    case 1:
        return DirectX::XMVectorGetY(Vec);
    case 2:
        return DirectX::XMVectorGetZ(Vec);
    case 3:
        return DirectX::XMVectorGetW(Vec);
    }
    return 0.0f;
}

/**
* Replicates one element into all four elements and returns the new vector.
*
* @param Vec			Source vector
* @param ElementIndex	Index (0-3) of the element to replicate
* @return				VectorRegister( Vec[ElementIndex], Vec[ElementIndex], Vec[ElementIndex], Vec[ElementIndex] )
*/
#define VectorReplicate( Vec, ElementIndex )	DirectX::XMVectorSwizzle<ElementIndex,ElementIndex,ElementIndex,ElementIndex>(Vec)

/**
* Returns the absolute value (component-wise).
*
* @param Vec			Source vector
* @return				VectorRegister( abs(Vec.x), abs(Vec.y), abs(Vec.z), abs(Vec.w) )
*/
#define VectorAbs( Vec )				DirectX::XMVectorAbs( Vec )

/**
* Returns the negated value (component-wise).
*
* @param Vec			Source vector
* @return				VectorRegister( -Vec.x, -Vec.y, -Vec.z, -Vec.w )
*/
#define VectorNegate( Vec )				DirectX::XMVectorNegate( Vec )

/**
* Adds two vectors (component-wise) and returns the result.
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x+Vec2.x, Vec1.y+Vec2.y, Vec1.z+Vec2.z, Vec1.w+Vec2.w )
*/
#define VectorAdd( Vec1, Vec2 )			DirectX::XMVectorAdd( Vec1, Vec2 )

/**
* Subtracts a vector from another (component-wise) and returns the result.
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x-Vec2.x, Vec1.y-Vec2.y, Vec1.z-Vec2.z, Vec1.w-Vec2.w )
*/
#define VectorSubtract( Vec1, Vec2 )	DirectX::XMVectorSubtract( Vec1, Vec2 )

/**
* Multiplies two vectors (component-wise) and returns the result.
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x*Vec2.x, Vec1.y*Vec2.y, Vec1.z*Vec2.z, Vec1.w*Vec2.w )
*/
#define VectorMultiply( Vec1, Vec2 )	DirectX::XMVectorMultiply( Vec1, Vec2 )

/**
* Divides two vectors (component-wise) and returns the result.
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x/Vec2.x, Vec1.y/Vec2.y, Vec1.z/Vec2.z, Vec1.w/Vec2.w )
*/
#define VectorDivide( Vec1, Vec2 )	DirectX::XMVectorDivide( Vec1, Vec2 )

/**
* Multiplies two vectors (component-wise), adds in the third vector and returns the result.
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @param Vec3	3rd vector
* @return		VectorRegister( Vec1.x*Vec2.x + Vec3.x, Vec1.y*Vec2.y + Vec3.y, Vec1.z*Vec2.z + Vec3.z, Vec1.w*Vec2.w + Vec3.w )
*/
#define VectorMultiplyAdd( Vec1, Vec2, Vec3 )	DirectX::XMVectorMultiplyAdd( Vec1, Vec2, Vec3 )

/**
* Calculates the dot3 product of two vectors and returns a vector with the result in all 4 components.
* Only really efficient on Xbox 360.
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		d = dot3(Vec1.xyz, Vec2.xyz), VectorRegister( d, d, d, d )
*/
#define VectorDot3( Vec1, Vec2 )		DirectX::XMVector3Dot( Vec1, Vec2 )

/**
* Calculates the dot4 product of two vectors and returns a vector with the result in all 4 components.
* Only really efficient on Xbox 360.
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		d = dot4(Vec1.xyzw, Vec2.xyzw), VectorRegister( d, d, d, d )
*/
#define VectorDot4( Vec1, Vec2 )		DirectX::XMVector4Dot( Vec1, Vec2 )

/**
* Creates a four-part mask based on component-wise == compares of the input vectors
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x == Vec2.x ? 0xFFFFFFFF : 0, same for yzw )
*/
#define VectorCompareEQ( Vec1, Vec2 )	DirectX::XMVectorEqual( Vec1, Vec2 )

/**
* Creates a four-part mask based on component-wise != compares of the input vectors
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x != Vec2.x ? 0xFFFFFFFF : 0, same for yzw )
*/
#define VectorCompareNE( Vec1, Vec2 )	DirectX::XMVectorNotEqual( Vec1, Vec2 )

/**
* Creates a four-part mask based on component-wise > compares of the input vectors
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x > Vec2.x ? 0xFFFFFFFF : 0, same for yzw )
*/
#define VectorCompareGT( Vec1, Vec2 )	DirectX::XMVectorGreater( Vec1, Vec2 )

/**
* Creates a four-part mask based on component-wise >= compares of the input vectors
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x >= Vec2.x ? 0xFFFFFFFF : 0, same for yzw )
*/
#define VectorCompareGE( Vec1, Vec2 )	DirectX::XMVectorGreaterOrEqual( Vec1, Vec2 )

/**
* Creates a four-part mask based on component-wise < compares of the input vectors
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x < Vec2.x ? 0xFFFFFFFF : 0, same for yzw )
*/
#define VectorCompareLT( Vec1, Vec2 )			_mm_cmplt_ps( Vec1, Vec2 )

/**
* Creates a four-part mask based on component-wise <= compares of the input vectors
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( Vec1.x <= Vec2.x ? 0xFFFFFFFF : 0, same for yzw )
*/
#define VectorCompareLE( Vec1, Vec2 )			_mm_cmple_ps( Vec1, Vec2 )

/**
* Does a bitwise vector selection based on a mask (e.g., created from VectorCompareXX)
*
* @param Mask  Mask (when 1: use the corresponding bit from Vec1 otherwise from Vec2)
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( for each bit i: Mask[i] ? Vec1[i] : Vec2[i] )
*
*/
#define VectorSelect( Mask, Vec1, Vec2 )	DirectX::XMVectorSelect( Vec2, Vec1, Mask )

/**
* Returns an integer bit-mask (0x00 - 0x0f) based on the sign-bit for each component in a vector.
*
* @param VecMask		Vector
* @return				Bit 0 = sign(VecMask.x), Bit 1 = sign(VecMask.y), Bit 2 = sign(VecMask.z), Bit 3 = sign(VecMask.w)
*/
#define VectorMaskBits( VecMask )			_mm_movemask_ps( VecMask )

/**
* Calculates the cross product of two vectors (XYZ components). W is set to 0.
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		cross(Vec1.xyz, Vec2.xyz). W is set to 0.
*/
#define VectorCross( Vec1, Vec2 )	DirectX::XMVector3Cross( Vec1, Vec2 )

/**
* Calculates x raised to the power of y (component-wise).
*
* @param Base		Base vector
* @param Exponent	Exponent vector
* @return			VectorRegister( Base.x^Exponent.x, Base.y^Exponent.y, Base.z^Exponent.z, Base.w^Exponent.w )
*/
#define VectorPow( Vec1, Vec2 )	DirectX::XMVectorPow( Vec1, Vec2 )


/**
* Returns an estimate of 1/sqrt(c) for each component of the vector
*
* @param Vector		Vector
* @return			VectorRegister(1/sqrt(t), 1/sqrt(t), 1/sqrt(t), 1/sqrt(t))
*/
#define VectorReciprocalSqrt( Vec )	DirectX::XMVectorReciprocalSqrtEst( Vec )

/**
* Computes an estimate of the reciprocal of a vector (component-wise) and returns the result.
*
* @param Vec	1st vector
* @return		VectorRegister( (Estimate) 1.0f / Vec.x, (Estimate) 1.0f / Vec.y, (Estimate) 1.0f / Vec.z, (Estimate) 1.0f / Vec.w )
*/
#define VectorReciprocal( Vec )	DirectX::XMVectorReciprocalEst( Vec )

/**
* Return Reciprocal Length of the vector
*
* @param Vector		Vector
* @return			VectorRegister(rlen, rlen, rlen, rlen) when rlen = 1/sqrt(dot4(V))
*/
#define VectorReciprocalLen( Vec )	DirectX::XMVector4ReciprocalLengthEst( Vec )

/**
* Return the reciprocal of the square root of each component
*
* @param Vector		Vector
* @return			VectorRegister(1/sqrt(Vec.X), 1/sqrt(Vec.Y), 1/sqrt(Vec.Z), 1/sqrt(Vec.W))
*/
#define VectorReciprocalSqrtAccurate( Vec )	DirectX::XMVectorReciprocalSqrt( Vec )

/**
* Computes the reciprocal of a vector (component-wise) and returns the result.
*
* @param Vec	1st vector
* @return		VectorRegister( 1.0f / Vec.x, 1.0f / Vec.y, 1.0f / Vec.z, 1.0f / Vec.w )
*/
#define VectorReciprocalAccurate( Vec )	DirectX::XMVectorReciprocal( Vec )

/**
* Normalize vector
*
* @param Vector		Vector to normalize
* @return			Normalized VectorRegister
*/
#define VectorNormalize( Vec )	DirectX::XMVector4NormalizeEst( Vec )

/**
* Loads XYZ and sets W=0
*
* @param Vector	VectorRegister
* @return		VectorRegister(X, Y, Z, 0.0f)
*/
#define VectorSet_W0( Vec )		DirectX::XMVectorAndInt( Vec , DirectX::g_XMMask3 )

/**
* Loads XYZ and sets W=1
*
* @param Vector	VectorRegister
* @return		VectorRegister(X, Y, Z, 1.0f)
*/
#define VectorSet_W1( Vec )		DirectX::XMVectorPermute<0,1,2,7>( Vec, VectorOne() )


/**
* Returns the minimum values of two vectors (component-wise).
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( min(Vec1.x,Vec2.x), min(Vec1.y,Vec2.y), min(Vec1.z,Vec2.z), min(Vec1.w,Vec2.w) )
*/
#define VectorMin( Vec1, Vec2 )		DirectX::XMVectorMin( Vec1, Vec2 )	

/**
* Returns the maximum values of two vectors (component-wise).
*
* @param Vec1	1st vector
* @param Vec2	2nd vector
* @return		VectorRegister( max(Vec1.x,Vec2.x), max(Vec1.y,Vec2.y), max(Vec1.z,Vec2.z), max(Vec1.w,Vec2.w) )
*/
#define VectorMax( Vec1, Vec2 )		DirectX::XMVectorMax( Vec1, Vec2 )	

/**
* Swizzles the 4 components of a vector and returns the result.
*
* @param Vec		Source vector
* @param X			Index for which component to use for X (literal 0-3)
* @param Y			Index for which component to use for Y (literal 0-3)
* @param Z			Index for which component to use for Z (literal 0-3)
* @param W			Index for which component to use for W (literal 0-3)
* @return			The swizzled vector
*/
#define VectorSwizzle( Vec, X, Y, Z, W ) DirectX::XMVectorSwizzle<X,Y,Z,W>( Vec )

/**
* Creates a vector through selecting two components from each vector via a shuffle mask.
*
* @param Vec1		Source vector1
* @param Vec2		Source vector2
* @param X			Index for which component of Vector1 to use for X (literal 0-3)
* @param Y			Index for which component to Vector1 to use for Y (literal 0-3)
* @param Z			Index for which component to Vector2 to use for Z (literal 0-3)
* @param W			Index for which component to Vector2 to use for W (literal 0-3)
* @return			The swizzled vector
*/
#define VectorShuffle( Vec1, Vec2, X, Y, Z, W )	DirectX::XMVectorPermute<X,Y,Z+4,W+4>( Vec1, Vec2 )

/**
* Returns non-zero if any element in Vec1 is greater than the corresponding element in Vec2, otherwise 0.
*
* @param Vec1			1st source vector
* @param Vec2			2nd source vector
* @return				Non-zero integer if (Vec1.x > Vec2.x) || (Vec1.y > Vec2.y) || (Vec1.z > Vec2.z) || (Vec1.w > Vec2.w)
*/
J_FORCE_INLINE unsigned int VectorAnyGreaterThan(const VectorRegister& Vec1, const VectorRegister& Vec2)
{
    using namespace DirectX;
    // Returns a comparison value that can be examined using functions such as XMComparisonAllTrue
    unsigned  comparisonValue = XMVector4GreaterR(Vec1, Vec2);

    //Returns true if any of the compared components are true
    return (unsigned int)XMComparisonAnyTrue(comparisonValue);
}

/**
* Multiplies two quaternions; the order matters.
*
* Order matters when composing quaternions: C = VectorQuaternionMultiply2(A, B) will yield a quaternion C = A * B
* that logically first applies B then A to any subsequent transformation (right first, then left).
*
* @param Quat1	Pointer to the first quaternion
* @param Quat2	Pointer to the second quaternion
* @return Quat1 * Quat2
*/
J_FORCE_INLINE VectorRegister VectorQuaternionMultiply2(const VectorRegister& Quat1, const VectorRegister& Quat2)
{
    // DirectXMath uses reverse parameter order to UnrealMath
    // XMQuaternionMultiply( FXMVECTOR Q1, FXMVECTOR Q2)
    // Returns the product Q2*Q1 (which is the concatenation of a rotation Q1 followed by the rotation Q2)

    // [ (Q2.w * Q1.x) + (Q2.x * Q1.w) + (Q2.y * Q1.z) - (Q2.z * Q1.y),
    //   (Q2.w * Q1.y) - (Q2.x * Q1.z) + (Q2.y * Q1.w) + (Q2.z * Q1.x),
    //   (Q2.w * Q1.z) + (Q2.x * Q1.y) - (Q2.y * Q1.x) + (Q2.z * Q1.w),
    //   (Q2.w * Q1.w) - (Q2.x * Q1.x) - (Q2.y * Q1.y) - (Q2.z * Q1.z) ]
    return DirectX::XMQuaternionMultiply(Quat2, Quat1);
}

/**
* Multiplies two quaternions; the order matters.
*
* When composing quaternions: VectorQuaternionMultiply(C, A, B) will yield a quaternion C = A * B
* that logically first applies B then A to any subsequent transformation (right first, then left).
*
* @param Result	Pointer to where the result Quat1 * Quat2 should be stored
* @param Quat1	Pointer to the first quaternion (must not be the destination)
* @param Quat2	Pointer to the second quaternion (must not be the destination)
*/
J_FORCE_INLINE void VectorQuaternionMultiply(VectorRegister *VResult, const VectorRegister* VQuat1, const VectorRegister* VQuat2)
{
    *VResult = VectorQuaternionMultiply2(*VQuat1, *VQuat2);
}

J_FORCE_INLINE VectorRegister VectorCeil(const VectorRegister& X)
{
    return DirectX::XMVectorCeiling(X);
}

J_FORCE_INLINE VectorRegister VectorFloor(const VectorRegister& X)
{
    return DirectX::XMVectorFloor(X);
}

J_FORCE_INLINE VectorRegister VectorTruncate(const VectorRegister& X)
{
    return DirectX::XMVectorTruncate(X);
}

J_FORCE_INLINE VectorRegister VectorFractional(const VectorRegister& X)
{
    return VectorSubtract(X, VectorTruncate(X));
}

J_FORCE_INLINE VectorRegister VectorMod(const VectorRegister& X, const VectorRegister& Y)
{
    return DirectX::XMVectorMod(X, Y);
}

//TODO: Vectorize
J_FORCE_INLINE VectorRegister VectorSign(const VectorRegister& X)
{
    return MakeVectorRegister(
        (float)(VectorGetComponent(X, 0) >= 0.0f ? 1.0f : -1.0f),
        (float)(VectorGetComponent(X, 1) >= 0.0f ? 1.0f : -1.0f),
        (float)(VectorGetComponent(X, 2) >= 0.0f ? 1.0f : -1.0f),
        (float)(VectorGetComponent(X, 3) >= 0.0f ? 1.0f : -1.0f));
}

//TODO: Vectorize
J_FORCE_INLINE VectorRegister VectorStep(const VectorRegister& X)
{
    return MakeVectorRegister(
        (float)(VectorGetComponent(X, 0) >= 0.0f ? 1.0f : -1.0f),
        (float)(VectorGetComponent(X, 1) >= 0.0f ? 1.0f : -1.0f),
        (float)(VectorGetComponent(X, 2) >= 0.0f ? 1.0f : -1.0f),
        (float)(VectorGetComponent(X, 3) >= 0.0f ? 1.0f : -1.0f));
}