#include <algorithm>
#include "jAdjacentPointPair.h"

namespace jLib
{

namespace jAlgorithm
{
    namespace
    {
        inline double __dst(const jPointPair &input)
        {
            using std::get;
            double fst_x = get<0>(get<0>(input));
            double fst_y = get<1>(get<0>(input));
            double snd_x = get<0>(get<1>(input));
            double snd_y = get<1>(get<1>(input));
            return (snd_x - fst_x) * (snd_x - fst_x) + (snd_y - fst_y)*(snd_y - fst_y);
        }
    }

    const boost::optional<jPointPair> mostAdjacentPointPair(const std::vector<jPoint> & inputSet)
    {
        if (inputSet.size() <= 1) return boost::none;
        if (inputSet.size() == 2) return std::make_tuple(inputSet[0], inputSet[1]);

        auto pointSetCopy = inputSet;

        std::sort(pointSetCopy.begin(), pointSetCopy.end(), [](jPoint &lhs, jPoint &rhs) {     // Firstly sort by points' x coordinate.
            return std::get<0>(lhs) < std::get<0>(rhs);
        });

        auto &lside = std::vector<jPoint>(pointSetCopy.begin(), pointSetCopy.begin() + pointSetCopy.size() / 2);    // divide point set to two half.
        auto &rside = std::vector<jPoint>(pointSetCopy.begin() + pointSetCopy.size() / 2, pointSetCopy.end());

        auto &lhs = mostAdjacentPointPair(lside);
        auto &rhs = mostAdjacentPointPair(rside);

        double lminDst = lhs ? __dst(lhs.value()) : DBL_MAX;
        double rminDst = rhs ? __dst(rhs.value()) : DBL_MAX;
        double minDst = std::min(lminDst, rminDst);

        auto ret = lminDst > rminDst ? rhs : lhs;      // most adjacent point pair exists in one of these two area or mid area.
        double lBorder_x = std::get<0>(pointSetCopy[pointSetCopy.size() / 2]) - minDst;
        double rBorder_x = std::get<0>(pointSetCopy[pointSetCopy.size() / 2]) + minDst;

        std::vector<jPoint> midArea;
        std::for_each(pointSetCopy.begin(), pointSetCopy.end(), [&midArea, &lBorder_x, &rBorder_x](auto &point) {
            if (std::get<0>(point) >= lBorder_x && std::get<0>(point) <= rBorder_x)  midArea.push_back(point);
        });

        std::sort(midArea.begin(), midArea.end(), [](jPoint &lhs, jPoint &rhs) {        // this time sort by y coordinate.
            return std::get<1>(lhs) < std::get<1>(rhs);
        });

        for (auto itr = midArea.begin(); itr != midArea.end(); ++itr)
        {
            size_t compare_times = 0;
            while (++compare_times > 6 || itr + compare_times != midArea.end())         // at most compare 6 times.
            {
                boost::optional<jPointPair> current = std::make_tuple(*itr, *(itr + compare_times));
                if (__dst(current.value()) < __dst(ret.value())) ret = current;
            }
        }
        return ret;
    }
}
    
}