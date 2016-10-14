/*
ID: razvan_10
PROG: beads
LANG: C++11
*/

#include <fstream>
#include <iostream>

std::ifstream mama("beads.in");
std::ofstream tata("beads.out");

bool
equals(const char& a,
       const char& b)
{
    if ( (a == b) or
         ('w' == b) )
    {
        return true;
    }

    return false;
}

int main()
{
    int         right[350] = {0};
    int         left[350] = {0};
    int         N;
    int         index;
    int         tempIndex;
    int         max;
    char        tempChar;
    std::string str;

    mama >> N;
    mama >> str;

    if (str[0] == 'w')
    {
        tempIndex = 1;
        while ( (tempIndex < N) and
                ('w' == str[tempIndex]) )
        {
            ++tempIndex;
        }

        index = tempIndex;
        while ( (tempIndex < N) and
                (str[index] == str[tempIndex]) )
        {
            ++tempIndex;
        }

        right[0] = tempIndex - 1;
    }
    else
    {
        index = 0;
        while ( (index < N) and
                (equals(str[0],
                        str[index])) )
        {
            ++index;
        }

        right[0] = index - 1;
    }

    if (str[N - 1] == 'w')
    {
        tempIndex = N - 2;
        while ( (tempIndex >= 0) and
                ('w' == str[tempIndex]) )
        {
            ++tempIndex;
        }

        index = tempIndex;
        while ( (tempIndex >= 0) and
                (str[index] == str[tempIndex]) )
        {
            ++tempIndex;
        }

        left[N - 1] = N - tempIndex - 1;
    }
    else
    {
        index = N - 2;
        while ( (index >= 0) and
                (equals(str[N - 1],
                        str[index])) )
        {
            --index;
        }

        left[N - 1] = N - index - 2;
    }

    for (index = 1; index < N; ++index)
    {
        if ( (str[index] == str[index - 1]) or
             ('w' == str[index - 1]) )
        {
            right[index] = std::max(right[index - 1] - 1, 0);
        }
        else if ('w' == str[index])
        {
            tempIndex = (index + 1) % N;
            while ( (tempIndex != index) and
                    ('w' == str[tempIndex]) )
            {
                ++right[index];
                ++tempIndex;

                if (tempIndex == N)
                {
                    tempIndex = 0;
                }
            }

            tempChar = str[tempIndex];
            while ( (tempIndex != index) and
                    (equals(tempChar,
                            str[tempIndex])) )
            {
                ++right[index];
                ++tempIndex;

                if (tempIndex == N)
                {
                    tempIndex = 0;
                }
            }
        }
        else
        {
            tempIndex = (index + 1) % N;
            while ( (tempIndex != index) and
                    (equals(str[index],
                            str[tempIndex])) )
            {
                ++right[index];
                ++tempIndex;

                if (tempIndex == N)
                {
                    tempIndex = 0;
                }
            }
        }
    }

    for (index = N - 2; index >= 0; --index)
    {
        if ( (str[index] == str[index + 1]) or
             ('w' == str[index + 1]) )
        {
            left[index] = std::max(left[index + 1] - 1, 0);
        }
        else if ('w' == str[index])
        {
            tempIndex = (0 == index) ? (N - 1) : (index - 1);
            while ( (tempIndex != index) and
                    ('w' == str[tempIndex]) )
            {
                ++left[index];
                --tempIndex;

                if (-1 == tempIndex)
                {
                    tempIndex = N - 1;
                }
            }

            tempChar = str[tempIndex];
            while ( (tempIndex != index) and
                    (equals(tempChar,
                            str[tempIndex])) )
            {
                ++left[index];
                --tempIndex;

                if (-1 == tempIndex)
                {
                    tempIndex = N - 1;
                }
            }
        }
        else
        {
            tempIndex = (0 == index) ? (N - 1) : (index - 1);
            while ( (tempIndex != index) and
                    (equals(str[index],
                            str[tempIndex])) )
            {
                ++left[index];
                --tempIndex;

                if (-1 == tempIndex)
                {
                    tempIndex = N - 1;
                }
            }
        }
    }

    max = left[N - 1] + right[0];
    for (index = 1; index < N; ++index)
    {
        max = std::max(max, left[index - 1] + right[index]);
    }

    tata << std::min(N, max + 2) << std::endl;

    return 0;
}
