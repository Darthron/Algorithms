/*
ID: razvan_10
PROG: barn1
LANG: C++11
*/

#include <fstream>
#include <string.h>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

std::ifstream mama("barn1.in");
std::ofstream tata("barn1.out");

struct Seq
{
    int beg;
    int end;
};

bool
cmp(const Seq& a, const Seq& b)
{
    return (a.end - a.beg) < (b.end - b.beg);
}

std::priority_queue <Seq, std::vector <Seq>, std::function <bool(Seq, Seq)>> q(cmp);

int main()
{
    int  m;
    int  s;
    int  c;
    int  index;
    int  stall;
    int  tempIndex;
    int  occStalls;
    int  firstOccupied;
    int  lastOccupied;
    Seq  seq;
    bool occupied[201];

    mama >> m;
    mama >> s;
    mama >> c;

    memset(occupied, 0, 201);

    for (index = 0; index < c; ++index)
    {
        mama >> stall;
        occupied[stall] = true;
    }

    if (m >= c)
    {
        tata << c << std::endl;
        return 0;
    }

    index = 1;
    occStalls = s;
    while ( (index <= s) and
            (not occupied[index]) )
    {
        ++index;
        --occStalls;
    }
    
    firstOccupied = index;
    lastOccupied = index;
    if (occStalls)
    {
        index = s;
        while ( (index > 0) and
                (not occupied[index]) )
        {
            --index;
            --occStalls;
        }

        lastOccupied = index;
    }

    index = firstOccupied;
    while (index <= s)
    {
        while ( (index <= s) and
                (occupied[index]) )
        {
            ++index;
        }

        tempIndex = index + 1;
        while ( (tempIndex <= s) and
                (not occupied[tempIndex]) )
        {
            ++tempIndex;
        }

        if (index > lastOccupied)
        {
            break;
        }

        seq.beg = index;
        seq.end = tempIndex;
        q.push(seq);

        index = tempIndex;
    }

    /*while (not q.empty())
    {
        seq = q.top();
        q.pop();

        std::cout << seq.beg << ' ' << seq.end << std::endl;
    }*/

    while (m > 1)
    {
        seq = q.top();
        q.pop();

        occStalls -= seq.end - seq.beg;
        --m;
    }

    tata << occStalls << std::endl;

    return 0;
}
