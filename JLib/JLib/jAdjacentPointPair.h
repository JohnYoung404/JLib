#pragma once

#include <vector>
#include <algorithm>
#include <tuple>
#include <boost/optional.hpp>
#include "jUtility.h"
#include "jTestBase.h"

namespace jLib {

namespace jAlgorithm
{
    using jPoint = std::tuple<double, double>;
    using jPointPair = std::tuple<jPoint, jPoint>;

    extern const boost::optional<jPointPair> mostAdjacentPointPair(const std::vector<jPoint> & inputSet);
}
    
}

namespace jLib {
    class jAdjacentPointPairTest final : public jITestable {
    public:
        virtual void test() override {
            using namespace jAlgorithm;
            jITestable::test();
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
    };
}