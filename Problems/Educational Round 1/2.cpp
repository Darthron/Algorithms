#include <iostream>
#include <deque>
#include <string.h>

using namespace std;

int main()
{
	char	s[10001];
	int		t;

	cin.getline(s, 10001);
	cin >> t;
	for (int i = 0, l, r, k; i < t; ++i)
	{
		cin >> l >> r >> k;

		deque<char> d;
		
		--l;
		--r;
		k %= (r - l + 1);
		for (int j = 1, m = r; j <= k; ++j)
			d.push_front(s[r - j + 1]);
		for (int j = l; j <= r - k; ++j)
			d.push_back(s[j]);
		for (int j = l; j <= r; ++j)
			s[j] = d[j - l];
	}
	int n = strlen(s);
	for (int j = 0; j < n; ++j)
		cout << s[j];
	return 0;
}
