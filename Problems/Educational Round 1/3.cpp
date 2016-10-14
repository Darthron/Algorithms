#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const long double PI = 2 * 3.1415926535897;

bool cmp(pair<long double, int> a, pair<long double, int> b)
{
	return a.first < b.first;
}

int main()
{
	int						n;
	pair<long double, int>	lines[100001];

	cin >> n;
	
	for (int i = 0, x, y; i < n; ++i)
	{
		cin >> x >> y;

		lines[i].first = atan2l(y, x);
		lines[i].second = i;
	}

	sort(lines, lines + n, cmp);
	long double minimum;
	
	minimum = min(abs(lines[0].first - lines[n - 1].first), PI - abs(lines[n - 1].first) - abs(lines[0].first));
	//cout << setprecision(10) << PI << " ";
	//cout << setprecision(10) << abs(lines[n - 1].first) + abs(lines[0].first) << '\n';
	int mx = lines[0].second, my = lines[n - 1].second;
	//cout << minimum << '\n';
	long double temp;
	for (int i = 1; i < n; ++i)
	{
		temp = min(abs(lines[i].first - lines[i - 1].first), PI - abs(lines[i].first) - abs(lines[i - 1].first));
		//cout << setprecision(10) << temp << '\n';
		if (temp < minimum)
		{ 
			minimum = temp;
			mx = lines[i - 1].second;
			my = lines[i].second;
		}
	}
	//for (int i = 0; i < n; ++i)
	//	cout << setprecision(10) << lines[i].second << " " << lines[i].first << '\n';
	cout << mx + 1 << " " << my + 1;
	return 0;
}
