#pragma once
#include <vector>
#include <unordered_map>
#include <cfloat>
#include <algorithm>
#include <iterator>

namespace jLib{
namespace jGraphLib{

//使用领接表的简单有向图结构
template <typename node>
class jGraph
{
public:

	virtual const std::vector<node>& neibours(node InputNode)
	{
		return _graph.count(InputNode) ? _graph[InputNode] : _graph[InputNode] = std::vector<node>();
	}

	virtual void addNode(node InputNode, std::vector<node> NodeNeibours)
	{
		_graph.insert(std::make_pair(InputNode, NodeNeibours));
	}

	virtual const float dist(node from, node to)
	{
		if (_graph.count(from) && _graph.count(to))
			return from == to ? 0 : (std::find(_graph[from].begin(), _graph[from].end(), to) != _graph[from].end()) ? 1.0f : FLT_MAX;
		return FLT_MAX;
	}

	virtual const float heuristic(node a, node b) {
		return 0;
	}

private:
	std::unordered_map<node, std::vector<node>> _graph;
};

}}