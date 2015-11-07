#include <iostream>

using namespace std;

int		problem_one(int n)
{
	//Given a number, determine how many bits equal to 1 it has
	//UNSIGNED

	//Trivial solution
	int res;
	
	res = 0;
	while (n)
	{
		res += n % 2;
		n >>= 1;
	}

	//Observation n & (n - 1) gets rid of the least significant 1
	//01001100 & 01001011 = 01001000
	res = 0;
	while (n)
	{
		n &= n - 1;
		res += 1;
	}

	//If we're dealing with large numbers(64-bit numbers) we can precompute a table
	//of 2^16 numbers, v[i] = number of bits equal to 1 i has
	//the result will be v[b1] + v[b2] + v[b3] + v[b4], where bi is the ith byte of n

	res = v[n & 0xffff] + v[(n >> 16) & 0xffff] + v[(n >> 32) & 0xffff] + v[(n >> 48) & 0xffff];
}

int		problem_two(int n)
{
	//Given a number, check its parity(whether it has an even number of bits equal to 1 or not)
	
	//Trivial
	int res;

	res = 0;
	while (n)
	{
		res += n % 2;
		n >>= 1;
	}

	//Observation: parity(n) = parity(b1) ^ parity(b2), ^ = XOR, b1 = first half, b2 = second half
	
	//n is uint, so it has 32 bits

	n = (n >> 32) ^ (n & 0xffffffff);
	n = (n >> 16) ^ (n & 0xffff);
	n = (n >> 8) ^ (n & 0xff);
	n = (n >> 4) ^ (n & 0xf);
	n = (n >> 2) ^ (n & 3);
	res = n % 2;
}

int		determine_power(int x, int y, int beg, int end)
{
	int middle;

	if (beg == end)
		return beg;
	middle = (beg + end) / 2;
	if (y << middle < y << (middle - 1))
		return determine_power(x, y, beg, middle - 1);
	if (x == y << middle)
		return middle;
	if (x < y << middle)
		return determine_power(x, y, beg, middle - 1);
	return determine_power(x, y, middle + 1, end);
	
}

int		problem_three(int x, int y)
{
	//Given two numbers, determine x/y using only addition, substraction and bit shifting
	
	//Observe that for x >= y, x/y = 2^k + (x - y * 2^k)/y
	
	int res;
	int power;

	res = 0;
	while (x > y)
	{
		//for each value of x, we have to determine k
		power = determine_power(x, y, 0, 63); //unsigned int
		x -= y << power; // x = x - y * 2^k
		res += 1 << power; // res = res + 2^k
	}
}

int		main()
{
	int n;
	int x, y;

	cout <<	problem_one(n);
	cout << problem_two(n);
	cout << problem_three(x, y);
	return 0;
}
