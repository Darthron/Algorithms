//https://www.hackerrank.com/contests/101hack31/challenges/subsets-counting
//xors[old][i] - if I had the number i, I could make xors[old][i] pairs of sets whose xor are equal; since i ^ i = 0, the result will be added to xors[now][0], where I will also have the final result
//I multiply xors[old][j] by two because I count the ordered pairs (A, B)
//I don't use fast power because because value * value may be too big to hold
//The MOD = 2 * M is a nice hack. I have to compute (result + xors[now][0]) / 2, but I need to hold both result and xors less then M. Since the overall result may be destorted when I divide by 2
//after using % M, the 2 * M will provide me with a safe way to hold the modulus, because I can always divide by 2

#include <iostream>
#include <string.h>
 2
using namespace std;

int N, M;
unsigned long long xors[2][4097];

int main()
{
	int		old, now;
	int		MOD;
	long long	result;

	cin >> N >> M;
	MOD = 2 * M;
	xors[0][0] = 1;
	old = 1;
	now = 0;
	for (int i = 1; i <= N; ++i)
	{
		old = 1 - old;
		now = 1 - now;
		for (int j = 0; j < 4097; ++j)
		{
			if (xors[old][j])
			{
				xors[now][j] = (xors[now][j] + xors[old][j]) % MOD;
				xors[now][i ^ j] = (xors[now][i ^ j] + 2 * xors[old][j]) % MOD;
			}
		}
		memset(xors[old], 0, sizeof(xors[old]));
	}

	result = 1;
	for (int j = 0; j < N; ++j)
		if ((result *= 3) >= MOD)
			result %= MOD;
	result += xors[now][0];
	result /= 2;
	cout << result % M;
	return 0;
}
