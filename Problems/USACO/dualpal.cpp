/*
ID: razvan_10
PROG: dualpal
LANG: C++11
*/

#include <fstream>

int b;

bool
palindrome(int num)
{
    char number[35];
    int  index;

    index = 0;
    while (num)
    {
        number[index] = '0' + (num % b);
        num /= b;
        ++index;
    }

    for (int i = 0; i < index / 2; ++i)
    {
        if (number[i] != number[index - 1 - i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::ifstream mama("dualpal.in");
    std::ofstream tata("dualpal.out");

    int n;
    int s;
    int index;
    int count;

    mama >> n;
    mama >> s;


    for (count = 0, index = s + 1; n > 0; count = 0, ++index)
    {
        for (b = 2; b < 11 and count < 2; ++b)
        {
            if (palindrome(index))
            {
                ++count;
            }
        }

        if (2 == count)
        {
            --n;
            tata << index << std::endl;
        }
    }

    return 0;
}
