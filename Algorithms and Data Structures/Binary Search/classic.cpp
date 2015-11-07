#include <iostream>

using namespace std;

int numbers[1000000];
int n;

bool	search(int beg, int end, int val)
{
	int middle;

	if (beg == end)
		if (numbers[beg] == val)
			return true;
		else
			return false;
	middle = (beg + end) / 2;
	if (numbers[middle] == val)
		return true;
	if (numbers[middle] > val)
		return search(beg, middle - 1, val);
	return search(middle + 1, end, val);
}

int		main()
{
	cin >> n;
	for (int i = 0; i < n; i += 1)
		cin >> numbers[i];
	cout <<	search(0, n - 1, 16);
	return 0;
}
