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
		double dist[n][n];
		int next[n][n];

		for (int i = 0; i != n; ++i)
			for (int j = 0; j != n; ++j)
			{
				next[i][j] = -1;
				if (i == j)
				{
					w[i][j] = 1.0;
					dist[i][j] = 0.0;
					continue;
				}
				cin >> w[i][j];
				dist[i][j] = -log(w[i][j]);
			}

		// Floyd-Warshall to find negative cycles.
		for (int k = 0; k != n; ++k)
			for (int i = 0; i != n; ++i)
				for (int j = 0; j != n; ++j)
					if (dist[i][k] + dist[k][j] < dist[i][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
						next[i][j] = k;
					}

		bool found{false};

		for (int i = 0; i != n; ++i)
			if (dist[i][i] < 0.0)
			{
				double profit = exp(-dist[i][i]);
				if (profit < 1.01)
					continue;
				found = true;

				auto *pnext = &next[0][0];

				function<void(int, int)> print_path = [&](int i, int j)
				{
					auto k = pnext[i*n + j];
					if (k == -1)
						found = false;
					print_path(i, k);
					cout << k << " ";
					print_path(k, j);
				};
				print_path(i, i);

				break;
			}

		if (!found)
			cout << "no arbitrage sequence exists" << endl;
	}
	return 0;
}
