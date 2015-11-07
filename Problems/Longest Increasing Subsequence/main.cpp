#include <fstream>
#include <iostream>

const int MAXN = 1000000;

using namespace std;

int N;
int v[MAXN];
int sequence;
int solution[MAXN];
int s[MAXN];
int top;
int r[MAXN];

int		find_position(int el)
{
	int temp;
	int index;

	for (temp = 1; temp <= sequence; temp <<= 1);
	for (index = 0; temp; temp >>= 1)
		if (index + temp <= sequence and v[index + temp] < el)
				index += temp;
	return index;
}

void	insert_element(int i)
{
	int pos;

	pos = find_position(r[i]);
	v[pos + 1] = r[i];
	s[pos + 1] = i;
	if (pos == 0)
		solution[i] = -1;
	else
		solution[i] = s[pos];
	if (pos == sequence)
	{
		top = i;
		++sequence;
	}
}

int		main()
{
	int j;

	ifstream mama("scmax.in");
	ofstream tata("scmax.out");

	mama >> N;
	for (int i = 0; i < N; i += 1)
	{
		mama >> r[i];
		insert_element(i);
	}
	tata << sequence << '\n';
	j = 0;
	for (int i = top; i > -1; j += 1)
	{
		s[j] = r[i];
		i = solution[i];
	}
	j -= 1;
	for (; j > -1; j -= 1)
		tata << s[j] << " ";
	return 0;
}
