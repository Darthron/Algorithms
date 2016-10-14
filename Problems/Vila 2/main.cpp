#include <fstream>
#include <deque>
#include <cmath>

using namespace std;

int main()
{
	int							N, D;
	int							val;
	deque<pair<int, int>>		maximum;
	deque<pair<int, int>>		minimum;
	int							i;
	int							result;

	ifstream mama("vila2.in");
	ofstream tata("vila2.out");

	mama >> N >> D;
	result = -1;
	for (i = 0; i < N; i += 1)
	{
		mama >> val;
		while (!minimum.empty() and minimum.back().first >= val)
			minimum.pop_back();
		while (!minimum.empty() and minimum.front().second < i - D)
			minimum.pop_front();
		minimum.push_back(make_pair(val, i));
		while (!maximum.empty() and maximum.front().first <= val)
			maximum.pop_front();
		while (!maximum.empty() and maximum.back().second < i - D)
			maximum.pop_back();
		maximum.push_front(make_pair(val, i));
		if (result < maximum.back().first - minimum.front().first)
			result = maximum.back().first - minimum.front().first;
	}
	tata << result;
	return 0;
}
