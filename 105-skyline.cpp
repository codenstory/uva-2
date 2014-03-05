#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>

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

int main()
{
	vector<Edge> edges;
	map<int, int> heights;
	int l{0}, h{0}, r{0};

	while (cin >> l >> h >> r)
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
				cout << edge.coord << ' ' << edge.height << ' ';
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
						cout << edge.coord << ' ' << next_height << ' ';
				}
				else if (heights.empty())
					cout << edge.coord << " 0 ";
			}
			break;
		}
	}
	cout << endl;

	return 0;
}
