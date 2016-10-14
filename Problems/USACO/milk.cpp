/*
ID: razvan_10
PROG: milk
LANG: C++11
*/

#include <fstream>
#include <algorithm>

struct Milk
{
    int cost;
    int quantity;
};

int main()
{
    std::ifstream mama("milk.in");
    std::ofstream tata("milk.out");

    Milk farmers[5001];
    int  n;
    int  m;
    int  index;
    int  s;
    int  min;

    mama >> n;
    mama >> m;

    for (index = 0; index < m; ++index)
    {
        mama >> farmers[index].cost;
        mama >> farmers[index].quantity;
    }

    std::sort(std::begin(farmers),
              std::begin(farmers) + m,
              [](const Milk& a, const Milk& b)
              {
                  return (a.cost < b.cost);
              });


    index = 0;
    s = 0;
    while (n)
    {
        min = std::min(n, farmers[index].quantity);

        s += farmers[index].cost * min;
        n -= min;
        ++index;
    }

    tata << s << std::endl;

    return 0;
}
