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
		int next[n][n];

		for (int u = 0; u != n; ++u)
			for (int v = 0; v != n; ++v)
			{
				next[u][v] = -1;
				if (u == v)
				{
					w[u][v] = 0.0;
					continue;
				}
				cin >> w[u][v];
				w[u][v] = -log(w[u][v]);
			}

		bool found{false};
		for (int source = 0; source != n && !found; ++source)
		{
			double dist[n];
			int pred[n];

			for (int i = 0; i != n; ++i)
				dist[i] = numeric_limits<double>::max(), pred[i] = -1;
			dist[source] = 0.0;

			for (int i = 1; i != n; ++i)
				for (int u = 0; u != n; ++u)
					for (int v = 0; v != n; ++v)
					{
						double nd = dist[u] + w[u][v];
						if (nd < dist[v])
							dist[v] = nd, pred[v] = u;
					}

			for (int u = 0; u != n && !found; ++u)
				for (int v = 0; v != n; ++v)
					if (dist[u] + w[u][v] < dist[v])
					{
						double delta = dist[u] + w[u][v] - dist[v];
						double profit = exp(-delta);
						if (profit < 1.01)
							continue;
						found = true;
						int p = v;
						do
						{
							cout << p + 1 << " ";
							p = pred[p];
						}
						while (p != v);
						cout << v + 1 << endl;
						break;
					}
		}

		if (!found)
			cout << "no arbitrage sequence exists" << endl;
	}
	return 0;
}
