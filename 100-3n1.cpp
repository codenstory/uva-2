#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<unsigned, unsigned> known_cycles;

unsigned CountCycles(unsigned i)
{
	auto it = known_cycles.find(i);
	if (it != end(known_cycles))
		return it->second;
	unsigned cycles = (i & 1)
		? 1 + CountCycles(i + i + i + 1)
		: 1 + CountCycles(i >> 1);
	return known_cycles[i] = cycles;
}

unsigned FindMax(unsigned i, unsigned j)
{
	unsigned max_cycles = 0;
	for (auto x = i; x != j + 1; ++x)
		max_cycles = std::max(max_cycles, CountCycles(x));
	return max_cycles;
}

int main()
{
	known_cycles.reserve(10000000);
	known_cycles[1] = 1;

	unsigned i(0), j(0);
	while (cin >> i >> j)
	{
		if (!i || !j)
			break;
		auto n = FindMax(i, j);
		cout << i << " " << j << " " << n << endl;
	}
	return 0;
}
