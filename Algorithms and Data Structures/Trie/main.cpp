#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

struct node
{
	int appearances;
	int nr;
	node	*suffixes[26];
	node()
	{
		nr = 0;
		appearances = 0;
		memset(suffixes, 0, sizeof(suffixes));
	}
};

node	*p;

void	insert(node *n, char w[])
{
	if (!w[0])
	{
		n -> nr += 1;
		n -> appearances += 1;
		return;
	}
	if (n -> suffixes[w[0] - 'a'] == 0)
	{
		n -> suffixes[w[0] - 'a'] = new node;
	}
	n -> nr += 1;
	insert(n -> suffixes[w[0] - 'a'], w + 1);
}

bool	del(node *n, char w[])
{
	if (!w[0])
	{
		if (!(n -> nr -= 1))
		{
			delete n;
			return 1;
		}
		n -> appearances -= 1;
		return 0;
	}
	if (del(n -> suffixes[w[0] - 'a'], w + 1))
		n -> suffixes[w[0] - 'a'] = 0;
	if (n != p and !(n -> nr -= 1))
	{
		delete n;
		return 1;
	}
	return 0;
	/*if (w.length() == 1)
	{
		n -> suffixes[w[0] - 'a'] -> nr -= 1;
		n -> suffixes[w[0] - 'a'] -> appearances -= 1;
		if (n -> suffixes[w[0] - 'a'] -> nr == 0)
		{
			n -> suffixes[w[0] - 'a'] = 0;
			delete n -> suffixes[w[0] - 'a'];
		}
		return;
	}
	del(n -> suffixes[w[0] - 'a'], w.substr(1));
	n -> suffixes[w[0] - 'a'] -> nr -= 1;
	if (n != p and n -> suffixes[w[0] - 'a'] -> nr == 0)
	{
		n -> suffixes[w[0] - 'a'] = 0;
		delete n -> suffixes[w[0] - 'a'];
	}*/	
}

int		appear(node *b, char w[])
{
	if (!w[0])
		return b -> appearances;
	if (b -> suffixes[w[0] - 'a'])
		return appear(b -> suffixes[w[0] - 'a'], w + 1);
	return 0;
}

int		prefix(node *b, char w[])
{
	if (!w[0])
		return 0;
	if (b -> suffixes[w[0] - 'a'] == 0)
		return 0;
	return 1 + prefix(b -> suffixes[w[0] - 'a'], w + 1);
}

int		main()
{
	char	s[26];
	int		op;
	node	base;

	ifstream mama("trie.in");
	ofstream tata("trie.out");
	base.nr = 0;
	p = &base;
	while (mama >> op)
	{
		mama >> s;
		if (op == 0)
			insert(&base, s);
		else if (op == 1)
			del(&base, s);
		else if (op == 2)
			tata << appear(&base, s) << '\n';
		else if (op == 3)
			tata << prefix(&base, s) << '\n';
	}
	return 0;
}
