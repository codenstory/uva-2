// 104 - Arbitrage
#include <iostream>
#include <cmath>
#include <limits>
#include <functional>

using namespace std;

int main()
{
	int n{0};
	while (cin >> n)
	{
		double w[n][n];

		for (int u = 0; u != n; ++u)
		{
			for (int v = 0; v != n; ++v)
			{
				if (u == v)
				{
					w[u][v] = 0.0;
					continue;
				}
				cin >> w[u][v];
				w[u][v] = -log(w[u][v]);
			}
		}

		double dist[n];
		int prev[n];
		int next[n];

		for (int i = 0; i != n; ++i)
			dist[i] = 0.0, prev[i] = -1, next[i] = -1;

		bool found{false};

		for (int i = n - 1; i >= 0; --i)
			for (int u = 0; !found && u != n; ++u)
				for (int v = 0; v != n; ++v)
				{
					double delta = dist[u] + w[u][v];
					if (delta >= dist[v])
						continue;
					if (i)
						dist[v] = delta, prev[v] = u;
					else
					{
						auto profit = exp(-delta);
						if (profit < 1.01)
							continue;
						found = true;

						// Calculate the cycle from the prev.
						int j{v};
						for (; ; j = prev[j])
						{
							auto &x = next[prev[j]];
							if (x != -1)
								break;
							x = j;
						}

						// Print the cycle
						int k{j};
						do
						{
							cout << k + 1 << " ";
							k = next[k];
						}
						while (k != j);
						cout << j + 1 << endl;
					}
				}

		if (!found)
			cout << "no arbitrage sequence exists" << endl;
	}
	return 0;
}
