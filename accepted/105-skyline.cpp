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
	int l{0}, h{0}, r{0};

	while (is >> l >> h >> r)
	{
		edges.push_back(Edge{l, h, Direction::Left});
		edges.push_back(Edge{r, h, Direction::Right});
	}

	sort(begin(edges), end(edges));

	int last_coord{-1};
	map<int, int> heights;
	heights[0] = 1;

	auto open_edge = [&](const Edge &edge)
	{
		auto old_height = heights.rbegin()->first;
		++heights[edge.height];
		auto new_height = heights.rbegin()->first;

		if (old_height != new_height && last_coord != edge.coord)
		{
			if (last_coord != -1)
				os << last_coord << ' ' << old_height << ' ';
			last_coord = edge.coord;
		}
	};

	auto close_edge = [&](const Edge &edge)
	{
		auto old_height = heights.rbegin()->first;
		if (!--heights[edge.height])
			heights.erase(edge.height);
		auto new_height = heights.rbegin()->first;

		if (old_height != new_height && last_coord != edge.coord)
		{
			if (last_coord != -1)
				os << last_coord << ' ' << old_height << ' ';
			last_coord = edge.coord;
		}
	};

	for (auto const &edge : edges)
	{
		switch (edge.direction)
		{
		case Direction::Left:
			open_edge(edge);
			break;
		case Direction::Right:
			close_edge(edge);
			break;
		}
	}
	os << last_coord << ' ' << heights.rbegin()->first << endl;
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
