// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

// Modified by JohnYoung, 2018.3.9

#pragma once

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#ifdef _MSC_VER
#define jforceinline __forceinline
#endif

#ifdef __GNUC__
#define jforceinline inline __attribute__((always_inline))
#endif

/*=============================================================================
 *	Helpers:
 *============================================================================*/

/**
 *	float4 vector register type, where the first float (X) is stored in the lowest 32 bits, and so on.
 */
typedef DirectX::XMVECTOR VectorRegister;
typedef __m128i VectorRegisterInt;

// for an DirectX::XMVECTOR, we need a single set of braces (for clang)
#define DECLARE_VECTOR_REGISTER(X, Y, Z, W) { X, Y, Z, W }


/**
 * Returns a bitwise equivalent vector based on 4 DWORDs.
 *
 * @param X		1st unsigned int component
 * @param Y		2nd unsigned int component
 * @param Z		3rd unsigned int component
 * @param W		4th unsigned int component
 * @return		Bitwise equivalent vector with 4 floats
 */
jforceinline VectorRegister MakeVectorRegister( unsigned int X, unsigned int Y, unsigned int Z, unsigned int W )
{
	using namespace DirectX;
	return DirectX::XMVectorSetInt( X, Y, Z, W );
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
jforceinline VectorRegister MakeVectorRegister( float X, float Y, float Z, float W )
{		
	return DirectX::XMVectorSet( X, Y, Z, W );
}

/**
 * Returns a vector based on 4 int.
 *
 * @param X		1st int component
 * @param Y		2nd int component
 * @param Z		3rd int component
 * @param W		4th int component
 * @return		Vector of the 4 int
 */
jforceinline VectorRegisterInt MakeVectorRegisterInt(int X, int Y, int Z, int W)
{
	return _mm_castps_si128(DirectX::XMVectorSet(X, Y, Z, W));
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
 * Loads 4 FLOATs from unaligned memory.
 *
 * @param Ptr	Unaligned memory pointer to the 4 FLOATs
 * @return		VectorRegister(Ptr[0], Ptr[1], Ptr[2], Ptr[3])
 */
#define VectorLoad( Ptr )	DirectX::XMLoadFloat4( (const DirectX::XMFLOAT4*)(Ptr) )

/**
 * Loads 3 FLOATs from unaligned memory and leaves W undefined.
 *
 * @param Ptr	Unaligned memory pointer to the 3 FLOATs
 * @return		VectorRegister(Ptr[0], Ptr[1], Ptr[2], undefined)
 */
#define VectorLoadFloat3( Ptr )			MakeVectorRegister( ((const float*)(Ptr))[0], ((const float*)(Ptr))[1], ((const float*)(Ptr))[2], 0.0f )


/**
 * Loads 3 FLOATs from unaligned memory and sets W=0.
 *
 * @param Ptr	Unaligned memory pointer to the 3 FLOATs
 * @return		VectorRegister(Ptr[0], Ptr[1], Ptr[2], 0.0f)
 */
#define VectorLoadFloat3_W0( Ptr )		MakeVectorRegister( ((const float*)(Ptr))[0], ((const float*)(Ptr))[1], ((const float*)(Ptr))[2], 0.0f )


/**
 * Loads 3 FLOATs from unaligned memory and sets W=1.
 *
 * @param Ptr	Unaligned memory pointer to the 3 FLOATs
 * @return		VectorRegister(Ptr[0], Ptr[1], Ptr[2], 1.0f)
 */
#define VectorLoadFloat3_W1( Ptr )		MakeVectorRegister( ((const float*)(Ptr))[0], ((const float*)(Ptr))[1], ((const float*)(Ptr))[2], 1.0f )

/**
 * Loads 4 FLOATs from aligned memory.
 *
 * @param Ptr	Aligned memory pointer to the 4 FLOATs
 * @return		VectorRegister(Ptr[0], Ptr[1], Ptr[2], Ptr[3])
 */
#define VectorLoadAligned( Ptr )		DirectX::XMLoadFloat4A( (const DirectX::XMFLOAT4A*)(Ptr) )	

/**
 * Loads 1 float from unaligned memory and replicates it to all 4 elements.
 *
 * @param Ptr	Unaligned memory pointer to the float
 * @return		VectorRegister(Ptr[0], Ptr[0], Ptr[0], Ptr[0])
 */
#define VectorLoadFloat1( Ptr )			DirectX::XMVectorReplicatePtr( (const float*)(Ptr) )

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
 * Propagates passed in float to all registers
 *
 * @param X		float to replicate to all registers
 * @return		VectorRegister(X, X, X, X)
 */
#define VectorSetFloat1( X )			MakeVectorRegister( X, X, X, X )

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
 * Stores a vector to aligned memory.
 *
 * @param Vec	Vector to store
 * @param Ptr	Aligned memory pointer
 */
#define VectorStoreAligned( Vec, Ptr )	DirectX::XMStoreFloat4A((DirectX::XMFLOAT4A*)(Ptr), Vec )

 /**
 * Performs non-temporal store of a vector to aligned memory without polluting the caches
 *
 * @param Vec	Vector to store
 * @param Ptr	Aligned memory pointer
 */
#define VectorStoreAlignedStreamed( Vec, Ptr )	XM_STREAM_PS( (float*)(Ptr), Vec )

/**
 * Stores a vector to memory (aligned or unaligned).
 *
 * @param Vec	Vector to store
 * @param Ptr	Memory pointer
 */
#define VectorStore( Vec, Ptr )			DirectX::XMStoreFloat4((DirectX::XMFLOAT4*)(Ptr), Vec )

/**
 * Stores the XYZ components of a vector to unaligned memory.
 *
 * @param Vec	Vector to store XYZ
 * @param Ptr	Unaligned memory pointer
 */
#define VectorStoreFloat3( Vec, Ptr )	DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)(Ptr), Vec )

/**
 * Stores the X component of a vector to unaligned memory.
 *
 * @param Vec	Vector to store X
 * @param Ptr	Unaligned memory pointer
 */
#define VectorStoreFloat1( Vec, Ptr )	DirectX::XMStoreFloat((float*)(Ptr), Vec )
 

/**
 * Returns an component from a vector.
 *
 * @param Vec				Vector register
 * @param ComponentIndex	Which component to get, X=0, Y=1, Z=2, W=3
 * @return					The component as a float
 */
jforceinline float VectorGetComponent( VectorRegister Vec, unsigned int ComponentIndex )
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
 * Combines two vectors using bitwise OR (treating each vector as a 128 bit field)
 *
 * @param Vec1	1st vector
 * @param Vec2	2nd vector
 * @return		VectorRegister( for each bit i: Vec1[i] | Vec2[i] )
 */
#define VectorBitwiseOr( Vec1, Vec2 )	DirectX::XMVectorOrInt( Vec1, Vec2 )

/**
 * Combines two vectors using bitwise AND (treating each vector as a 128 bit field)
 *
 * @param Vec1	1st vector
 * @param Vec2	2nd vector
 * @return		VectorRegister( for each bit i: Vec1[i] & Vec2[i] )
 */
#define VectorBitwiseAnd( Vec1, Vec2 )	DirectX::XMVectorAndInt( Vec1, Vec2 )

/**
 * Combines two vectors using bitwise XOR (treating each vector as a 128 bit field)
 *
 * @param Vec1	1st vector
 * @param Vec2	2nd vector
 * @return		VectorRegister( for each bit i: Vec1[i] ^ Vec2[i] )
 */
#define VectorBitwiseXor( Vec1, Vec2 )	DirectX::XMVectorXorInt( Vec1, Vec2 )

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
 * Merges the XYZ components of one vector with the W component of another vector and returns the result.
 *
 * @param VecXYZ	Source vector for XYZ_
 * @param VecW		Source register for ___W (note: the fourth component is used, not the first)
 * @return			VectorRegister(VecXYZ.x, VecXYZ.y, VecXYZ.z, VecW.w)
 */
jforceinline VectorRegister VectorMergeVecXYZ_VecW(const VectorRegister& VecXYZ, const VectorRegister& VecW)
{
	using namespace DirectX;
	return DirectX::XMVectorSelect( VecXYZ, VecW, g_XMMaskW );
}

/**
 * Loads 4 BYTEs from unaligned memory and converts them into 4 FLOATs.
 * IMPORTANT: You need to call VectorResetFloatRegisters() before using scalar FLOATs after you've used this intrinsic!
 *
 * @param Ptr			Unaligned memory pointer to the 4 BYTEs.
 * @return				VectorRegister( float(Ptr[0]), float(Ptr[1]), float(Ptr[2]), float(Ptr[3]) )
 */
#define VectorLoadByte4( Ptr )		DirectX::PackedVector::XMLoadUByte4((const DirectX::PackedVector::XMUBYTE4*)(Ptr) )

/**
 * Loads 4 BYTEs from unaligned memory and converts them into 4 FLOATs in reversed order.
 * IMPORTANT: You need to call VectorResetFloatRegisters() before using scalar FLOATs after you've used this intrinsic!
 *
 * @param Ptr			Unaligned memory pointer to the 4 BYTEs.
 * @return				VectorRegister( float(Ptr[3]), float(Ptr[2]), float(Ptr[1]), float(Ptr[0]) )
 */
jforceinline VectorRegister VectorLoadByte4Reverse( const unsigned char* Ptr )
{
	VectorRegister Temp = VectorLoadByte4(Ptr);
	return VectorSwizzle(Temp,3,2,1,0);
}

/**
 * Converts the 4 FLOATs in the vector to 4 BYTEs, clamped to [0,255], and stores to unaligned memory.
 * IMPORTANT: You need to call VectorResetFloatRegisters() before using scalar FLOATs after you've used this intrinsic!
 *
 * @param Vec			Vector containing 4 FLOATs
 * @param Ptr			Unaligned memory pointer to store the 4 BYTEs.
 */
#define VectorStoreByte4( Vec, Ptr )		DirectX::PackedVector::XMStoreUByte4( (DirectX::PackedVector::XMUBYTE4*)(Ptr), Vec )

/**
* Loads packed RGB10A2(4 bytes) from unaligned memory and converts them into 4 FLOATs.
* IMPORTANT: You need to call VectorResetFloatRegisters() before using scalar FLOATs after you've used this intrinsic!
*
* @param Ptr			Unaligned memory pointer to the RGB10A2(4 bytes).
* @return				VectorRegister with 4 FLOATs loaded from Ptr.
*/
#define VectorLoadURGB10A2N( Ptr )	DirectX::PackedVector::XMLoadUDecN4( (const DirectX::PackedVector::XMUDECN4*)(Ptr) )

/**
* Converts the 4 FLOATs in the vector RGB10A2, clamped to [0, 1023] and [0, 3], and stores to unaligned memory.
* IMPORTANT: You need to call VectorResetFloatRegisters() before using scalar FLOATs after you've used this intrinsic!
*
* @param Vec			Vector containing 4 FLOATs
* @param Ptr			Unaligned memory pointer to store the packed RGB10A2(4 bytes).
*/
#define VectorStoreURGB10A2N( Vec, Ptr )	DirectX::PackedVector::XMStoreUDecN4( (const DirectX::PackedVector::XMUDECN4*)(Ptr), Vec )

/**
* Loads packed RGBA16(4 bytes) from unaligned memory and converts them into 4 FLOATs.
* IMPORTANT: You need to call VectorResetFloatRegisters() before using scalar FLOATs after you've used this intrinsic!
*
* @param Ptr			Unaligned memory pointer to the RGBA16(8 bytes).
* @return				VectorRegister with 4 FLOATs loaded from Ptr.
*/
#define VectorLoadURGBA16N( Ptr )	DirectX::PackedVector::XMLoadUShortN4( (const DirectX::PackedVector::XMUSHORTN4*)(Ptr) )

/**
* Converts the 4 FLOATs in the vector RGBA16, clamped to [0, 65535], and stores to unaligned memory.
* IMPORTANT: You need to call VectorResetFloatRegisters() before using scalar FLOATs after you've used this intrinsic!
*
* @param Vec			Vector containing 4 FLOATs
* @param Ptr			Unaligned memory pointer to store the packed RGBA16(8 bytes).
*/
#define VectorStoreURGBA16N( Vec, Ptr )	DirectX::PackedVector::XMStoreUShortN4( (const DirectX::PackedVector::XMUSHORTN4*)(Ptr), Vec )

/**
 * Returns non-zero if any element in Vec1 is greater than the corresponding element in Vec2, otherwise 0.
 *
 * @param Vec1			1st source vector
 * @param Vec2			2nd source vector
 * @return				Non-zero integer if (Vec1.x > Vec2.x) || (Vec1.y > Vec2.y) || (Vec1.z > Vec2.z) || (Vec1.w > Vec2.w)
 */
jforceinline unsigned int VectorAnyGreaterThan(const VectorRegister& Vec1, const VectorRegister& Vec2)
{
	using namespace DirectX;
	// Returns a comparison value that can be examined using functions such as XMComparisonAllTrue
	unsigned  comparisonValue = XMVector4GreaterR( Vec1, Vec2 );
	
	//Returns true if any of the compared components are true
	return (unsigned int)XMComparisonAnyTrue( comparisonValue );
}

/**
 * Resets the floating point registers so that they can be used again.
 * Some intrinsics use these for MMX purposes (e.g. VectorLoadByte4 and VectorStoreByte4).
 */
// This is no longer necessary now that we don't use MMX instructions
#define VectorResetFloatRegisters()

/**
 * Returns the control register.
 *
 * @return			The unsigned int control register
 */
#define VectorGetControlRegister()		_mm_getcsr()

/**
 * Sets the control register.
 *
 * @param ControlStatus		The unsigned int control status value to set
 */
#define	VectorSetControlRegister(ControlStatus) _mm_setcsr( ControlStatus )

/**
 * Control status bit to round all floating point math results towards zero.
 */
#define VECTOR_ROUND_TOWARD_ZERO		_MM_ROUND_TOWARD_ZERO

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
jforceinline VectorRegister VectorQuaternionMultiply2( const VectorRegister& Quat1, const VectorRegister& Quat2 )
{
	// DirectXMath uses reverse parameter order to UnrealMath
	// XMQuaternionMultiply( FXMVECTOR Q1, FXMVECTOR Q2)
	// Returns the product Q2*Q1 (which is the concatenation of a rotation Q1 followed by the rotation Q2)

	// [ (Q2.w * Q1.x) + (Q2.x * Q1.w) + (Q2.y * Q1.z) - (Q2.z * Q1.y),
	//   (Q2.w * Q1.y) - (Q2.x * Q1.z) + (Q2.y * Q1.w) + (Q2.z * Q1.x),
	//   (Q2.w * Q1.z) + (Q2.x * Q1.y) - (Q2.y * Q1.x) + (Q2.z * Q1.w),
	//   (Q2.w * Q1.w) - (Q2.x * Q1.x) - (Q2.y * Q1.y) - (Q2.z * Q1.z) ]
	return DirectX::XMQuaternionMultiply( Quat2, Quat1  );
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
jforceinline void VectorQuaternionMultiply( VectorRegister *VResult, const VectorRegister* VQuat1, const VectorRegister* VQuat2)
{	
	*VResult = VectorQuaternionMultiply2(*VQuat1, *VQuat2);
}


jforceinline VectorRegister VectorCeil(const VectorRegister& X)
{
	return DirectX::XMVectorCeiling(X);
}

jforceinline VectorRegister VectorFloor(const VectorRegister& X)
{
	return DirectX::XMVectorFloor(X);
}

jforceinline VectorRegister VectorTruncate(const VectorRegister& X)
{
	return DirectX::XMVectorTruncate(X);
}

jforceinline VectorRegister VectorFractional(const VectorRegister& X)
{
	return VectorSubtract(X, VectorTruncate(X));
}

jforceinline VectorRegister VectorMod(const VectorRegister& X, const VectorRegister& Y)
{
	return DirectX::XMVectorMod(X, Y);
}

//TODO: Vectorize
jforceinline VectorRegister VectorSign(const VectorRegister& X)
{
	return MakeVectorRegister(
		(float)(VectorGetComponent(X, 0) >= 0.0f ? 1.0f : -1.0f),
		(float)(VectorGetComponent(X, 1) >= 0.0f ? 1.0f : -1.0f),
		(float)(VectorGetComponent(X, 2) >= 0.0f ? 1.0f : -1.0f),
		(float)(VectorGetComponent(X, 3) >= 0.0f ? 1.0f : -1.0f));
}

//TODO: Vectorize
jforceinline VectorRegister VectorStep(const VectorRegister& X)
{
	return MakeVectorRegister(
		(float)(VectorGetComponent(X, 0) >= 0.0f ? 1.0f : -1.0f),
		(float)(VectorGetComponent(X, 1) >= 0.0f ? 1.0f : -1.0f),
		(float)(VectorGetComponent(X, 2) >= 0.0f ? 1.0f : -1.0f),
		(float)(VectorGetComponent(X, 3) >= 0.0f ? 1.0f : -1.0f));
}

//////////////////////////////////////////////////////////////////////////
//Integer ops

//Bitwise
/** = a & b */
#define VectorIntAnd(A, B)		_mm_and_si128(A, B)
/** = a | b */
#define VectorIntOr(A, B)		_mm_or_si128(A, B)
/** = a ^ b */
#define VectorIntXor(A, B)		_mm_xor_si128(A, B)
/** = (~a) & b */
#define VectorIntAndNot(A, B)	_mm_andnot_si128(A, B)

//Comparison
#define VectorIntCompareEQ(A, B)	_mm_cmpeq_epi32(A,B)
#define VectorIntCompareNEQ(A, B)	VectorIntNot(_mm_cmpeq_epi32(A,B))
#define VectorIntCompareGT(A, B)	_mm_cmpgt_epi32(A,B)
#define VectorIntCompareLT(A, B)	_mm_cmplt_epi32(A,B)
#define VectorIntCompareGE(A, B)	VectorIntNot(VectorIntCompareLT(A,B))
#define VectorIntCompareLE(A, B)	VectorIntNot(VectorIntCompareGT(A,B))


jforceinline VectorRegisterInt VectorIntSelect(const VectorRegisterInt& Mask, const VectorRegisterInt& Vec1, const VectorRegisterInt& Vec2)
{
	return _mm_xor_si128(Vec2, _mm_and_si128(Mask, _mm_xor_si128(Vec1, Vec2)));
}

//Arithmetic
#define VectorIntAdd(A, B)	_mm_add_epi32(A, B)
#define VectorIntSubtract(A, B)	_mm_sub_epi32(A, B)

jforceinline VectorRegisterInt VectorIntMultiply(const VectorRegisterInt& A, const VectorRegisterInt& B)
{
	//SSE2 doesn't have a multiply op for 4 32bit ints. Ugh.
	__m128i Temp0 = _mm_mul_epu32(A, B);
	__m128i Temp1 = _mm_mul_epu32(_mm_srli_si128(A, 4), _mm_srli_si128(B, 4));
	return _mm_unpacklo_epi32(_mm_shuffle_epi32(Temp0, _MM_SHUFFLE(0, 0, 2, 0)), _mm_shuffle_epi32(Temp1, _MM_SHUFFLE(0, 0, 2, 0)));
}

jforceinline VectorRegisterInt VectorIntMin(const VectorRegisterInt& A, const VectorRegisterInt& B)
{
	VectorRegisterInt Mask = VectorIntCompareLT(A, B);
	return VectorIntSelect(Mask, A, B);
}

jforceinline VectorRegisterInt VectorIntMax(const VectorRegisterInt& A, const VectorRegisterInt& B)
{
	VectorRegisterInt Mask = VectorIntCompareGT(A, B);
	return VectorIntSelect(Mask, A, B);
}


#define VectorIntToFloat(A) _mm_cvtepi32_ps(A)
#define VectorFloatToInt(A) _mm_cvttps_epi32(A)

//Loads and stores

/**
* Stores a vector to memory (aligned or unaligned).
*
* @param Vec	Vector to store
* @param Ptr	Memory pointer
*/
#define VectorIntStore( Vec, Ptr )			_mm_storeu_si128( (VectorRegisterInt*)(Ptr), Vec )

/**
* Loads 4 ints from unaligned memory.
*
* @param Ptr	Unaligned memory pointer to the 4 ints
* @return		VectorRegisterInt(Ptr[0], Ptr[1], Ptr[2], Ptr[3])
*/
#define VectorIntLoad( Ptr )				_mm_loadu_si128( (VectorRegisterInt*)(Ptr) )

/**
* Stores a vector to memory (aligned).
*
* @param Vec	Vector to store
* @param Ptr	Aligned Memory pointer
*/
#define VectorIntStoreAligned( Vec, Ptr )			_mm_store_si128( (VectorRegisterInt*)(Ptr), Vec )

/**
* Loads 4 ints from aligned memory.
*
* @param Ptr	Aligned memory pointer to the 4 ints
* @return		VectorRegisterInt(Ptr[0], Ptr[1], Ptr[2], Ptr[3])
*/
#define VectorIntLoadAligned( Ptr )				_mm_load_si128( (VectorRegisterInt*)(Ptr) )

/**
* Loads 1 int from unaligned memory into all components of a vector register.
*
* @param Ptr	Unaligned memory pointer to the 4 ints
* @return		VectorRegisterInt(*Ptr, *Ptr, *Ptr, *Ptr)
*/
#define VectorIntLoad1( Ptr )	_mm_shuffle_epi32(_mm_loadu_si128((VectorRegisterInt*)Ptr),_MM_SHUFFLE(0,0,0,0))