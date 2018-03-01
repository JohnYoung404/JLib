#include <iostream>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include "jBigInt.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jNum)

jBigInt::jBigInt(const std::string &initstring)
{
	try
	{
		jIntString jis = initstring;
		jis.changeRadix(2);
		for (auto i : jis.numVecRef())
		{
			bitArr_.push_back(i == 1);
		}
		if (jis.sign() == true)
			bitArr_.push_back(0);
		else
			bitArr_.push_back(1);
		toComplement();
	}
	catch (const std::invalid_argument&)
	{
		throw std::invalid_argument("Invalid number string Input.");
	}
}

jBigInt::jBigInt(int i) 
{
	*this = std::move(jBigInt(boost::lexical_cast<std::string>(i)));
}

jBigInt::jBigInt(jBigInt && rhs) noexcept
{
	bitArr_ = std::move(rhs.bitArr_);
}

jBigInt::jBigInt(const jBigInt &rhs) : bitArr_(rhs.bitArr_) {}

const jBigInt& jBigInt::operator=(const jBigInt & rhs) {
	if (this != &rhs) {
		bitArr_ = rhs.bitArr_;
	}
	return *this;
}

const jBigInt& jBigInt::operator=(jBigInt && rhs) noexcept {
	if (this != &rhs)
	{
		bitArr_ = std::move(rhs.bitArr_);
	}
	return *this;
}

jBigInt& jBigInt::operator+= (const jBigInt& rhs) {
	size_t newlen = 1 + (rhs.bitlen() > bitlen() ? rhs.bitlen() : bitlen());
	jBigInt ext_rhs(rhs);
	ext_rhs.extendBitlen(newlen);
	this->extendBitlen(newlen);
	size_t i, t, carryflag;
	for (carryflag = i = 0; i < bitlen(); ++i) {
		t = ext_rhs.bitArr_[i] + bitArr_[i] + carryflag;
		bitArr_[i] = (t % 2) == 1;
		carryflag = t > 1 ? 1 : 0;
	}
	condenceBits();
	return *this;
}

jBigInt& jBigInt::operator-= (const jBigInt& rhs)
{
	jBigInt oppo_rhs(rhs);
	oppo_rhs.toOpposite();
	*this += oppo_rhs;
	return *this;
}

jBigInt& jBigInt::operator*= (const jBigInt& rhs)        //implement Booth Algorithm.
{
	jBigInt neg_lhs(*this);
	neg_lhs.toOpposite();
	jBigInt ret = "0";
	int i;
	for (i = static_cast<int>(rhs.signBit()); i > 0 && rhs.bitArr_[i] == rhs.bitArr_[i - 1]; i--);
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

jBigInt& jBigInt::operator/= (const jBigInt& rhs)        //implement Booth Algorithm.
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
	high = static_cast<int>(b.maxLeftShiftLen());
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

jBigInt& jBigInt::operator%= (const jBigInt& rhs)        //implement Booth Algorithm.
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
	high =static_cast<int>(b.maxLeftShiftLen());
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

jBigInt& jBigInt::operator << (size_t indent)
{
	bitArr_._Insert_n(bitArr_.begin(), indent, 0);
	return *this;
}

jBigInt& jBigInt::operator >> (size_t indent)
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

const jIntString jBigInt::toIntString() const {
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
	return retStr;
}

void jBigInt::toComplement() {
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

void jBigInt::toOpposite() {
	toComplement();
	bitArr_[signBit()] = !bitArr_[signBit()];
	toComplement();
}

void jBigInt::extendBitlen(size_t largerLen) {
#ifdef _DEBUG
	BOOST_ASSERT_MSG(largerLen >= bitlen(), "New Bit Length should be larger.");
#endif
	bool sign = bitArr_[signBit()];
	bitArr_.resize(largerLen, sign);
}

void jBigInt::condenceBits() {
	toComplement();
	int i, bitCut = 0;
	for (i = static_cast<int>(signBit()) - 1; i >= 0 && bitArr_[i] == 0; --i)
	{
		++bitCut;
	}
	int newlen = static_cast<int>(bitlen()) - bitCut;
	if (newlen == 1) newlen = 2; // In this case only sign bit left.
	std::vector<bool> tmp;
	tmp.resize(newlen);
	tmp.assign(bitArr_.begin(), bitArr_.begin() + newlen - 1);
	tmp.push_back(bitArr_[signBit()]);
	bitArr_ = std::move(tmp);
	toComplement();
}

const size_t jBigInt::maxLeftShiftLen() const {
	jBigInt tmp = *this;
	tmp.toComplement();
	int i, k;
	for (i = static_cast<int>(signBit()) - 1, k = 0; i >= 0 && tmp.bitArr_[i] == 0; --i, ++k);
	return k;
}

std::ostream& operator << (std::ostream &output, const jBigInt &jbi) {
	output << jbi.toIntString();
	return output;
}

NAME_SPACE_END
NAME_SPACE_END