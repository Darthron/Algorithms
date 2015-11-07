//http://www.infoarena.ro/problema/rucsac

#include <fstream>

using namespace std;

const int MAXN = 10001;

int sum[MAXN];

int	main()
{
	int N;
	int G;
	int w;
	int p;

	ifstream mama("rucsac.in");
	ofstream tata("rucsac.out");
	mama >> N;
	mama >> G;
	for (int j, i = 0; i < N; i += 1) {
		mama >> w;
		mama >> p;
		for (j = G; j >= w; j -= 1) {
			if (sum[j] < sum[j - w] + p)
				sum[j] = sum[j - w] + p;
		}
	}
	tata << sum[G];
	return 0;
}
