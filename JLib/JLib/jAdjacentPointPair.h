#pragma once

// Author : John Young
// Contact : JohnYoung404@outlook.com
// Description : Implement an algorithm that can find most adjacant point pair in a point set in O(n*log n).

#include <vector>
#include <tuple>
#include <boost/optional.hpp>
#include "jUtility.h"

NAME_SPACE_BEGIN(jLib)
NAME_SPACE_BEGIN(jAlgorithm)

using jPoint = std::tuple<double, double>;
using jPointPair = std::tuple<jPoint, jPoint>;

extern const boost::optional<jPointPair> mostAdjacentPointPair(const std::vector<jPoint> & inputSet);

NAME_SPACE_END
NAME_SPACE_END


////////////// Unit Test //////////////
#include "jTestBase.h"

JTEST_BEGIN(jAdjacentPointPairTest)
{
    using namespace jAlgorithm;
    std::vector<jPoint> pointSet = {
        jPoint{ 0.0, 0.0 }, jPoint{ 0.0, 2.0 }, jPoint{ 1.0, 0.0 },
        jPoint{ 0.5, 0.5 }, jPoint{ 0.2, 1.3 }, jPoint{ 0.7, 0.3 },
        jPoint{ 0.51, 0.49 }, jPoint{ 0.23, 1.27 }
    };
    const auto & closest = mostAdjacentPointPair(pointSet);
    if (closest)
    {
        std::cout << "(" << std::get<0>(std::get<0>(closest.value())) << ", " << std::get<1>(std::get<0>(closest.value())) << ")" << std::endl;
        std::cout << "(" << std::get<0>(std::get<1>(closest.value())) << ", " << std::get<1>(std::get<1>(closest.value())) << ")" << std::endl;
    }
}
JTEST_END