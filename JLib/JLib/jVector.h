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
    constexpr jVecBase<Type, Degree>()
    {
        if (std::is_scalar<Type>::value)
            std::memset(_inner_vec.data(), 0, Degree * sizeof(Type));
        else
            _inner_vec = {};
    }
    constexpr jVecBase<Type, Degree>(const Type &val)
    {
        _inner_vec.assign(val);
    }
    jVecBase<Type, Degree>(const std::initializer_list<Type> &init_list)
    {
        _inner_vec = {};
        auto itr_inner = _inner_vec.begin();
        for (auto itr_input = init_list.begin(); itr_input != init_list.end(); ++itr_input, ++itr_inner)
        {
            *itr_inner = *itr_input;
        }
    }
    jVecBase<Type, Degree>(std::initializer_list<Type> &&init_list)
    {
        _inner_vec = {};
        auto itr_inner = _inner_vec.begin();
        for (auto itr_input = init_list.begin(); itr_input != init_list.end(); ++itr_input, ++itr_inner)
        {
            if (std::is_scalar<Type>::value)
                *itr_inner = *itr_input;
            else
                *itr_inner = std::move(*itr_input);
        }
    }
    jVecBase<Type, Degree>(const jVecBase<Type, Degree> &rhs) {
        if (std::is_trivially_copyable<Type>::value)
            std::memcpy(_inner_vec.data(), rhs._inner_vec.data(), Degree * sizeof(Type));
        else
            _inner_vec = rhs._inner_vec;
    }


public:
    inline static  jVecBase<Type, Degree> zero()
    {
        jConstrain_sentence_is_arithmetic(Type);
        return jVecBase<Type, Degree>(0);
    }
    inline static constexpr jVecBase<Type, Degree> identity()
    {
        jConstrain_sentence_is_arithmetic(Type);
        return jVecBase<Type, Degree>(1);
    }
private:
    template <typename Type, size_t Degree>
    friend std::ostream& operator << (std::ostream &output, const jVecBase<Type, Degree> &vec);

    std::array<Type, Degree> _inner_vec;
};

template <typename Type, size_t Degree>
std::ostream& operator << (std::ostream &output, const jVecBase<Type, Degree> &vec)
{
    for (auto & v : vec._inner_vec)
    {
        output << v << " ";
    }
    output << std::endl;
    return output;
}

}
}

#include "jTestBase.h"
namespace jLib {
    class jVecBaseTest final : public jITestable {
    public:
        virtual void test() override {
            jContainer::jVecBase<float, 3> v = {1, 2};
            std::cout << v << jContainer::jVecBase<int, 5>::zero();
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