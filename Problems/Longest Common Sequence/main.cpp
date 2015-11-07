#include <fstream>

using namespace std;

const int MAXL = 1024;

int N, M;
int n[MAXL];
int m[MAXL];

int		lcs(int p, int q)
{
	if (p < 0 or q < 0)
		return 0;
	if (n[p] == m[q])
		return 1 + lcs(p - 1, q - 1);
	return max(lcs(p - 1, q), lcs(p, q - 1));
}

int		main()
{
	ifstream mama("cmlsc.in");
	ofstream tata("cmlsc.out");

	mama >> N;
	mama >> M;
	for (int i = 0; i < N; i += 1)
		mama >> n[i];
	for (int i = 0; i < M; i += 1)
		mama >> m[i];
	tata << lcs(N - 1, M - 1);
	return 0;
}
