//Having a multiset(a set where elements may be present more than once), can you form a sum of N using the elements of the multiset

#include <iostream>

using namespace std;

const int MAXN = 1000000;

int sum[MAXN];

int	main()
{
	int n;
	int m;
	int maxi;
	int a;

	cin >> n;
	cin >> m;
	sum[0] = 1;
	maxi = 0;
	for (int j, i = 0; i < m; i += 1) {
		cin >> a;
		j = maxi;
		while (j >= 0) {
			sum[j + a] = sum[j] && 1;
			j--;
		}
		maxi = maxi + a;
		if (sum[n]) {
			cout << 1 << '\n';
			return 0;
		}
	}
	cout << 0 << '\n';
	return 0;
}
