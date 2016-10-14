#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

enum        fall { left, right };
int         coml[2005][2], comr[2005][2], cadel[2005], cader[2005], v[2005];
double  db[2005][2005][2][2], de[2005][2005][2][2];
double p;
int         h;

double e(int i, int j, fall fl, fall fr);

double  b(int i, int j, fall fl, fall fr)
{
		if (i > j)
				return 0;
		if (db[i][j][fl][fr] > -1)
				return db[i][j][fl][fr];
		double  result;
		int         temp;
		int         t;

		result = p * (h - coml[i][fl] + 0.5 * (b(i + 1, j, ::left, fr) + e(i + 1, j, ::left, fr)));
		if (cader[i] > j)
				temp = j;
		else
				temp = cader[i];
		if (temp < j)
				t = 0;
		else
				t = comr[temp][fr];
		result += (1 - p) * (v[temp] - v[i] + h - t + 0.5 * (b(temp + 1, j, ::right, fr) + e(temp + 1, j, ::right, fr)));
		return db[i][j][fl][fr] = result;
}

double e(int i, int j, fall fl, fall fr)
{
		if (i > j)
				return 0;
		if (de[i][j][fl][fr] > -1)
				return de[i][j][fl][fr];
		double result;
		int         temp;
		int         t;
		result = (1 - p) * (h - comr[j][fr] + 0.5 * (b(i, j -  1, fl, ::right) + e(i, j - 1, fl, ::right)));
		if (cadel[j] < i)
				temp = i;
		else
				temp = cadel[j];
		if (temp > i)
				t = 0;
		else
				t = coml[temp][fl];
		result += p * (v[j] - v[temp] + h - t + 0.5 * (b(i, temp - 1, fl, ::left) + e(i, temp - 1, fl, ::left)));
		return de[i][j][fl][fr] = result;
}

int         main()
{
		int n;
		int i;

		cin >> n >> h >> p;

		for (i = 1; i <= n; ++i)
			cin >> v[i];

		sort(v + 1, v + n + 1);
		coml[1][::left] = 0;
		coml[1][::right] = 0;
		cadel[1] = 1;
		for (i = 2; i <= n; ++ i)
		{
			coml[i][::left] = h - v[i] + v[i - 1];
			coml[i][::right] = h - v[i] + h + v[i - 1];
			if (coml[i][::left] < 0)
					coml[i][::left] = 0;
			if (coml[i][::right] < 0)
					coml[i][::right] = 0;
			if (v[i] - v[i - 1] < h)
					cadel[i] = cadel[i - 1];
			else
					cadel[i] = i;
		}
		for (i = 1; i < n; ++i)
		{
			comr[i][::left] = h + h - (v[i + 1] - v[i]);
			comr[i][::right] = h - (v[i + 1] - v[i]);
			if (comr[i][::left] < 0)
					comr[i][::left] = 0;
			if (comr[i][::right] < 0)
					comr[i][::right] = 0;
		}
		comr[n][::left] = 0;
		comr[n][::right] = 0;
		cader[n] = n;
		for (i = n - 1; i; --i)
		{
			if (v[i + 1] - v[i] < h)
				cader[i] = cader[i + 1];
			else
				cader[i] = i;
		}
		for (i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				for (int k = 0; k < 2; ++k)
					for (int l = 0; l < 2; ++l)
					{
						db[i][j][k][l] = -1;
						de[i][j][k][l] = -1;
					}
		cout << setprecision(10) << 0.5 * (b(1, n, ::left, ::right) + e(1, n, ::left, ::right));
		    return 0;
}
