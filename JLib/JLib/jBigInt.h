#pragma once
#include <vector>
#include "jIntString.h"
#include "jTestBase.h"

namespace jLib {

namespace jNum
{

class jBigInt {
public:
	jBigInt(const std::string &initstring);
	jBigInt(int i = 0);
	jBigInt(jBigInt && rhs) noexcept;
	jBigInt(const jBigInt &rhs);
	const jBigInt& operator=(const jBigInt & rhs);
	const jBigInt& operator=(jBigInt && rhs) noexcept;

	jBigInt& operator += (const jBigInt& rhs);
	jBigInt& operator -= (const jBigInt& rhs);
	jBigInt& operator *= (const jBigInt& rhs);    
	jBigInt& operator /= (const jBigInt& rhs);
	jBigInt& operator %= (const jBigInt& rhs);
	jBigInt& operator << (size_t indent);
	jBigInt& operator >> (size_t indent);

	friend inline const jBigInt operator + (const jBigInt& lhs, const jBigInt& rhs) 
	{
		jBigInt left(lhs);
		return std::move(left += rhs);
	}
	friend inline const jBigInt operator - (const jBigInt& lhs, const jBigInt& rhs) 
	{
		jBigInt left(lhs);
		return std::move(left -= rhs);
	}
	friend inline const jBigInt operator * (const jBigInt& lhs, const jBigInt& rhs) 
	{
		jBigInt left(lhs);
		return std::move(left *= rhs);
	}
	friend inline const jBigInt operator / (const jBigInt& lhs, const jBigInt& rhs) 
	{
		jBigInt left(lhs);
		return std::move(left /= rhs);
	}
	friend inline const jBigInt operator % (const jBigInt& lhs, const jBigInt& rhs) 
	{
		jBigInt left(lhs);
		return std::move(left %= rhs);
	}
	friend inline const bool operator== (const jBigInt &lhs, const jBigInt &rhs) 
	{
		if (lhs.bitlen() != rhs.bitlen())	return false;
		return std::equal(lhs.bitArr_.begin(), lhs.bitArr_.end(), rhs.bitArr_.begin(), rhs.bitArr_.end());
	}

	const jIntString toIntString() const;

private:
	std::vector<bool> bitArr_;	//in vector<bool>, bits are stored as 1-bit not 8-bits.

	inline const size_t bitlen() const 
	{
		return bitArr_.size();
	}

	inline const size_t signBit() const 
	{
		return bitArr_.size() - 1;
	}

	void toComplement();
	void toOpposite();
	void extendBitlen(size_t largerLen);
	void condenceBits();
	const size_t maxLeftShiftLen() const;
};

extern std::ostream& operator << (std::ostream &output, const jBigInt &jbi);

}
	
}

namespace jLib {
	class jBigIntTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			try
			{
				jNum::jBigInt k = "464132132164163132135464121";
				jNum::jBigInt T = "134612313513143";
				std::cout << (k / T) + 1;	//division would be slow in debug mode.
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	};
}