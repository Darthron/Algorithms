/*
ID: razvan_10
PROG: milk2
LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <iostream>

std::ifstream mama("milk2.in");
std::ofstream tata("milk2.out");

struct Farmer
{
    int beg;
    int end;
};

int main()
{
    Farmer  arr[5000];
    int     index;
    int     n;
    int     finishMax;
    int     tempIndex;
    int     max;
    
    mama >> n;
    for (index = 0; index < n; ++index)
    {
        mama >> arr[index].beg;
        mama >> arr[index].end;
    }

    std::sort(arr,
              arr + n,
              [](const Farmer& a, const Farmer& b)
              {
                  return ( (a.beg < b.beg) or ( (a.beg == b.beg) and (a.end <= b.end) ) );
              });

    tempIndex = 1;
    finishMax = arr[0].end;
    while ( (tempIndex < n) and
            (arr[tempIndex].beg <= finishMax) )
    {
        if (arr[tempIndex].end > finishMax)
        {
            finishMax = arr[tempIndex].end;
        }

        ++tempIndex;
    }

    max = finishMax - arr[0].beg;
    while ( (index = tempIndex) < n)
    {
        finishMax = arr[index].end;
        tempIndex = index + 1;
        while ( (tempIndex < n) and
                (arr[tempIndex].beg <= finishMax) )
        {
            if (arr[tempIndex].end > finishMax)
            {
                finishMax = arr[tempIndex].end;
            }

            ++tempIndex;
        }

        max = std::max(finishMax - arr[index].beg,
                       max);
    }


    tata << max << ' ';

    if (1 == n)
    {
        tata << 0 << std::endl;
    }
    else
    {
        max = 0;
        finishMax = arr[0].end;
        for (index = 1; index < n; ++index)
        {
            max = std::max(arr[index].beg - finishMax,
                           max);
            if (arr[index].end > finishMax)
            {
                finishMax = arr[index].end;
            }
        }

        tata << max << std::endl;
    }

    return 0;
}
