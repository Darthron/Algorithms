/*
ID: razvan_10
PROG: test
LANG: C++
*/

#include <fstream>

int main()
{
    std::ifstream mama("test.in");
    std::ofstream tata("test.out");

    int a;
    int b;

    mama >> a;
    mama >> b;

    tata << a + b << std::endl;

    return 0;
}
