#include <fstream>
#include <stdlib.h>

struct value {
	int val;
	value *next;
};

value* hash[12582917];

value*	find(int a, int b)
{
	value* it;

	it = hash[b];
	while (it && it -> val != a)
		it = it -> next;
	return it;
}

value*	createEntry(int a, value* b)
{
	value *r;

	r = new(value);
	r -> next = b;
	r -> val = a;
	return r;
}

int	main()
{
	std::ifstream mama("hashuri.in");
	std::ofstream tata("hashuri.out");

	int	n;
	int	a;
	int	op;
	int	b;
	value	*findReturn;
	value	*r;

	mama >> n;
	for (int i = 0; i < n; i += 1)
	{
		mama >>	op >> a;
		b = a % 12582917;
		findReturn = find(a, b);
		if (op == 1 && !findReturn)
		{
			r = createEntry(a, hash[b]);
			hash[b] = r;
		}
		else if (op == 2 && findReturn)
		{
			if (hash[b] == findReturn)
				hash[b] = findReturn -> next;
			else
			{
				value *s;
		
				s = hash[b];
				while (s -> next -> val != a)
					s = s -> next;
				s -> next = s -> next -> next;
			}
		}
		else if (op == 3)
		{
			if (findReturn)
				tata << 1 << '\n';
			else
				tata << 0 << '\n';
		}
	}
	return 0;
}
