#pragma once
#include <initializer_list>
#include <boost/assert.hpp>
#include <cmath>
#include <array>
#include <cstring>
#include "jTypeTraits.h"

namespace jLib{
namespace jContainer {

template <typename Type, size_t Degree>
class jVecBase
{
public:
    constexpr jVecBase() : _inner_vec{}
    {
    }
    //constexpr jVecBase(Type ... inputs) : _inner_vec{ inputs... }
    //{
    //}
    constexpr jVecBase(const std::array<Type, Degree> &arrayInput) : _inner_vec(arrayInput)
    {
    }
    constexpr jVecBase(const Type(&arrayInput)[Degree]) : _inner_vec(arrayInput)
    {
    }
    jVecBase(const Type &val)
    {
        _inner_vec.assign(val);
    }
    //constexpr jVecBase(std::initializer_list<Type> init_list) : _inner_vec(std::array<Type, Degree>(init_list))
    //{
    //    //_inner_vec = {};
    //    //auto itr_inner = _inner_vec.begin();
    //    //for (auto itr_input = init_list.begin(); itr_input != init_list.end(); ++itr_input, ++itr_inner)
    //    //{
    //    //    *itr_inner = *itr_input;
    //    //}
    //}

    jVecBase(const jVecBase &rhs)
    {
        if (std::is_trivially_copyable<Type>::value)
            std::memcpy(_inner_vec.data(), rhs._inner_vec.data(), Degree * sizeof(Type));
        else
            _inner_vec = rhs._inner_vec;
    }
    constexpr const Type & at(size_t pos) const {
        return _inner_vec.at(pos);
    }
    Type & at(size_t pos)
    {
        return _inner_vec.at(pos);
    }

public:
    inline static constexpr size_t dim(){
        return Degree;
    }
    inline static const jVecBase zero()
    {
        jConstrain_sentence_is_arithmetic(Type);
        return jVecBase(0);
    }
    inline static const jVecBase identity()
    {
        jConstrain_sentence_is_arithmetic(Type);
        return jVecBase(1);
    }
    //inline static constexpr std::array<Type, Degree> make_array()
private:
    std::array<Type, Degree> _inner_vec;
};

template <typename Type, size_t Degree>
class jVecBase2 
{
public:
    inline static constexpr size_t dim() {
        return Degree;
    }
    inline constexpr static const jVecBase2 zero()
    {
        jConstrain_sentence_is_arithmetic(Type);
        return jVecBase();
    }
    constexpr const Type & at(size_t pos) const {
        return _inner_vec.at(pos);
    }
    std::array<Type, Degree> _inner_vec;
    //inline static const jVecBase identity()
    //{
    //    jConstrain_sentence_is_arithmetic(Type);
    //    return jVecBase(1);
    //}
};


}
}

#include "jTestBase.h"
#include "jVectorTraits.h"
#include "jTupleMPL.h"
namespace jLib {
    class jVecBaseTest final : public jITestable {
    public:
        virtual void test() override {
            constexpr jContainer::jVecBase2<int, 4> v = { 1, 2, 3, 4};
            ////jContainer::jVecBase<float, 3> v = {1, 2};
            //const auto & v2 = jContainer::jVecBase<float, 3>::zero();
            //auto v3 = jContainer::jVecBase<int, 3>::identity();
            //testConstNumber<jMPL::jVecTraits::is_vec<decltype(v2)>::value> out1;
            ////testConstNumber<decltype(v)::dim()> out2;
            //testConstNumber<decltype(v3)::dim()> out3;
            //constexpr auto vx = std::array<int, 4> {1, 2, 3, 4};
            //testConstNumber<vx.at(1)> out4;
            //constexpr auto constV = jContainer::jVecBase<int, 4>(); // Intellisense Bug here.
            //testConstNumber<constV.at(1)> out5;
            //constexpr jContainer::jVecBase<int, 4> constV2 = { { 1, 2, 3, 4 } };
            ////std::initializer_list<int> il = { 1, 2 ,3, 4 };
            ////std::array<int, 4> = il;
            constexpr auto k = jMPL::make_tuple_n<5>(6);    //Intellisense Bug here.
            testConstNumber<v.at(3)> out6;
        }
    };
}

template<size_t Degree, typename Type>
class jVector_base {
	template<size_t U, typename M>
	friend class jVector_base;
public:
	inline static const jVector_base<Degree, Type> Zero() {
		return std::move(jVector_base<Degree, Type>());
	}
	inline static const jVector_base<Degree, Type> Identity() {
		jVector_base<Degree, Type> ret = jVector_base<Degree, Type>();
		for (int i = 0; i < Degree; ++i) {
			ret.vec_[i] = static_cast<Type>(1);
		}
		return std::move(ret);
	}

	jVector_base<Degree, Type>() {
		vec_ = new Type[Degree];
		memset(vec_, 0, Degree * sizeof(Type));
	}
	jVector_base<Degree, Type>(const std::initializer_list<Type> &initList) {
#ifdef _DEBUG
		BOOST_ASSERT(initList.size() == Degree);
#endif
		vec_ = new Type[Degree];
		int i = 0;
		for (auto item : initList) {
			vec_[i] = item;
			++i;
		}
	}
	jVector_base<Degree, Type> (const jVector_base<Degree, Type> &rhs) {
		vec_ = new Type[Degree];
		memcpy(vec_, rhs.vec_, Degree * sizeof(Type));
	}
	jVector_base<Degree, Type>& operator=(const jVector_base<Degree, Type> &rhs) {
		if (this != &rhs) {
			memcpy(vec_, rhs.vec_, Degree * sizeof(Type));
		}
		return *this;
	}
    jVector_base<Degree, Type>(jVector_base<Degree, Type> &&rhs) : vec_(rhs.vec_)
    {
        rhs.vec_ = nullptr;
    }
	jVector_base<Degree, Type>& operator= (jVector_base<Degree, Type> &&rhs) {
		if (this != &rhs) {
			this->vec_ = rhs.vec_;
			rhs.vec_ = nullptr;
		}
		return *this;
	}
	~jVector_base() {
		if (vec_ != nullptr)
		{
			delete[] vec_;
		}
	}

	friend const jVector_base<Degree, Type>  operator+ (const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs) {
		jVector_base<Degree, Type> ret = lhs;
		for (int i = 0 ; i < Degree ; ++i)
		{
			ret.vec_[i] += rhs.vec_[i];
		}
		return std::move(ret);
	}

	friend const jVector_base<Degree, Type>  operator- (const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs) {
		jVector_base<Degree, Type> ret = lhs;
		for (int i = 0; i < Degree; ++i)
		{
			ret.vec_[i] -= rhs.vec_[i];
		}
		return std::move(ret);
	}

	friend const jVector_base<Degree, Type>  operator* (const jVector_base<Degree, Type> &lhs, const Type k) {
		jVector_base<Degree, Type> ret = lhs;
		for (int i = 0; i < Degree; ++i)
		{
			ret.vec_[i] *= k;
		}
		return std::move(ret);
	}

	friend const jVector_base<Degree, Type>  operator* (const Type k, const jVector_base<Degree, Type> &rhs) {
		jVector_base<Degree, Type> ret = rhs;
		for (int i = 0; i < Degree; ++i)
		{
			ret.vec_[i] *= k;
		}
		return std::move(ret);
	}

	const Type& operator[] (size_t index) const {
#ifdef _DEBUG
		BOOST_ASSERT(index < Degree);
#endif
		return this->vec_[index];
	}
	Type& operator[](size_t index) {
#ifdef _DEBUG
		BOOST_ASSERT(index < Degree);
#endif
		return this->vec_[index];
	}

	template<size_t Degree, typename Type>
	friend const jVector_base<Degree, Type> doCross(const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs);

	template<size_t Degree, typename Type>
	friend const jVector_base<Degree, Type> Lerp(const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs, float interpolator);

	template<size_t Degree, typename Type>
	inline friend const float cosTheta(const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs);

	template<size_t Degree, typename Type>
	inline friend const float theta(const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs);

	friend const Type  operator* (const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs) {
		Type ret = 0;
		for (int i = 0; i < Degree; ++i)
		{
			ret += lhs.vec_[i] * rhs.vec_[i];
		}
		return ret;
	}

	friend std::ostream& operator<< (std::ostream &os, const jVector_base<Degree, Type> &outVec) {
		os << "[";
		for (int i = 0; i < Degree; ++i)
		{
			os << outVec.vec_[i] << ", ";
		}
		os << "\b\b]" << std::endl;
		return os;
	}

	inline const Type SquareLength() const {
		return (*this) * (*this);
	}

	inline const float Length() const {
		return sqrt(SquareLength());
	}

	const jVector_base<Degree, Type> Normalize() const {
		jVector_base<Degree, Type> ret = *this;
		float len = Length();
		for (int i = 0; i < Degree; ++i)
		{
			ret.vec_[i] /= len;
		}
		return std::move(ret);
	};
	
private:
	Type * vec_;
};

template<typename Type>
using jVec_3 = jVector_base<3, Type>;

using jPoint2D = jVector_base<2, float>;

using jPoint3D = jVector_base<3, float>;

template<size_t Degree, typename Type>
const jVector_base<Degree, Type>  doCross(const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs) {
	BOOST_STATIC_ASSERT(Degree == 3);
	jVector_base<Degree, Type> ret = jVector_base<Degree, Type>();
	ret.vec_[0] = lhs.vec_[1] * rhs.vec_[2] - lhs.vec_[2] * rhs.vec_[1];
	ret.vec_[1] = lhs.vec_[2] * rhs.vec_[0] - lhs.vec_[0] * rhs.vec_[2];
	ret.vec_[2] = lhs.vec_[0] * rhs.vec_[1] - lhs.vec_[1] * rhs.vec_[0];
	return std::move(ret);
}

template<size_t Degree, typename Type>
const jVector_base<Degree, Type>  Lerp(const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs, float interpolater) {
	jVector_base<Degree, Type> ret = jVector_base<Degree, Type>();
	for (int i = 0 ; i < Degree; ++i)
	{
		ret.vec_[i] = lhs.vec_[i] + interpolater * (rhs.vec_[i] - lhs.vec_[i]);
	}
	return std::move(ret);
}

template<size_t Degree, typename Type>
const float cosTheta(const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs) {
	float div = (lhs.Length() * rhs.Length());
	BOOST_ASSERT(div > 0);
	return static_cast<float>(lhs * rhs) / div;
};

template<size_t Degree, typename Type>
const float theta(const jVector_base<Degree, Type> &lhs, const jVector_base<Degree, Type> &rhs) {
	return (float)acosf(cosTheta(lhs, rhs)) * 180 / PI;
};