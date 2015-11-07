#include <iostream>

using namespace std;

int		main()
{
	char table[8][8];
	int minA;
	int minB;
	int i;
	int j;
	char ok;

	minA = 10;
	minB = 10;
	for (i = 0; i < 8; i += 1)
		for (j = 0; j < 8; j += 1)
			cin >> table[i][j];

	for (j = 0; j < 8; j += 1)
	{
		i = 0;
		while (i < 8 and table[i][j] == '.')
			i += 1;
		if (i < 8 and table[i][j] == 'W')
			minA = min(minA, i);
	}
	for (j = 0; j < 8; j += 1)
	{
		i = 7;
		while (i > -1 and table[i][j] == '.')
			i -= 1;
		if (i > -1 and table[i][j] == 'B')
			minB = min(minB, 7 - i);
	}
	if (minA <= minB)
		cout << 'A';
	else
		cout << 'B';
	return 0;
}
