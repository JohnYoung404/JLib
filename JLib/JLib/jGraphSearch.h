#pragma once
#include <queue>
#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>
#include "jGraph.h"
#include "jTestBase.h"

namespace jGraphLib
{

namespace {
template<typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

	inline bool empty() const { return elements.empty(); }

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	inline T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};
}

namespace {
template<typename node>
std::vector<node> reconstruct_path(node start, node goal, std::unordered_map<node, node>& came_from)
{
	std::vector<node> path;
	node current = goal;
	while (current != start) {
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start);
	return std::vector<node>(path.rbegin(), path.rend());
}
}

template<typename node, typename Graph>
std::enable_if_t<std::is_base_of<jGraph<node>, Graph>::value, std::vector<node> >
a_star_search(Graph &graph, const node &start, const node & goal)
{
	PriorityQueue<node, float> theQueue;
	theQueue.put(start, 0);

	std::unordered_map<node, node> path;
	std::unordered_map<node, float> cost_eval;
    std::unordered_set<node> closed_set;

	path[start] = start;
	cost_eval[start] = 0;

	while (!theQueue.empty())
	{
		auto current = theQueue.get();
        closed_set.emplace(current);
		if (current == goal)
		{
			return reconstruct_path(start, goal, path);
		}
		for (auto &next : graph.neibours(current))
		{
            if(closed_set.count(next)) continue;
			float new_cost = graph.dist(current, next) == FLT_MAX ? FLT_MAX :cost_eval[current] + graph.dist(current, next);
			if (!cost_eval.count(next) || new_cost < cost_eval[next]) {
				cost_eval[next] = new_cost;
				float priority = new_cost + graph.heuristic(next, goal);	//heuristic启发函数如果是常值，则退化为dijkstra搜索
				theQueue.put(next, priority);
				path[next] = current;
			}
		}
	}

	return std::vector<node>();
}

}

namespace jLib {
	class jGraphSearchTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();
			using namespace jGraphLib;
			jGraph<int> g;
			g.addNode(1, std::vector<int>{2, 3});
			g.addNode(2, std::vector<int>{4, 6});
			g.addNode(3, std::vector<int>{5});
			g.addNode(4, std::vector<int>{5});
			g.addNode(5, std::vector<int>{});
			g.addNode(6, std::vector<int>{});
			auto ret = a_star_search(g, 1, 5);
			for (auto &i : ret)
			{
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}
	};
}