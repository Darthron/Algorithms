#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

int N;
int v[1000000];

void	shuffle_array()
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(v, v + N, default_random_engine(seed));
}

void	swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	three_way_quicksort(int begin, int end)
{
	int lt;
	int gt;
	int i;
	int element;

	if (begin >= end)
		return;
	element = v[begin];
	i = begin + 1;
	lt = begin;
	gt = end;
	while (i <= gt)
	{
		if (v[i] < element)
		{
			swap(v + i, v + lt);
			++i;
			++lt;
		}
		else if (v[i] > element)
		{
			swap(v + i, v + gt);
			--gt;
		}
		else 
			++i;
	}
	three_way_quicksort(begin, lt - 1);
	three_way_quicksort(i, end);
}

int		main()
{
	cin >> N;
	for (int i = 0; i < N; i += 1)
	cin >> v[i];
	shuffle_array();
	three_way_quicksort(0, N - 1);
	for (int i = 0; i < N; i += 1)
		cout << v[i] << " ";
	return 0;
}
