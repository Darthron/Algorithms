//Given two strings of characters, one having distinct characters, print the letters from the first string in the order they appear in the second one

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>

using namespace std;

bool cmp(pair<char, int> a, pair<char, int> b)
{
	return a.second > b.second;
}

int		main()
{
	char S[1000];
	int  alpha[26];
	char chars[27];
	int  length;

	cin.getline(S, 1000);
	cin.getline(chars, 27);
	memset(alpha, 0, sizeof(alpha));

	length = strlen(chars);
	for (int i = 0, counter = 1; i < length; i += 1)
		if (!alpha[chars[i] - 'a'])
			alpha[chars[i] - 'a'] = counter++;
	priority_queue<pair<char, int>, vector< pair<char, int> >, decltype(&cmp)> q(&cmp);
	length = strlen(S);
	for (int i = 0; i < length; i += 1)
		q.push(make_pair(S[i], alpha[S[i] - 'a']));
	while (!q.empty())
	{
		cout << q.top().first;
		q.pop();
	}
	return 0;
}
