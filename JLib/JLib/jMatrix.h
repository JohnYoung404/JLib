// Author : John Young
// Contact : JohnYoung404@outlook.com
// Date : [9/28/2017]
// Description : Matrix Library.
#pragma once
#include <initializer_list>
#include <boost/static_assert.hpp>
#include "jOpsMPL.h"
#include <bitset>

namespace jGraphic {

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

		inline Type& RefOfPos(int i, int j) {
			return mat_[i * Degree + j];
		}
		inline const Type& RefOfPos(int i, int j) const {
			return mat_[i * Degree + j];
		}

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
		jMat_base<Degree, Type>() {
			mat_ = new Type[size];
			memset(mat_, 0, size * sizeof(Type));
		}
		Type* mat_;
	};

	////////////////////////////////////////////////////////////////////////// Declaration of jMat_4
	template<typename Type>
	using jMat_4 = jMat_base<4, Type>;


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
}
