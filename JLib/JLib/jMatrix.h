// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/28/2017]
// Description : Matrix Library.
#pragma once
#include <initializer_list>
#include <boost/static_assert.hpp>
#include "jOpsMPL.h"
#include "jMPL.h"
#include "boost/assert.hpp"
#include "jVector.h"

namespace jGraphic {

	//////////////////////////////////////////////////////////////////////////
	// The index of a 3-degree matrix:
	//[ 00 01 02 ]
	//[ 10 11 12 ]
	//[ 20 21 22 ]
	//////////////////////////////////////////////////////////////////////////
	template <size_t Degree, typename Type>
	class jMat_base {
	public:
		enum {
			size = _mult<Degree, Degree>::value
		};
		inline static const jMat_base<Degree, Type> Zero() {
			return std::move(jMat_base<Degree, Type>());
		}
		inline static const jMat_base<Degree, Type> Identity() {
			jMat_base<Degree, Type> ret = jMat_base<Degree, Type>();
			for (int i = 0; i < Degree; ++i)
			{
				ret.mat_[i + i * Degree] = static_cast<Type>(1);
			}
			return std::move(ret);
		}

		jMat_base<Degree, Type>() {
			mat_ = new Type[size];
			memset(mat_, 0, size * sizeof(Type));
		}
		jMat_base<Degree, Type>(const std::initializer_list<Type> &initList) {
			BOOST_ASSERT(initList.size() == size);
			mat_ = new Type[size];
			int i = 0;
			for (auto &item : initList)
			{
				mat_[i] = item;
				i++;
			}
		}
		jMat_base<Degree, Type>(const jMat_base<Degree, Type> &rhs) {
			mat_ = new Type[size];
			memcpy(mat_, rhs.mat_, size * sizeof(Type));
		}
		jMat_base<Degree, Type>& operator= (const jMat_base<Degree, Type> &rhs) {
			if (this != &rhs) {
				memcpy(mat_, rhs.mat_, size * sizeof(Type));
			}
			return *this;
		}
		jMat_base<Degree, Type>(jMat_base<Degree, Type> &&rhs) {
			if (this != &rhs) {
				this->mat_ = rhs.mat_;
				rhs.mat_ = nullptr;
			}
		}
		jMat_base<Degree, Type>& operator= (jMat_base<Degree, Type> &&rhs) {
			if (this != &rhs) {
				this->mat_ = rhs.mat_;
				rhs.mat_ = nullptr;
			}
			return *this;
		}
		~jMat_base<Degree, Type>() {
			if (mat_ != nullptr)
			{
				delete[] mat_;
			}
		}

		template<size_t Degree, typename Type>
		friend const jMat_base<Degree, Type> operator+ (const jMat_base<Degree, Type> &lhs, const jMat_base<Degree, Type> &rhs);
		template<size_t Degree, typename Type>
		friend const jMat_base<Degree, Type> operator- (const jMat_base<Degree, Type> &lhs, const jMat_base<Degree, Type> &rhs);
		template<size_t Degree, typename Type>
		friend const jMat_base<Degree, Type> operator* (const jMat_base<Degree, Type> &lhs, const jMat_base<Degree, Type> &rhs);
		template<size_t Degree, typename Type>
		friend const jVector_base<Degree, Type> operator* (const jMat_base<Degree, Type> &lmat, const jVector_base<Degree, Type> &rvec);

		inline Type& RefOfPos(int i, int j) {
#ifdef _DEBUG
			BOOST_ASSERT(i < Degree && i >= 0 && j < Degree && j >= 0);
#endif
			return mat_[i * Degree + j];
		}
		inline const Type& RefOfPos(int i, int j) const {
#ifdef _DEBUG
			BOOST_ASSERT(i < Degree && i >= 0 && j < Degree && j >= 0);
#endif
			return mat_[i * Degree + j];
		}

		template<size_t Degree, typename Type>
		friend const jMat_base<Degree, Type> inverse(const jMat_base<Degree, Type> &rhs);

		template<size_t Degree, typename Type>
		friend const Type determinant(const jMat_base<Degree, Type> &rhs);

		template<size_t Degree, typename Type>
		friend const jMat_base<Degree, Type> adjoint(const jMat_base<Degree, Type> &rhs);

		friend std::ostream& operator<< (std::ostream& os, const jMat_base<Degree, Type> &outMat) {
			for (int i = 0; i < Degree; ++i)
			{
				for (int j = 0; j < Degree; ++j)
				{
					os << outMat.RefOfPos(i, j) << " ";
				}
				std::cout << "\n";
			}
			return os;
		}
	private:
		Type* mat_;
	};

	////////////////////////////////////////////////////////////////////////// Implementation of operations
	template <size_t Degree, typename Type>
	const jMat_base<Degree, Type> operator+ (const jMat_base<Degree, Type> &lhs, const jMat_base<Degree, Type> &rhs) {
		jMat_base<Degree, Type> ret = lhs;
		for (int i = 0; i < jMat_base<Degree, Type>::size; ++i) {
			ret.mat_[i] += rhs.mat_[i];
		}
		return std::move(ret);
	};

	template <size_t Degree, typename Type>
	const jMat_base<Degree, Type> operator- (const jMat_base<Degree, Type> &lhs, const jMat_base<Degree, Type> &rhs) {
		jMat_base<Degree, Type> ret = lhs;
		for (int i = 0; i < jMat_base<Degree, Type>::size; ++i) {
			ret.mat_[i] -= rhs.mat_[i];
		}
		return std::move(ret);
	}

	template <size_t Degree, typename Type>
	const jMat_base<Degree, Type> operator* (const jMat_base<Degree, Type> &lhs, const jMat_base<Degree, Type> &rhs) {
		jMat_base<Degree, Type> ret = jMat_base<Degree, Type>::Zero();
		for (int i = 0; i < Degree; ++i) {
			for (int j = 0; j < Degree; ++j) {
				for (int k = 0; k < Degree; ++k) {
					ret.RefOfPos(i, j) += lhs.RefOfPos(i, k) * rhs.RefOfPos(k, j);
				}
			}
		}
		return std::move(ret);
	}

	template<size_t Degree, typename Type>
	const Type determinant(const jMat_base<Degree, Type> &rhs) {
		return determinantOfMatrix<Degree, Type>::invoke(rhs);
	}

	template<size_t Degree, typename Type>
	const jMat_base<Degree, Type> adjoint(const jMat_base<Degree, Type> &rhs) {
		auto ret = jMat_base<Degree, Type>::Zero();
		for (int i = 0; i < Degree; ++i)
		{
			for (int j = 0; j < Degree; ++j) 
			{
				auto tmp = jMat_base<Degree - 1, Type>::Zero();
				for (int m = 0; m < Degree - 1; ++m) {
					for (int n = 0; n < Degree - 1; ++n) {
						tmp.RefOfPos(m, n) = rhs.RefOfPos((m < i ? m : m + 1), (n < j ? n : n + 1));
					}
				}
				ret.RefOfPos(j, i) = ((i + j) % 2 == 0 ? 1 : -1) * determinant(tmp);
			}
		}
		return std::move(ret);
	}

	template<size_t Degree, typename Type>
	const jMat_base<Degree, Type> inverse(const jMat_base<Degree, Type> &rhs) {
		Type det = determinant(rhs);
		auto ret = adjoint(rhs);
		for (int i = 0 ; i < Degree; ++i)
		{
			for (int j = 0; j < Degree; ++j)
			{
				ret.RefOfPos(i, j) = ret.RefOfPos(i, j) / det;
			}
		}
		return std::move(ret);
	}

    //////////////////////////////////////////////////////////////////////////
    //向量和矩阵的列乘法
    // @  @  @     @
    // @  @  @  x  @  
    // @  @  @     @
    //////////////////////////////////////////////////////////////////////////
	template<size_t Degree, typename Type>
	const jVector_base<Degree, Type> operator* (const jMat_base<Degree, Type> &lmat, const jVector_base<Degree, Type> &rvec) {
		auto ret = std::move(jVector_base<Degree, Type>::Zero());
		for (int i = 0 ; i < Degree; ++i)
		{
			for (int j = 0; j < Degree; ++j)
			{
				ret[i] += lmat.RefOfPos(i, j) * rvec[j];
			}
		}
		return std::move(ret);
	}

    //////////////////////////////////////////////////////////////////////////
    //向量和矩阵的行乘法
    //             @  @  @
    // @  @  @  x  @  @  @ 
    //             @  @  @
    //////////////////////////////////////////////////////////////////////////
    template<size_t Degree, typename Type>
    const jVector_base<Degree, Type> operator* (const jVector_base<Degree, Type> &lvec, const jMat_base<Degree, Type> &rmat) {
        auto ret = std::move(jVector_base<Degree, Type>::Zero());
        for (int i = 0; i < Degree; ++i)
        {
            for (int j = 0; j < Degree; ++j)
            {
                ret[i] += rmat.RefOfPos(j, i) * lvec[j];
            }
        }
        return std::move(ret);
    }

	////////////////////////////////////////////////////////////////////////// Declaration of jMat_4
	template<typename Type>
	using jMat_4 = jMat_base<4, Type>;
}
