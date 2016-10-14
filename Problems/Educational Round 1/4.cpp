#include <iostream>
//#include <fstream>

using namespace std;

const unsigned int INF = 1 << 30;
unsigned int d[31][31][51];

//ifstream mama("test.in");
//ofstream tata("verifMain.out");

void	haida()
{
	int i, j, k;
	int temp;
	int minimum;

	for (i = 1; i < 31; ++i)
		for (j = 1; j < 31; ++j)
			for (k = 1; k < 51; ++k)
				d[i][j][k] = INF;
	for (j = 1; j < 31; ++j)
		for (k = 1; k < 51; ++k)
			if (k <= j)
				d[1][j][k] = d[j][1][k] = !(j == k);
	for (i = 1; i < 31; ++i)
		for (j = 1; j < 31; ++j)
			d[i][j][0] = 0;
	for (i = 2; i < 31; ++i)
	{
		for (j = 2; j < 31; ++j)
		{
			temp = i * j + 1;
			if (i * j > 50)
				temp = 51;
			for (k = 1; k < temp; ++k)
			{
				minimum = INF;
				if (d[i][j][k] < INF)
					continue;
				if (i * j == k)
				{
					d[i][j][k] = 0;
					continue;
				}
				int l;
				for (l = 1; l < i; ++l)
				{
					if (k - l * j >= 0 and minimum > j * j + d[i - l][j][k - l * j])
						minimum = j * j + d[i - l][j][k - l * j];
					if (minimum > j * j + d[i - l][j][k])
						minimum = j * j + d[i - l][j][k];
				}
				for (l = 1; l < j; ++l)
				{
					if (k - l * i >= 0 and minimum > i * i + d[i][j - l][k - l * i])
						minimum = i * i + d[i][j - l][k - l * i];
					if (minimum > i * i + d[i][j - l][k])
						minimum = i * i + d[i][j - l][k];
				}
				d[i][j][k] = minimum;
				d[j][i][k] = minimum;
			}
		}
	}
	/*for (i = 1; i < 10; ++i)
		for (j = 1; j < 10; ++j)
			for (k = 1; k < 51 and k <= i * j; ++k)
				tata << i << " " << j << " " << k << " " << d[i][j][k] << '\n';*/
}

int		main()
{
	int t;

	cin >> t;
	//mama >> t;
	haida();
	for (int i = 0,x, y, k; i < t; ++i)
	{
		cin >> x >> y >> k;
		cout << d[x][y][k] << '\n';
		//mama >> x >> y >> k;
		//tata << d[x][y][k] << '\n';
	}
	return 0;
}
