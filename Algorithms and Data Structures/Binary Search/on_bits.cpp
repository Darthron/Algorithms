#include <iostream>

using namespace std;

int numbers[1000000];
int n;

bool	search(int val)
{
	int index;
	int temp;

	//temp = log n
	for (temp = 1; temp < n; temp <<= 1);
	//Try to find the index of the searched element
	for (index = 0; temp; temp >>= 1)
		if (index + temp < n and numbers[index + temp] <= val)
			index += temp;
	return (numbers[index] == val);
}

int		main()
{
	int val;

	cin >> n;
	cin >> val;
	for (int i = 0; i < n; i += 1)
		cin >> numbers[i];
	cout <<	search(val);
	return 0;
}
