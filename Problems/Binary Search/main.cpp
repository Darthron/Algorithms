//http://www.infoarena.ro/problema/cautbin

#include <fstream>

using namespace std;

const int MAXN = 100001;

int N;
int M;
unsigned v[MAXN];

ifstream mama("cautbin.in");
ofstream tata("cautbin.out");
int		biggest_pos(int n)
{
	int temp;
	int index;

	for (temp = 1; temp < N; temp <<= 1);
	for (index = 0; temp; temp >>= 1)
		if (index + temp < N and v[temp + index] <= n)
			index += temp;
	return index;
}

void	bsearch(int t, int n)
{
	int index;

	if (t < 2)
	{
		index = biggest_pos(n);
		if (t == 0)
		{
			if (v[index] == n)
				tata << index << '\n';
			else
				tata << -1 << '\n';
		}
		else
			tata << index << '\n';
	}
	else
	{
		index = biggest_pos(n - 1);
		tata << index + 1 << '\n';
	}
}

int		main()
{
	int i;
	unsigned n;
	int t;

	mama >> N;
	N += 1;
	for (i = 1; i < N; i += 1)
		mama >> v[i];
	mama >> M;
	M += 1;
	v[0] = -1;
	for (i = 1; i < M; i += 1)
	{
		mama >> t;
		mama >> n;
		bsearch(t, n);
	}
	return 0;
}
