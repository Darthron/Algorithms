#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

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

void	quick_sort(int begin, int end)
{
	int i;
	int j;
	int element;

	if (begin >= end)
		return;
	i = begin + 1;
	j = end;
	element = v[begin];
	while (i <= j)
	{
		while (v[i] <= element and i <= j)
			++i;
		while (v[j] >= element and i <= j)
			--j;
		if (i <= j)
			swap(v + i, v + j);
	}
	swap(v + begin, v + j);
	quick_sort(begin, j - 1);
	quick_sort(i, end);
}

int		main()
{
	cin >> N;
	for (int i = 0; i < N; i += 1)
		cin >> v[i];
	shuffle_array();
	quick_sort(0, N - 1);
	for (int i = 0; i < N; i += 1)
		cout << v[i] << " ";
	return 0;
}
