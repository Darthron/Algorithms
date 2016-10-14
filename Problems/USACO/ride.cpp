/*
ID: razvan_10
PROG: ride
LANG: C++
*/

#include <fstream>

std::ifstream mama("ride.in");
std::ofstream tata("ride.out");

int main()
{
    char c;
    int  comet;
    int  ufo;

    comet = 1;
    while (mama.get(c))
    {
        if ('\n' == c)
        {
            break;
        }

        comet *= c - 64;
        comet %= 47;
    }

    ufo = 1;
    while (mama.get(c))
    {
        if ('\n' == c)
        {
            break;
        }

        ufo *= c - 64;
        ufo %= 47;
    }

    if (ufo == comet)
    {
        tata << "GO" << std::endl;
    }
    else
    {
        tata << "STAY" << std::endl;
    }

    return 0;
}
