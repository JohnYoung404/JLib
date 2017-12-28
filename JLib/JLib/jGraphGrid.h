#pragma once
#include <tuple>
#include <functional>
#include <cmath>
#include <unordered_set>
#include <array>
#include "jGraphSearch.h"
#include "jGrid.h"
#include "jVector.h"
#include "jTestBase.h"

namespace std {

template <>
struct hash<tuple<int, int> > 
{
	inline size_t operator()(const tuple<int, int>& location) const {
		int x, y;
		tie(x, y) = location;
		return x * 1812433253 + y;
	}
};

}

namespace jGame
{

using jPosNode = std::tuple<int, int>;

class jPositionGraph : public jGraphLib::jGraph<jPosNode>
{
public:
    jPositionGraph(int initWidth, int initHeight) : _width(initWidth), _height(initHeight) { }
	static std::array<jPosNode, 4> DIRS;
	

    std::vector<jPosNode> neibours(jPosNode InputNode) override
    {
		int x, y, dx, dy;
		std::tie(x, y) = InputNode;
		std::vector<jPosNode> results;

		for (auto dir : DIRS) {
			std::tie(dx, dy) = dir;
			jPosNode next(x + dx, y + dy);
			if (in_bounds(next) && passable(next)) {
				results.push_back(next);
			}
		}

		return results;
    }

	const float dist(jPosNode from, jPosNode to) override
	{
		if (in_bounds(from) && in_bounds(to))
		{
			if (passable(to) && passable(from))
			{
				auto neibourVec = neibours(from);
				return from == to ? 0 : (std::find(neibourVec.begin(), neibourVec.end(), to) != neibourVec.end()) ? 1.0f : FLT_MAX;
			}
		}
		return FLT_MAX;
	}

	const float heuristic(jPosNode a, jPosNode b) override {
		int x1, y1, x2, y2;
		std::tie(x1, y1) = a;
		std::tie(x2, y2) = b;
		return static_cast<float>(abs(x1 - x2) + abs(y1 - y2));
	}

	inline bool in_bounds(jPosNode input)  {
		int x, y;
		std::tie(x, y) = input;
		return 0 <= x && x < _width && 0 <= y && y < _height;
	}

	inline bool passable(jPosNode input)  {
		return !_walls.count(input);
	}

	inline void addWall(jPosNode input)
	{
		_walls.emplace(input);
	}

private:
    int _width, _height;
	std::unordered_set<jPosNode> _walls;
};

std::array<jPosNode, 4> jPositionGraph::DIRS{ jPosNode{ 1, 0 }, jPosNode{ 0, -1 }, jPosNode{ -1, 0 }, jPosNode{ 0, 1 } };


}

namespace jLib {
	class jGraphGridTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			using namespace jGame;
			jPositionGraph g(3, 3);
			g.addWall(std::make_tuple(1, 1));
			auto ret = a_star_search(g, std::make_tuple(0, 0), std::make_tuple(2, 2));
			for (auto &i : ret)
			{
				std::cout << "(" <<std::get<0>(i) << "," << std::get<1>(i) << ") ";
			}
			std::cout << std::endl;
		}
	};
}