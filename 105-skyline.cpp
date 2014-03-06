#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>

#ifndef ONLINE_JUDGE
#include <gtest/gtest.h>
#include <boost/algorithm/string/trim.hpp>
#endif

using namespace std;

enum class Direction
{
	Left = 0,
	Right
};

struct Edge
{
	int coord;
	int height;
	Direction direction;

	Edge(int coord, int height, Direction direction)
		: coord(coord)
		, height(height)
		, direction(direction)
	{
	}

	bool operator<(const Edge &other) const
	{
		if (coord < other.coord)
			return true;
		if (coord > other.coord)
			return false;
		return direction < other.direction;
	}
};

void SkyLine(istream &is, ostream &os)
{
	vector<Edge> edges;
	map<int, int> heights;
	int l{0}, h{0}, r{0};

	while (is >> l >> h >> r)
	{
		edges.push_back(Edge{l, h, Direction::Left});
		edges.push_back(Edge{r, h, Direction::Right});
	}

	sort(begin(edges), end(edges));

	for (auto const &edge : edges)
	{
		switch (edge.direction)
		{
		case Direction::Left:
			if (heights.empty() || heights.rbegin()->first < edge.height)
				os << edge.coord << ' ' << edge.height << ' ';
			++heights[edge.height];
			break;
		case Direction::Right:
			assert(!heights.empty());
			assert(heights.rbegin()->first >= edge.height);
			{
				auto max_height = heights.rbegin()->first;
				if (!--heights[edge.height])
				{
					heights.erase(edge.height);
					auto next_height = heights.empty() ? 0 : heights.rbegin()->first;
					if (max_height == edge.height)
						os << edge.coord << ' ' << next_height << ' ';
				}
				else if (heights.empty())
					os << edge.coord << " 0 ";
			}
			break;
		}
	}
	os << endl;
}

#ifdef ONLINE_JUDGE

int main()
{
	SkyLine(cin, cout);
	return 0;
}

#else

class SkyLineFixture
	: public ::testing::Test
{
protected:
	ostringstream oss;

	virtual void SetUp()
	{
		oss.str("");
		oss.clear();
	}

	string GetOutput() const
	{
		namespace bal = boost::algorithm;
		return bal::trim_copy(oss.str());
	}
};

TEST_F(SkyLineFixture, Example)
{
	istringstream iss(
		"1 11 5 "
		"2 6 7 "
		"3 13 9 "
		"12 7 16 "
		"14 3 25 "
		"19 18 22 "
		"23 13 29 "
		"24 4 28 "
		);
	SkyLine(iss, oss);

	ASSERT_EQ("1 11 3 13 9 0 12 7 16 3 19 18 22 3 23 13 29 0", GetOutput());
}

#endif
