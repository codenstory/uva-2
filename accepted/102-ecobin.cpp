// 102 - Ecological Bin Packing
#include <iostream>
#include <algorithm>

using namespace std;

const int BIN_COUNT = 3;

enum Color
{
	BROWN = 0,
	CLEAR,
	GREEN
};

struct Bin
{
	int color[BIN_COUNT];
};

unsigned CountMoves(Bin bins[], Color colors[])
{
	unsigned count = 0;

	for (int bin_from = 0; bin_from != BIN_COUNT; ++bin_from)
		for (int bin_to = 0; bin_to != BIN_COUNT; ++bin_to)
		{
			if (bin_from == bin_to) continue;
			count += bins[bin_from].color[colors[bin_to]];
		}
	return count;
}

int main()
{
	Bin bins[BIN_COUNT];
	while (cin)
	{
		for (int i = 0; i != BIN_COUNT; ++i)
			cin >> bins[i].color[BROWN] >> bins[i].color[GREEN] >> bins[i].color[CLEAR];
		if (!cin)
			break;
		Color colors[BIN_COUNT] = { BROWN, CLEAR, GREEN };
		auto min_moves = numeric_limits<unsigned>::max();
		Color min_moves_colors[BIN_COUNT];
		do
		{
			auto moves = CountMoves(bins, colors);
			if (moves < min_moves)
			{
				min_moves = moves;
				copy(colors, colors + BIN_COUNT, min_moves_colors);
			}
		}
		while (next_permutation(colors, colors + BIN_COUNT));

		for (int i = 0; i != BIN_COUNT; ++i)
		{
			switch (min_moves_colors[i])
			{
			case BROWN: cout << "B"; break;
			case GREEN: cout << "G"; break;
			case CLEAR: cout << "C"; break;
			}
		}
		cout << " " << min_moves << endl;
	}

	return 0;
}
