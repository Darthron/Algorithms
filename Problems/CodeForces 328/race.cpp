#include <iostream>

using namespace std;

long long gcd(long long a, long long b)
{
	long long temp;

	if (b == 0)
		return a;
	temp = b;
	b = a % b;
	a = temp;
	return gcd(a, b);
}

int main()
{
	long long cmmdc;
	long long cmmmc;
	long long a;
	long long b;
	long long t;
	long long eq;
	cin >> t;
	cin >> a;
	cin >> b;
	cmmdc = gcd(a, b);
	cmmmc = cmmdc * (a / cmmdc) * (b / cmmdc);
	eq = (t / cmmmc) * (min(a, b)) - 1;
	eq += min(t - (t / cmmmc) * cmmmc + 1, min(a, b));
	cmmdc = gcd(eq, t);
	eq /= cmmdc;
	t /= cmmdc;
	cout << eq << "/" << t;
	return 0;
}
