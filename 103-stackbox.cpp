// 103 - Stacking Boxes
#include <iostream>
#include <algorithm>

using namespace std;


template <typename IterT, typename CompareT>
vector<IterT>
FindLongestIncreasingSubsequence(IterT first, IterT last,
                                 CompareT compare)
{
	int n = last - first;

	// Dynamic programming O(n²)
	int M[n];
	int backref[n];

	for (int i{0}; i != n; ++i)
	{
		M[i] = 1;
		backref[i] = -1;

		for (int j{0}; j != i; ++j)
		{
			if (compare(*(first + j), *(first + i)))
			{
				if (M[j] + 1 >= M[i])
				{
					M[i] = M[j] + 1;
					backref[i] = j;
				}
			}
		}
	}

	vector<IterT> sequence;

	for (auto m = max_element(M, M + n) - M; m >= 0; m = backref[m])
		sequence.push_back(first + m);

	return sequence;
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
			if (dimensions[i] <= other.dimensions[i])
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
		is >> d;
	sort(begin(b.dimensions), end(b.dimensions));
	return is;
}

int main()
{
	int k{0}, n{0};

	while (cin >> k >> n)
	{
		vector<Box> boxes;
		for (int i{1}; i <= k; ++i)
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
