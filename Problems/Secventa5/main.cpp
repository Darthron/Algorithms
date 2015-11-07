//http://www.infoarena.ro/problema/secv5

#include <fstream>
#include <iostream>

#define MOD 12582917
using namespace std;

struct element {
	unsigned int val;
	unsigned int position;
	element *next;
};

element *hassh[MOD];
unsigned int N, L, U;
unsigned int *v;

bool exists(unsigned int value, unsigned int low, unsigned int up)
{
	unsigned int pos;
	element *el;

	pos = value % MOD;
	el = hassh[pos];
	while (el and el -> val != value)
		el = el -> next;
	while (el and el -> val == value and el -> position <= up)
	{
		if (el -> position >= low and el -> position <= up)
			return true;
		el = el -> next;
	}
	return false;
}

unsigned int secv(unsigned int lower, unsigned int upper, bool up, bool down, unsigned int different)
{
	unsigned res;
	int fix;

	fix = 0;
	if (up)
		fix = 1;
	if (upper >= N)
		return 0;
	res = 0;
	if (down)
		if (!exists(v[lower - 1], lower, upper - fix))
			different -= 1;
	if (up)
		if (!exists(v[upper], lower, upper - fix))
			different += 1;
	if (different > U)
	{
		return 0;
	}
	if (different >= L and different <= U)
	{
		res = 1;
	}
	res += secv(lower, upper + 1, true, false, different);
	if (upper - lower == L - 1)
		res += secv(lower + 1, upper + 1, true, true, different);
	return res;	
}

element *createElement(unsigned int v, unsigned int p)
{
	element *e;

	e = new(element);
	e -> val = v;
	e -> position = p;
	return e;
}

void insertInHash(unsigned int i, unsigned int value, unsigned int position)
{
	element *el;
	element *temp;
	element *elem;

	if (hassh[i] == NULL)
	{
		hassh[i] = createElement(value, position);
		hassh[i] -> next = NULL;
		return;
	}
	el = hassh[i];
	temp = hassh[i];
	while (temp and temp -> val != value)
	{
		el = temp;
		temp = temp -> next;
	}
	while (temp and temp -> val == value)
	{
		el = temp;
		temp = temp -> next;
	}
	elem = createElement(value, position);
	elem -> next = el -> next;
	el -> next = elem;
}

void buildHash(unsigned int value, unsigned int position)
{
	unsigned int positionInHash;

	positionInHash = value % MOD;
	insertInHash(positionInHash, value, position);
}

int main()
{
	ifstream mama("secv5.in");
	ofstream tata("secv5.out");

	unsigned int different;

	different = 1;
	mama >> N;
	mama >> L;
	mama >> U;

	v = new unsigned int[N];
	for (unsigned int i = 0; i < N; i += 1)
	{
		mama >> v[i];
		buildHash(v[i], i);
	}
	for (unsigned int i = 1; i < L; i += 1)
		if (!exists(v[i], 0, i - 1))
			different += 1;
	tata << secv(0, L - 1, false, false, different);
	return 0;
}
