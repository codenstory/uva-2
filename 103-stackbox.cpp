// 103 - Stacking Boxes
#include <iostream>
#include <algorithm>

using namespace std;

template <typename IterT, typename CompareT>
vector<IterT>
FindLongestIncreasingSubsequence(IterT first, IterT last,
                                 CompareT compare)
{
	// Patience sorting to find increasing longest subsequence
	vector<IterT> piles;
	vector<IterT> backrefs;

	for (IterT i{first}; i != last; ++i)
	{
		auto it = lower_bound(begin(piles), end(piles),
		                      i,
		                      [&compare](IterT a, IterT b) -> bool
		                          { return compare(*a, *b); }
		                      );
		backrefs.push_back(it > begin(piles) ? *(it - 1) : last);
		if (it == end(piles))
			piles.push_back(i);
		else
			*it = i;
	}

	vector<IterT> seq(piles.size());

	int j = seq.size() - 1;
	for (IterT i{piles.back()}; i != last; --j, i = backrefs[i - first])
		seq[j] = i;
	return seq;
}

struct Box
{
	int number;
	vector<int> dimensions;

	Box(int number, int dimensions)
		: number(number)
		, dimensions(dimensions)
	{
	}

	int GetVolume() const
	{
		return accumulate(begin(dimensions), end(dimensions), 1, multiplies<int>());
	}

	bool CanFit(const Box &other) const
	{
		for (size_t i{0}; i != dimensions.size(); ++i)
		{
			if (dimensions[i] < other.dimensions[i])
				return false;
		}
		return true;
	}
};

bool CanFit(const Box &a, const Box &b)
{
	return a.CanFit(b);
}

istream &operator>>(istream &is, Box &b)
{
	for (auto &d : b.dimensions)
		cin >> d;
	sort(begin(b.dimensions), end(b.dimensions));
	return is;
}

int main()
{
	int k{0}, n{0};

	while (cin >> k >> n)
	{
		vector<Box> boxes;
		for (int i{0}; i != k; ++i)
		{
			Box box{i, n};
			cin >> box;
			boxes.push_back(move(box));
		}

		// First sort descending by volume
		sort(begin(boxes), end(boxes),
		     [](const Box &a, const Box &b) -> bool
		     {
		         return a.GetVolume() > b.GetVolume();
		     });

		auto sequence =
			FindLongestIncreasingSubsequence(begin(boxes), end(boxes), &CanFit);
		cout << sequence.size() << endl;
		for (auto s : sequence)
			cout << s->number << " ";
		cout << endl;
	}

	return 0;
}
