#pragma once
#include <vector>
#include <utility>



namespace jLib {

	template<typename T>
	class jRange {
	public:
		void addRange(T beg, T end) {
			if (beg <= end) {
				rangeVec_.push_back(std::make_pair(beg, end));
			}
			condence_();
		}

		bool contains(T elem) {
			for (int i = 0 ; i < rangeVec_.size(); ++i)
			{
				if (rangeVec_[i].first <= elem && rangeVec_[i].second >= elem) {
					return true;
				}
			}
			return false;
		}

		bool cover(jRange otherRange) {
			return false;
		}

		bool interSect(jRange otherRange) {
			return false;
		}
	private:
		std::vector<std::pair<T, T> > rangeVec_;

		void condence_() {
			if (rangeVec_.size() == 1) return;
			std::vector<std::pair<T, T> > newRange;
			std::sort(rangeVec_.begin(),  rangeVec_.end(), 
				[](const std::pair<T, T> &lhs, const std::pair<T, T> &rhs)
			{
				return lhs.first < rhs.first;
			});
			for (int i = 0 ; i < rangeVec_.size(); ++i)
			{
				if (i + 1 < rangeVec_.size()) {
					if (rangeVec_[i].second >= rangeVec_[i + 1].second)
						newRange.push_back(rangeVec_[i]);
					else if (rangeVec_[i].second < rangeVec_[i + 1].first)
					{
						newRange.push_back(rangeVec_[i]);
						newRange.push_back(rangeVec_[i + 1]);
					}else
					{
						newRange.push_back(std::make_pair(rangeVec_[i].first, rangeVec_[i + 1].second));
					}
				}
			}
			rangeVec_ = std::move(newRange);
		}
	};

}