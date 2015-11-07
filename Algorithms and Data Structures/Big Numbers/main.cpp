#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

int		a[100];
int		b[100];
int		r[205];
int		lengthA;
int		lengthB;
int		lengthR;

void	add()
{
	int i;
	int t;

	for (i = 0; i < lengthA or i < lengthB or t; i += 1, t /= 10)
		r[i] = (t += a[i] + b[i]) % 10;
	lengthR = i;
}

void	multiply_small()
{
	int i;
	int t;
	
	int nr;
	nr = 17;
	for (i = 0; i < lengthA or t; i += 1, t /= 10)
		r[i] = (t += a[i] * nr) % 10;
	lengthR = i;
}

void	multiply_big()
{
	int i;
	int j;
	int t;
	
	for (i = 0; i < lengthA; i += 1)
	{
		for (t = 0, j = 0; j < lengthB or t; j += 1, t /= 10)
			r[i + j] = (t += r[i + j] + a[i] * b[j]) % 10;
		if (i + j > lengthR)
			lengthR = i + j;
	}
}

void	substract()
{
	int t;
	int i;
	int sgn;

	if (/*bigger()*/ true)
		sgn = 1;
	else
		sgn = -1;
	if (sgn == 1)
	{
		for (t = 0, i = 0; i < lengthA; i += 1)
		{
			r[i] = a[i] - b[i] - t;
			t = (r[i] < 0);
			if (r[i] < 0)
				r[i] += 10;
		}
		lengthR = lengthA;
		while (lengthR > 1 and r[lengthR - 1] == 0)
			--lengthR;
		r[lengthR] = 1;
	}
	else
	{
		for (t = 0, i = 0; i < lengthB; i += 1)
		{
			r[i] = b[i] - a[i] - t;
			t = (r[i] < 0);
			if (r[i] < 0)
				r[i] += 10;
		}
		lengthR = lengthA;
		while (lengthR > 1 and r[lengthR - 1] == 0)
			--lengthR;
		r[lengthR] = 1;
	}
}

void	divide()
{
	int i;
	int t;
	int nr;

	t = 0;
	nr = 17;
	for (i = lengthA - 1; i > -1; i -= 1, t %= nr)
		r[i] = (t = t * 10 + a[i]) / nr;
	for (lengthR = lengthA; lengthR > 1 and !r[lengthR - 1]; --lengthR);
}

int		main()
{
	char s[100];

	cin.getline(s, 100);
	lengthA = strlen(s);
	for (int i = lengthA - 1; i > -1; i -= 1)
		a[lengthA - 1 - i] = s[i] - 48;

	cin.getline(s, 100);
	lengthB = strlen(s);
	for (int i = lengthB - 1; i > -1; i -= 1)
		b[lengthB - i - 1] = s[i] - 48;
	divide();
	for (int i = lengthR - 1; i > -1; i -= 1)
		cout << r[i];
	cout << '\n';
	return 0;
}
