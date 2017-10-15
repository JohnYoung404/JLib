#pragma once
#include <vector>
#include <utility>
#include <cstdlib>
#include <iostream>
#include "boost/assert.hpp"
#include "jTestBase.h"

namespace jLib {

	///////////////////////////////////
	// represent a segment of range.
	///////////////////////////////////
	template<typename T>
	class jsegmentRange {
	public:
		jsegmentRange(T low, T high, bool left_closed = true, bool right_closed = true)
			:left_closed_(left_closed)
			, right_closed_(right_closed)
		{
#ifdef _DEBUG
			BOOST_ASSERT(low <= high);
			if (low == high) {
				BOOST_ASSERT(left_closed_ == true);
				BOOST_ASSERT(right_closed_ == true);
			}
#endif
			segRange_ = std::move(std::make_pair(low, high));
		}

		template <typename T>
		static const bool mergable(const jsegmentRange<T> & lhs, const jsegmentRange<T> &rhs) {
			if (lhs.segRange_.second < rhs.segRange_.first || lhs.segRange_.first > rhs.segRange_.second)
				return false;
			else if (lhs.segRange_.second == rhs.segRange_.first) {
				if (lhs.right_closed_ == false && rhs.left_closed_ == false)
					return false;
				else
					return true;
			}
			else {
				return true;
			}
		}

		const std::vector<jsegmentRange<T> > merge(const jsegmentRange<T> &rhs) const  {
			std::vector<jsegmentRange<T> > ret;
			if (!mergable(*this, rhs)) {
				ret.push_back(*this);
				ret.push_back(rhs);
				return std::move(ret);
			}
			else {
				T left_min, right_max;
				bool left_closed, right_closed;

				if (this->segRange_.first > rhs.segRange_.first)
				{
					left_min = rhs.segRange_.first;
					left_closed = rhs.left_closed_;
				}
				else if (this->segRange_.first == rhs.segRange_.first) {
					left_min = this->segRange_.first;
					left_closed = this->left_closed_ || rhs.left_closed_;
				}
				else if (this->segRange_.first < rhs.segRange_.first)
				{
					left_min = this->segRange_.first;
					left_closed = this->left_closed_;
				}

				if (this->segRange_.second > rhs.segRange_.second)
				{
					right_max = this->segRange_.second;
					right_closed = this->right_closed_;
				}
				else if (this->segRange_.second == rhs.segRange_.second) {
					right_max = this->segRange_.second;
					right_closed = this->right_closed_ || rhs.right_closed_;
				}
				else if (this->segRange_.second < rhs.segRange_.second)
				{
					right_max = rhs.segRange_.second;
					right_closed = rhs.right_closed_;
				}

				ret.push_back(std::move(jsegmentRange<T>(left_min, right_max, left_closed, right_closed)));
			}
			return std::move(ret);
		}

		const bool contains(T val) const  {
			if (val < segRange_.first || val > segRange_.second)
			{
				return false;
			}
			if (val > segRange_.first && val < segRange_.second)
			{
				return true;
			}
			if (val == segRange_.first && left_closed_) {
				return true;
			}
			if (val == segRange_.second && right_closed_)
			{
				return true;
			}
			return false;
		}

		const bool intersected(const jsegmentRange& other) {
			if (segRange_.first == other.segRange_.second)
			{
				if (left_closed_ && other.right_closed_)
				{
					return true;
				}
				return false;
			}else if (segRange_.second == other.segRange_.first)
			{
				if (right_closed_ && other.left_closed_) 
				{
					return true;
				}
				return false;
			}
			else if (segRange_.first > other.segRange_.second || segRange_.second < other.segRange_.first) {
				return false;
			}
			else {
				return true;
			}
		}

		inline const T & getFrom() const {
			return segRange_.first;
		};

		inline const T & getTo() const {
			return segRange_.second;
		};

		friend std::ostream& operator << (std::ostream &os, const jsegmentRange<T> & out) {
			if (out.left_closed_)
			{
				os << "[";
			}
			else {
				os << "(";
			}
			os << out.segRange_.first << ", " << out.segRange_.second;
			if (out.right_closed_)
			{
				os << "]";
			}
			else {
				os << ")";
			}
			return os;
		}

	private:
		std::pair<T, T> segRange_;
		bool left_closed_, right_closed_;
	};

	///////////////////////////////////
	// Union of segment-ranges
	///////////////////////////////////
	template<typename T>
	class jRange {
	public:
		void addRange(T from, T to, bool left_close = true, bool right_close = true) {
			if (from <= to) {
				if (from == to && (left_close != true || right_close != true))
				{
					return;
				}
				condence_(std::move(jsegmentRange<T>(from, to, left_close, right_close)));
			}
		}

		const bool contains(T elem) const {
			for (int i = 0 ; i < rangeVec_.size(); ++i)
			{
				if (rangeVec_[i].contains(elem)) {
					return true;
				}
			}
			return false;
		}

		const bool intersected(jRange<T> otherRange) const {
			for (auto i : rangeVec_)
			{
				for (auto j : otherRange.rangeVec_) {
					if (i.intersected(j))
					{
						return true;
					}
				}
			}
			return false;
		}

		const jRange<T> merge(const jRange<T> &other) const {
			jRange<T> ret = *this;
			for (auto i : other.rangeVec_)
			{
				ret.condence_(i);
			}
			return std::move(ret);
		}

		friend std::ostream& operator << (std::ostream &os, const jRange & r) {
			if (r.rangeVec_.size() == 0)
			{
				return os;
			}
			auto t = r;
			t.sequential();
			for (auto i : t.rangeVec_)
			{
				os << i;
				os << "->";
			}
			os << "\b"  " "  "\b";
			os << "\b"  " "  "\b";
			return os;
		}
	private:
		std::vector<jsegmentRange<T> > rangeVec_;

		void condence_(jsegmentRange<T> toAdd) {
			bool condece_begin = false;
			std::vector<jsegmentRange<T> > newRange;
			sequential();
			for (int i = 0; i < rangeVec_.size(); ++i)
			{
				auto rangeList = rangeVec_[i].merge(toAdd);
				if (rangeList.size() == 2 && condece_begin == false)
				{
					newRange.push_back(rangeVec_[i]);
					continue;
				}
				if (rangeList.size() == 1)
				{
					condece_begin = true;
					toAdd = rangeList[0];
					continue;
				}
				if (rangeList.size() == 2 && condece_begin == true)
				{
					for (i ;i < rangeVec_.size(); ++i)
					{
						newRange.push_back(rangeVec_[i]);
					}
					break;
				}
			}
			newRange.push_back(toAdd);
			rangeVec_ = std::move(newRange);
		}

		void sequential() {
			std::sort(rangeVec_.begin(), rangeVec_.end(),
				[](const jsegmentRange<T> &lhs, const jsegmentRange<T> &rhs)
			{
				return lhs.getFrom() < rhs.getFrom();
			});
		}

	};

	class jRangeTest final : public jITestable {
	public:
		virtual void test() override {
            jITestable::test();

			jLib::jRange<int> r, m;
            r.addRange(-1, 5);
            std::cout << "r.addRange [-1, 5] : " << r << std::endl;
            r.addRange(7, 9, true, false);
            std::cout << "r.addRange [7, 9) : " << r << std::endl;
            r.addRange(3, 6, true, false);
            std::cout << "r.addRange [3, 6) : " << r << std::endl;

            std::cout << "r.contains 6 : " << r.contains(6) << std::endl;
            std::cout << "r.contains -1 : " << r.contains(-1) << std::endl;
            std::cout << "r.contains 8 : " << r.contains(8) << std::endl;

            for (int i = 0; i < 20; ++i)
            {
                r.addRange(i, i + 1, false, false);
            }
            std::cout << "r.add (0,1),(1,2)...(19,20) : " << r << std::endl;

		}
	};
}