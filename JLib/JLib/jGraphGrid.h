#pragma once
#include <tuple>
#include <functional>
#include <cmath>
#include <ctime>
#include <unordered_set>
#include <array>
#include "jGraphSearch.h"
#include "jGrid.h"
#include "jHash.h"

namespace jGame
{

using jPosNode = std::tuple<int, int>;

class jPositionGraph : public jGraphLib::jGraph<jPosNode>
{
public:
    jPositionGraph(int initWidth, int initHeight) : _width(initWidth), _height(initHeight), _DIRS{ jPosNode{ 1, 0 }, jPosNode{ 0, -1 }, jPosNode{ -1, 0 }, jPosNode{ 0, 1 } } { }
	
    const std::vector<jPosNode>& neibours(jPosNode InputNode) override
    {
        if (_cachedNeibourMap.count(InputNode))
        {
            return _cachedNeibourMap[InputNode];
        }
		int x, y, dx, dy;
		std::tie(x, y) = InputNode;
		std::vector<jPosNode> results;

		for (auto &dir : _DIRS) {
			std::tie(dx, dy) = dir;
			jPosNode next(x + dx, y + dy);
			if (in_bounds(next) && passable(next)) {
				results.push_back(next);
			}
		}
        _cachedNeibourMap[InputNode] = results;
		return _cachedNeibourMap[InputNode];
    }

	const float dist(jPosNode from, jPosNode to) override
	{
		if (in_bounds(from) && in_bounds(to))
		{
			if (passable(to) && passable(from))
			{
                float dst = static_cast<float>(abs(std::get<0>(from) - std::get<0>(to)) + abs(std::get<1>(from) - std::get<1>(to)));
				return from == to ? 0 : (std::find(neibours(from).begin(), neibours(from).end(), to) != neibours(from).end()) ? dst : FLT_MAX;
			}
		}
		return FLT_MAX;
	}

	const float heuristic(jPosNode a, jPosNode b) override {
        int x1, y1, x2, y2;
        std::tie(x1, y1) = a;
        std::tie(x2, y2) = b;
        return static_cast<float>(abs(x1 - x2) + abs(y1 - y2)) * 1.1f;   //增大权重，优先往离目标近的方向搜
	}

	inline void addWall(jPosNode input)
	{
		_walls.emplace(input);
	}

private:
    int _width, _height;
	std::unordered_set<jPosNode> _walls;
    std::unordered_map<jPosNode, std::vector<jPosNode>> _cachedNeibourMap;
    const std::array<jPosNode, 4> _DIRS;

    inline bool in_bounds(jPosNode input) {
        int x, y;
        std::tie(x, y) = input;
        return 0 <= x && x < _width && 0 <= y && y < _height;
    }

    inline bool passable(jPosNode input) {
        return !_walls.count(input);
    }
};

}

#include "jTestBase.h"

namespace jLib {
	class jGraphGridTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			using namespace jGame;
			jPositionGraph g(100, 100);
            for (auto i = 1; i < 99; ++i)
            {
                g.addWall(std::make_tuple(i, i));
            }
            g.addWall(std::make_tuple(0, 4));
            g.addWall(std::make_tuple(4, 0));
            auto before = clock();
			auto ret = a_star_search(g, std::make_tuple(0, 0), std::make_tuple(99, 99));
            std::cout << "time cost:" << clock() - before << "ms" << std::endl;     //release模式下，100 * 100网格0ms；debug模式150ms
			for (auto &i : ret)
			{
				std::cout << "(" <<std::get<0>(i) << "," << std::get<1>(i) << ") ";
			}
			std::cout << std::endl;
		}
	};
}