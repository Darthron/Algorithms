#include <fstream>
#include <stack>
#include <deque>
#include <iostream>

using namespace std;

int main()
{
	int				k;
	char			op;
	string			title;
	int				counter;
	bool			direction;
	deque<string>	q;
	stack<string>	s;

	ifstream mama("books.in");
	ofstream tata("books.out");

	mama >> k;
	counter = 0;
	direction = 0;
	while (mama >> op)
	{
		if (op == '0')
		{
			mama >> title;
			if (!direction)
			{
				if (counter < k)
					q.push_back(title);
				else
				{
					string temp;
					
					temp = q.front();
					q.pop_front();
					s.push(temp);
					q.push_back(title);				
				}
			}
			else
			{
				if (counter < k)
					q.push_front(title);
				else
				{
					string temp;

					temp = q.back();
					q.pop_back();
					s.push(temp);
					q.push_front(title);
				}
			}
			++counter;
		}
		else if (op == '1')
		{
			if (!direction)
			{
				tata << q.back() << '\n';
				if (counter <= k)
					q.pop_back();
				else
				{
					string temp;

					q.pop_back();
					temp = s.top();
					s.pop();
					q.push_front(temp);
				}
			}
			else
			{
				tata << q.front() << '\n';
				if (counter <= k)
					q.pop_front();
				else
				{
					string temp;

					q.pop_front();
					temp = s.top();
					s.pop();
					q.push_back(temp);
				}
			}
			--counter;
		}
		else if (op == '2')
			direction = !direction;
	}
	return 0;
}
