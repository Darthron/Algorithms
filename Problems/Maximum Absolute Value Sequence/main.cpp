#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

bool	cmp(pair<int, int> a, pair<int, int> b)
{
	return a.first < b.first;
}

int		main()
{
	ifstream mama("seq.in");
	ofstream tata("seq.out");

	int				n;
	pair<int, int>	sums[10000];
	int				a;
	int				minimum;
	int				sols, solx, soly;

	mama >> n;
	mama >> a;
	sums[0] = make_pair(a, 0);
	for (int i = 1; i < n; i += 1)
	{
		mama >> a;
		sums[i] = make_pair(sums[i - 1].first + a, i);
	}
	sort (sums, sums + n, cmp);
	minimum = 10000000;
	for (int i = 1; i < n; i += 1)
	{
		if (abs(sums[i].first - sums[i - 1].first) < minimum)
		{
			solx = sums[i].second;
			soly = sums[i - 1].second;
			sols = abs(sums[i].first - sums[i - 1].first);
			minimum = sols;
		}
	}
	tata << sols << " " << min(solx, soly) + 1 << " " << max(soly, solx) << '\n';
	return 0;
}
