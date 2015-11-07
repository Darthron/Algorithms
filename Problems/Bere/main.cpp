//http://www.infoarena.ro/problema/br

#include <fstream>
#include <iostream>

using namespace std;

const int MAXN = 15000;

int x[MAXN];
int cost[2 * MAXN + 2];
int N;
int T;

void	build_cost()
{
	int i;

	cost[0] = 0;
	for (i = 0; i <= N; i += 1)
		cost[i + 1] = cost[i] + x[i];
	for (i = N + 1; i < 2 * N; i += 1)
		cost[i] = cost[i - 1] + x[i - N - 1];
}

int		find_beers(int beg, int end, int money)
{
	int index;
	int temp;

	if (cost[beg] - cost[beg - 1] > money)
		return 0;
	for (temp = 1; temp < N; temp <<= 1);
	temp /= 2;
	for (index = beg; temp > 0; temp >>= 1)
		if (index + temp < end and cost[index + temp] - cost[beg - 1] <= money)
			index += temp;
	return index - beg + 1;
}

int		main()
{
	int i;
	int fr;
	int money;

	ifstream mama("br.in");
	ofstream tata("br.out");

	mama >> N;
	mama >> T;
	for (i = 0; i < N; i += 1)
		mama >> x[i];
	build_cost();
	for (i = 0; i < T; i += 1)
	{
		mama >> fr;
		mama >> money;
		tata << find_beers(fr, fr + N, money) << '\n'; 
	}
	return 0;
}
