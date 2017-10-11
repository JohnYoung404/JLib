#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include "jMath.h"


//////////////////////////////////////////////////////////////////////////
// Too old, so Discarded, maybe restored later.
//////////////////////////////////////////////////////////////////////////
namespace jGraphLib {

	struct graghNode
	{
		size_t dstVertex;
		double weight;
	};

	struct DijkstraTableEntry {
		bool known;
		double dist;
		size_t prevNode;
		DijkstraTableEntry() {
			known = false;
			dist = DBL_MAX;
			prevNode = 0;
		}
	};
	typedef DijkstraTableEntry *DijkstraTable;

	class jGraph		//directed graph. vertex enum from 1.
	{
	public:
		jGraph() :t(NULL) {}
		~jGraph() {
			delete[] t;
		}
		friend std::ostream& operator << (std::ostream &output, jGraph g);
		inline void addLink(size_t i, size_t j, double weight) {
			//std::vector<graghNode> nullVec;
			if (i + 1 > vertexNum())	theGragh.resize(i + 1);
			if (j + 1 > vertexNum())	theGragh.resize(j + 1);
			graghNode toPush;
			toPush.dstVertex = j;
			toPush.weight = weight;
			theGragh[i].push_back(toPush);
		}
		inline size_t vertexNum() {
			return theGragh.size();
		}
		void DijkstraAlgorithm(size_t startNode) {
			if (t) delete[] t;
			t = new DijkstraTableEntry[vertexNum()];
			t[startNode].dist = 0;
			while (1)
			{
				size_t nextVert = 0;
				double smallestDist = DBL_MAX;
				for (int i = 1; i < vertexNum(); ++i)
				{
					if (t[i].known == false && t[i].dist < smallestDist)
					{
						nextVert = i;
						smallestDist = nextVert;
					}
				}
				if (nextVert == 0)
				{
					break;
				}
				t[nextVert].known = true;
				std::vector<graghNode>::iterator itr = theGragh[nextVert].begin();
				for (; itr != theGragh[nextVert].end(); ++itr)
				{
					if (t[(*itr).dstVertex].known == false)
					{
						if (t[nextVert].dist + (*itr).weight < t[(*itr).dstVertex].dist)
						{
							t[(*itr).dstVertex].dist = t[nextVert].dist + (*itr).weight;
							t[(*itr).dstVertex].prevNode = nextVert;
						}
					}
				}
			}
		};
	private:
		std::vector<std::vector<graghNode>> theGragh;
		DijkstraTable t;
	};

	std::ostream& operator << (std::ostream &output, jGraph g) {
		for (int i = 0; i < g.vertexNum(); ++i)
		{
			if (g.theGragh[i].size() == 0)
			{
				continue;
			}
			output << i << " -> ";
			for (int j = 0; j < g.theGragh[i].size(); ++j)
			{
				output << g.theGragh[i][j].dstVertex /*<< "[" << g.theGragh[i][j].weight << "]"*/;
				output << " | ";
			}
			output << "\b\b\b   " << std::endl;
		}
		return output;
	}

	class jPoint {
	public:
		jPoint(double inX = 0, double inY = 0) :x(inX), y(inY) {}
		double x;
		double y;
		bool isInfinityPoint() {
			if (x == DBL_MAX || y == DBL_MAX) return true;
			return false;
		}
	};

	bool comp_x(jPoint& lhs, jPoint& rhs) {
		if (lhs.x < rhs.x) return true;
		return false;
	}

	bool comp_y(jPoint& lhs, jPoint& rhs) {
		if (lhs.y < rhs.y) return true;
		return false;
	}

	class jPointPair :public std::pair<jPoint, jPoint> {
	public:
		jPointPair() {}
		jPointPair(std::pair<jPoint, jPoint> &p) {
			this->first = p.first;
			this->second = p.second;
		}
		inline double dst() {
			if (this->first.isInfinityPoint() || this->second.isInfinityPoint())
			{
				return DBL_MAX;
			}
			return sqrt((this->first.x - this->second.x)*(this->first.x - this->second.x) + (this->first.y - this->second.y)*(this->first.y - this->second.y));
		}
	};

	class jPointSet : public std::vector<jPoint> {
	public:
		jPointPair mostAdjacentPointPair() {
			jPointPair ret;
			jPointPair lhs, rhs;
			if (this->size() <= 1)
			{
				ret = std::make_pair(jPoint(0, 0), jPoint(DBL_MAX, DBL_MAX));
				return ret;
			}
			if (this->size() == 2)
			{
				ret = std::make_pair((*this)[0], (*this)[1]);
				return ret;
			}
			std::sort(this->begin(), this->end(), comp_x);
			size_t midIndex = this->size() / 2;
			jPointSet lside, rside, midArea;
			for (size_t i = 0; i < this->size(); ++i)
			{
				if (i < midIndex) lside.push_back((*this)[i]);
				else rside.push_back((*this)[i]);
			}
			lhs = lside.mostAdjacentPointPair();
			rhs = rside.mostAdjacentPointPair();
			double lminDst = lhs.dst();
			double rminDst = rhs.dst();
			double minDst = min(lminDst, rminDst);
			if (lhs.dst() < rhs.dst())
				ret = lhs;
			else
				ret = rhs;
			double lborder = (*this)[midIndex].x - minDst, rborder = (*this)[midIndex].x + minDst;
			for (size_t i = 0; i < this->size(); ++i)
			{
				if ((*this)[i].x >= lborder && (*this)[i].x <= rborder)
					midArea.push_back((*this)[i]);
			}
			std::sort(midArea.begin(), midArea.end(), comp_y);
			jPointSet::iterator itr = midArea.begin();
			for (; itr != midArea.end(); ++itr)
			{
				size_t compareCount = 0;
				jPointPair p;
				while (1)
				{
					++compareCount;
					if (itr + compareCount == midArea.end() || compareCount == 8)
					{
						break;
					}
					p = std::make_pair(*itr, *(itr + compareCount));
					if (p.dst() < ret.dst())
						ret = p;
				}
			}
			return ret;
		}
	};

	std::ostream& operator << (std::ostream &output, jPointPair pp) {
		output << "(" << pp.first.x << ", " << pp.first.y << "), (" << pp.second.x << ", " << pp.second.y << ")" << std::endl;
		return output;
	}

	std::ostream& operator << (std::ostream &output, jPointSet ps) {
		for (size_t i = 0; i < ps.size(); ++i)
		{
			output << "(" << ps[i].x << ", " << ps[i].y << ")" << std::endl;
		}
		return output;
	}
}