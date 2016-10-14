#include <stack>
#include <fstream>
#include <queue>
#include <iostream>

using namespace std;

int main()
{
	int						N, X, Y, Z;
	deque<pair<int, int>>	minimum;
	deque<pair<int, int>>	maximum;
	int						i, s;
	int						val;
	int						resulti, results;
	int						index;
	int						range;

	ifstream mama("sir.in");
	ofstream tata("sir.out");

	mama >> N >> X >> Y >> Z;
	resulti = -1;
	results = -1;
	for (i = s = index = 0; index < N; ++index)
	{
		mama >> val;
		while (!minimum.empty() and minimum.back().first > val)
			minimum.pop_back();
		minimum.push_back(make_pair(val, index));
		while (!maximum.empty() and maximum.front().first < val)
			maximum.pop_front();
		maximum.push_front(make_pair(val, index));
		/*for (int k = 0; k < minimum.size(); ++k)
			cout << minimum[k].first << " ";
		cout << '\n';*/
		/*for (int k = 0; k < maximum.size(); ++k)
			cout << maximum[k].first << " ";
		cout << '\n';*/
		++s;
		range = maximum.back().first - minimum.front().first;
		//cout << range << '\n';
		if (range > Z)
		{
			if (maximum.back().first == val)
			{
				int temp;
				while (val - minimum.front().first > Z)
				{
					temp = minimum.front().second;
					minimum.pop_front();
				}
				if (minimum.empty())
					i = index;
				else
					i = temp + 1;
			}
			else
			{
				int temp;
				while (maximum.back().first - val > Z)
				{
					temp = maximum.back().second;
					maximum.pop_back();
				}
				if (maximum.empty())
					i = index;
				else
					i = temp + 1;
			}
		}
		/*for (int k = 0; k < minimum.size(); ++k)
			cout << minimum[k].first << " ";
		cout << '\n';
		for (int k = 0; k < maximum.size(); ++k)
			cout << maximum[k].first << " ";
		cout << '\n' << i << " " << s;*/
		if (s - i >= X and s - i <= Y and s - i >= results - resulti)
		{
			results = s;
			resulti = i;
		}
		if (s - i == Y)
		{
			++i;
			while (!minimum.empty() and minimum.front().second < i)
				minimum.pop_front();
			while (!maximum.empty() and maximum.back().second < i)
				maximum.pop_back();
		}
		//cout << "\n\n";
	}
	if (resulti == -1)
		tata << -1;
	else
		tata << results - resulti << " " << resulti + 1 << " " << results;
	return 0;
}
