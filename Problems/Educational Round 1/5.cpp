#include <iostream>
#include <queue>
#include <fstream>
#include <string.h>
#include <cstdio>

using namespace std;

ifstream mama("b.in");

const int MAXN = 1005;
const int gox[] = {0, 1, 0, -1};
const int goy[] = {1, 0, -1, 0};
int		  n, m;
char	  mat[MAXN][MAXN];
int		  pictures[MAXN][MAXN];
bool	  visited[MAXN][MAXN], vis[MAXN][MAXN];
bool	  v[MAXN][MAXN];

int		seePictures(int x, int y)
{
	queue<pair<int, int>>	q;
	int						result;
	
	q.push(make_pair(x, y));
	result = 0;
	visited[x][y] = true;
	while (!q.empty())
	{
		pair<int, int> pos;

		pos = q.front();
		q.pop();
		x = pos.first;
		y = pos.second;
		for (int i = 0; i < 4; ++i)
		{
			if (mat[x + gox[i]][y + goy[i]] == '.' and !visited[x + gox[i]][y + goy[i]])
			{
				visited[x + gox[i]][y + goy[i]] = true;
				q.push(make_pair(x + gox[i], y + goy[i]));
			}
		}		
		result += pictures[x][y];
	}
	return result;
}

void	fill(int x, int y)
{
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	int val = pictures[x][y];
	vis[x][y] = true;
	
	while (!q.empty())
	{
		pair<int, int> pos;

		pos = q.front();
		q.pop();
		x = pos.first;
		y = pos.second;
		pictures[x][y] = val;
		for (int i = 0; i < 4; ++i)
			if (mat[x + gox[i]][y + goy[i]] == '.' and !vis[x + gox[i]][y + goy[i]])
			{
				vis[x + gox[i]][y + goy[i]] = true;
				q.push(make_pair(x + gox[i], y + goy[i]));
			}
	}
}

void	countPictures(int x, int y)
{
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	v[x][y] = true;
	
	while (!q.empty())
	{
		pair<int, int> pos;

		pos = q.front();
		q.pop();
		x = pos.first;
		y = pos.second;
		for (int i = 0; i < 4; ++i)
			if (mat[x + gox[i]][y + goy[i]] == '*')
				++pictures[x][y];
			else if (!v[x + gox[i]][y + goy[i]])
			{
				v[x + gox[i]][y + goy[i]] = true;
				q.push(make_pair(x + gox[i], y + goy[i]));
			}
	}
}

int		main()
{
	int k;

	//mama >> n >> m >> k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; ++i)
			//mama >> mat[i];
		scanf("%s", mat[i]);
	for (int i = 0, x, y; i < k; ++i)
	{
		//mama >> x >> y;
		scanf("%d%d", &x, &y);
		if (!vis[x - 1][y - 1])
		{
			countPictures(x - 1, y - 1);
			pictures[x - 1][y - 1] = seePictures(x - 1, y - 1);
			fill(x - 1, y - 1);
		}
		printf("%d\n", pictures[x - 1][y - 1]);
	}
	return 0;
}
