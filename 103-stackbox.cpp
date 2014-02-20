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

template <typename BoxT>
bool BoxFits(const BoxT &a, const BoxT &b)
{
	for (size_t i{0}; i != a.size(); ++i)
	{
		if (a[i] < b[i])
			return false;
	}
	return true;
}

int main()
{
	int k{0}, n{0};

	typedef vector<int> BoxT;

	while (cin >> k >> n)
	{
		vector<BoxT> boxes;
		for (int i{0}; i != k; ++i)
		{
			BoxT box;
			for (int j{0}; j != n; ++j)
			{
				int d;
				cin >> d;
				box.push_back(d);
			}
			sort(begin(box), end(box));
			boxes.push_back(move(box));
		}

		// First sort descending by volume
		sort(begin(boxes), end(boxes),
		     [](const BoxT &a, const BoxT &b) -> bool
		     {
		         return accumulate(begin(a), end(a), 1, multiplies<int>())
		              > accumulate(begin(b), end(b), 1, multiplies<int>());
		     });

		auto sequence =
			FindLongestIncreasingSubsequence(begin(boxes), end(boxes),
			                                 &BoxFits<BoxT>);
		cout << sequence.size() << endl;
		for (auto s : sequence)
			cout << (s - begin(boxes)) << " ";
		cout << endl;
	}

	return 0;
}
