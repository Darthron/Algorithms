#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

int N;
int v[1000000];
int K;

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

int		find_kth_element(int begin, int end)
{
	int i;
	int j;
	int element;

	if (begin >= end)
		return v[begin];
	element = v[begin];
	i = begin + 1;
	j = end;
	while (i <= j)
	{
		while (v[i] <= element and i <= j)
			++i;
		while (v[j] >= element and i <= j)
			--j;
		if (i <= j)
			swap(v + i, v + j);
	}
	if (j == K)
		return element;
	swap(v + begin, v + j);
	if (j < K)
		return find_kth_element(i, end);
	return find_kth_element(begin, j - 1);	
}

int		main()
{
	cin >> N;
	cin >> K;
	--K;
	for (int i = 0; i < N; i += 1)
		cin >> v[i];
	shuffle_array();
	cout << find_kth_element(0, N - 1);
	return 0;
}
