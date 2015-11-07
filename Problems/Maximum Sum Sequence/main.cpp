//http://www.infoarena.ro/problema/ssm

#include <fstream>

using namespace std;

const long long INF = 1UL << 40;

int		main()
{
	ifstream mama("ssm.in");
	ofstream tata("ssm.out");

	int N;
	long maxim;
	int s;
	int n;
	int x;
	int y;
	int imax;
	int jmax;

	mama >> N;
	N += 1;
	maxim = -INF;
	s = 0;
	x = 1;
	for (int i = 1; i < N; i += 1)
	{
		mama >> n;
		if (s < 0)
		{
			s = n;
			x = i;
			y = i;
		}
		else
		{
			s += n;
			y = i;
		}
		if (s > maxim)
		{
			maxim = s;
			imax = x;
			jmax = y;
		}
	}
	tata << maxim << " " << imax << " " << jmax << '\n'; 
	return 0;
}
