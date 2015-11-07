#include <fstream>
#include <string.h>
#include <iostream>

#define MAXN 2000001
#define	MOD1 100007
#define MOD2 100021

using namespace std;

char pattern[MAXN], text[MAXN];
int hash1, hash2;
int hasht1, hasht2;
int position[MAXN];

int main()
{
	int n;
	int m;
	int i;
	int power1, power2;
	int counter;

	ifstream mama("strmatch.in");
	ofstream tata("strmatch.out");

	mama.getline(pattern, MAXN);
	mama.getline(text, MAXN);
	
	counter = 0;
	n = strlen(pattern);
	m = strlen(text);
	if (n > m)
	{
		tata << 0;
		return 0;
	}
	power1 = 1;
	power2 = 1;
	hash1 = (hash1 * 73 + pattern[0]) % MOD1;
	hash2 = (hash2 * 73 + pattern[0]) % MOD2;	
	for (i = 1; i < n; i += 1)
	{
		hash1 = (hash1 * 73 + pattern[i]) % MOD1;
		hash2 = (hash2 * 73 + pattern[i]) % MOD2;
		power1 = (power1 * 73) % MOD1;
		power2 = (power2 * 73) % MOD2;
	}
	for (i = 0; i < n; i += 1)
	{
		hasht1 = (hasht1 * 73 + text[i]) % MOD1;
		hasht2 = (hasht2 * 73 + text[i]) % MOD2;
	}
	if (hash1 == hasht1 and hash2 == hasht2)
		position[counter++] = 0;	
	m = m - n + 1;
	for (i = 1; i < m; i += 1)
	{
		hasht1 = ((hasht1 - (text[i - 1] * power1) % MOD1 + MOD1) * 73 + text[i + n - 1]) % MOD1;
		hasht2 = ((hasht2 - (text[i - 1] * power2) % MOD2 + MOD2) * 73 + text[i + n - 1]) % MOD2;
		if (hash1 == hasht1 and hash2 == hasht2)
			position[counter++] = i;
	}
	tata << counter << '\n';
	for (i = 0; i < counter && i < 1000; i += 1)
		tata << position[i] << " ";
	return 0;
}
