#pragma once
#include <vector>
#include <sstream>
#include <iostream>
#include "jIntString.h"

namespace jLib {

	class jBigInt {
	public:
		jBigInt(const std::string initstring) {
			jIntString jis = initstring;
			jis.changeRadix(2);
			for (auto i : jis.numVecRef())
			{
				bitArr_.push_back(i);
			}
			if (jis.Sign() == true)
				bitArr_.push_back(0);
			else
				bitArr_.push_back(1);
			toComplement();
		}
		jBigInt(int i = 0) {
			std::string intString;
			std::stringstream ss;
			ss << i;
			ss >> intString;
			*this = std::move(jBigInt(intString));
		}
		jBigInt(jBigInt && rhs) 
		{
			bitArr_ = std::move(rhs.bitArr_);
		}
		jBigInt(const jBigInt &rhs) : bitArr_ (rhs.bitArr_){}
		const jBigInt& operator=(const jBigInt & rhs) {
			if (this != &rhs) {
				bitArr_ = rhs.bitArr_;
			}
			return *this;
		}
		const jBigInt& operator=(jBigInt && rhs){
			if (this != &rhs)
			{
				bitArr_ = std::move(rhs.bitArr_);
			}
			return *this;
		}

		jBigInt& operator += (const jBigInt& rhs) {
			size_t newlen = 1 + (rhs.bitlen() > bitlen() ? rhs.bitlen() : bitlen());
			jBigInt ext_rhs(rhs);
			ext_rhs.extendBitlen(newlen);
			this->extendBitlen(newlen);
			size_t i, t, carryflag;
			for (carryflag = i = 0; i < bitlen(); ++i) {
				t = ext_rhs.bitArr_[i] + bitArr_[i] + carryflag;
				bitArr_[i] = t % 2;
				carryflag = t > 1 ? 1 : 0;
			}
			condenceBits();
			return *this;
		}
		friend inline const jBigInt operator + (const jBigInt& lhs, const jBigInt& rhs) {
			jBigInt left(lhs);
			return std::move(left += rhs);
		}
		jBigInt& operator -= (const jBigInt& rhs)
		{
			jBigInt oppo_rhs(rhs);
			oppo_rhs.toOpposite();
			*this += oppo_rhs;
			return *this;
		}
		friend inline const jBigInt operator - (const jBigInt& lhs, const jBigInt& rhs) {
			jBigInt left(lhs);
			return std::move(left -= rhs);
		}
		jBigInt& operator *= (const jBigInt& rhs)        //implement Booth Algorithm.
		{
			jBigInt neg_lhs(*this);
			neg_lhs.toOpposite();
			jBigInt ret = "0";
			int i;
			for (i = rhs.signBit(); i > 0 && rhs.bitArr_[i] == rhs.bitArr_[i - 1]; i--);
			while (i > 0)
			{
				ret << 1;
				if (rhs.bitArr_[i] != rhs.bitArr_[i - 1])
				{
					ret += (rhs.bitArr_[i - 1] > rhs.bitArr_[i]) ? *this : neg_lhs;
				}
				i--;
			}

			ret << 1;
			if (rhs.bitArr_[0] != 0)
			{
				ret += neg_lhs;
			}
			condenceBits();
			*this = std::move(ret);
			return *this;
		}
		friend inline const jBigInt operator * (const jBigInt& lhs, const jBigInt& rhs) {
			jBigInt left(lhs);
			return std::move(left *= rhs);
		}
		jBigInt& operator /= (const jBigInt& rhs)        //implement Booth Algorithm.
		{
			jBigInt a = std::move(*this);
			jBigInt b(rhs);
			jBigInt ret = 0;
			jBigInt c, d, e, remainder;
			size_t newlen = a.bitlen() > b.bitlen() ? a.bitlen() : b.bitlen();
			a.extendBitlen(newlen);
			b.extendBitlen(newlen);
			ret.extendBitlen(newlen);
			int low, high, mid;
			low = 0;
			high = b.maxLeftShiftLen();
			c = a;

			if (a.bitArr_[a.signBit()] == b.bitArr_[b.signBit()])
			{
				ret.bitArr_[ret.signBit()] = 0;
				while (1)
				{
					while (low <= high)
					{
						mid = (high + low) / 2;
						d = b;
						d << mid;
						e = c - d;
						if (d.bitArr_[d.signBit()] == e.bitArr_[e.signBit()] || e == 0)
							low = mid + 1;
						else
							high = mid - 1;
					}
					if (high != -1)
					{
						ret.bitArr_[high] = 1;
						d = b;
						d << high;
						c = c - d;
						low = 0;
						high--;
					}
					else
					{
						remainder = c;
						break;
					}
				}
			}
			else {
				ret.bitArr_[ret.signBit()] = 1;
				while (1)
				{
					while (low <= high)
					{
						mid = (high + low) / 2;
						d = b;
						d << mid;
						e = c + d;
						if (d.bitArr_[d.signBit()] != e.bitArr_[e.signBit()] || e == 0)
							low = mid + 1;
						else
							high = mid - 1;
					}
					if (high != -1)
					{
						ret.bitArr_[high] = 1;
						d = b;
						d << high;
						c = c + d;
						low = 0;
						high--;
					}
					else
					{
						remainder = c;
						break;
					}
				}
			}
			ret.toComplement();
			ret.condenceBits();
			*this = std::move(ret);
			return *this;
		}
		friend inline const jBigInt operator / (const jBigInt& lhs, const jBigInt& rhs) {
			jBigInt left(lhs);
			return std::move(left /= rhs);
		}
		jBigInt& operator %= (const jBigInt& rhs)        //implement Booth Algorithm.
		{
			jBigInt a(*this);
			jBigInt b(rhs);
			jBigInt ret = "0";
			jBigInt c, d, e, remainder;
			size_t newlen = a.bitlen() > b.bitlen() ? a.bitlen() : b.bitlen();
			a.extendBitlen(newlen);
			b.extendBitlen(newlen);
			ret.extendBitlen(newlen);
			int low, high, mid;
			low = 0;
			high = b.maxLeftShiftLen();
			c = a;

			if (a.bitArr_[a.signBit()] == b.bitArr_[b.signBit()])
			{
				ret.bitArr_[ret.signBit()] = 0;
				while (1)
				{
					while (low <= high)
					{
						mid = (high + low) / 2;
						d = b;
						d << mid;
						e = c - d;
						if (d.bitArr_[d.signBit()] == e.bitArr_[e.signBit()] || e == 0)
							low = mid + 1;
						else
							high = mid - 1;
					}
					if (high != -1)
					{
						ret.bitArr_[high] = 1;
						d = b;
						d << high;
						c = c - d;
						low = 0;
						high--;
					}
					else
					{
						remainder = c;
						break;
					}
				}
			}
			else {
				ret.bitArr_[ret.signBit()] = 1;
				while (1)
				{
					while (low <= high)
					{
						mid = (high + low) / 2;
						d = b;
						d << mid;
						e = c + d;
						if (d.bitArr_[d.signBit()] != e.bitArr_[e.signBit()] || e == 0)
							low = mid + 1;
						else
							high = mid - 1;
					}
					if (high != -1)
					{
						ret.bitArr_[high] = 1;
						d = b;
						d << high;
						c = c + d;
						low = 0;
						high--;
					}
					else
					{
						remainder = c;
						break;
					}
				}
			}
			remainder.condenceBits();
			*this = std::move(remainder);
			return *this;
		}
		friend inline const jBigInt operator % (const jBigInt& lhs, const jBigInt& rhs) {
			jBigInt left(lhs);
			return std::move(left %= rhs);
		}
		jBigInt& operator << (size_t indent)
		{
			bitArr_._Insert_n(bitArr_.begin(), indent, 0);
			return *this;
		}
		jBigInt& operator >> (size_t indent)
		{
			if (indent >= bitlen() - 1) {
				bitArr_.clear();
				bitArr_.push_back(0);
				bitArr_.push_back(0);
			}
			else {
				toComplement();
				size_t rest = bitlen() - 1 - indent;
				std::vector<bool> tmp;
				tmp.resize(rest + 1);
				for (size_t i = indent; i < signBit(); ++i) {
					tmp[i - indent] = bitArr_[i];
				}
				tmp[signBit() - indent] = bitArr_[signBit()];
				bitArr_ = std::move(tmp);
				toComplement();
			}
			return *this;
		}
		friend inline const bool operator== (jBigInt lhs, jBigInt rhs) {
			lhs.condenceBits();
			rhs.condenceBits();
			if (lhs.bitlen() != rhs.bitlen())	return false;
			for (int i = 0; i < lhs.bitlen(); ++i) {
				if (lhs.bitArr_[i] != rhs.bitArr_[i])	return false;
			}
			return true;
		}
		const jIntString toIntString() const {
			jBigInt tmp = *this;
			tmp.toComplement();

			unsigned char retRadix = 2;
			bool retSign;
			if (tmp.bitArr_[tmp.signBit()] == 1)
				retSign = false;
			else
				retSign = true;
			std::vector<char> retVec;
			for (size_t i = 0; i < tmp.signBit(); ++i)
			{
				retVec.push_back(tmp.bitArr_[i]);
			}

			jIntString retStr(retVec, retSign, retRadix);
			retStr.changeRadix(10);
			return std::move(retStr);
		}
	private:
		std::vector<bool> bitArr_;	//in vector<bool>, bits are stored as 1-bit not 8-bits.
		inline size_t bitlen() const  {
			return bitArr_.size();
		}
		inline size_t signBit() const  {
			return bitArr_.size() - 1;
		}

		void toComplement() {
			if (bitArr_[signBit()] == 1) {
				std::vector<bool> tmp;
				tmp.resize(bitlen());
				tmp[signBit()] = 1;
				size_t i = 0;
				for (; i < signBit() && bitArr_[i] == 0; ++i)
				{
					tmp[i] = bitArr_[i];
				}
				if (i == signBit())
				{
					tmp[i] = 0; //complement of -0;
				}
				else {
					tmp[i] = bitArr_[i];
					for (++i; i < signBit(); ++i)
					{
						tmp[i] = !bitArr_[i]; 
					}
				}
				bitArr_ = std::move(tmp);
			}
			else {
				return;
			}
		}
		void toOpposite() {
			toComplement();
			bitArr_[signBit()] = !bitArr_[signBit()];
			toComplement();
		}
		void extendBitlen(size_t largerLen) {
			BOOST_ASSERT(largerLen >= bitlen(), "New Bit Length should be larger.");
			bool sign = bitArr_[signBit()];
			bitArr_.resize(largerLen, sign);
		}
		void condenceBits() {
			toComplement();
			int i, bitCut = 0;
			for (i = signBit() - 1; i >= 0 && bitArr_[i] == 0; --i)
			{
				++bitCut;
			}
			int newlen = bitlen() - bitCut;
			if (newlen == 1) newlen = 2; // In this case only sign bit left.
			std::vector<bool> tmp;
			tmp.resize(newlen);
			tmp.assign(bitArr_.begin(), bitArr_.begin() + newlen - 1);
			tmp.push_back(bitArr_[signBit()]);
			bitArr_ = std::move(tmp);
			toComplement();
		}
		size_t maxLeftShiftLen() const {
			jBigInt tmp = *this;
			tmp.toComplement();
			int i, k;
			for (i = signBit() - 1, k = 0; i >= 0 && tmp.bitArr_[i] == 0; --i, ++k);
			return k;
		}
	};

	std::ostream& operator << (std::ostream &output, const jBigInt &jbi) {
		output << jbi.toIntString();
		return output;
	}

}