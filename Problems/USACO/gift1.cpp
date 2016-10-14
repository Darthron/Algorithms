/*
ID: razvan_10
PROG: gift1
LANG: C++11
*/

#include <fstream>
#include <unordered_map>
#include <vector>

std::ifstream mama("gift1.in");
std::ofstream tata("gift1.out");

int main()
{
    std::unordered_map <std::string, int> people;
    std::vector <std::string>             peopleOrder;
    int                                   n;
    std::string                           name;
    int                                   index;
    int                                   sum;
    int                                   receivers;
    int                                   gift;

    mama >> n;

    for (index = 0; index < n; ++index)
    {
        mama >> name;

        peopleOrder.push_back(name);
        people[name] = 0;
    }

    for (index = 0; index < n; ++index)
    {
        mama >> name;
        mama >> sum;
        mama >> receivers;

        if (receivers)
        {
            gift = sum / receivers;
        }

        people[name] -= sum;
        people[name] += sum - gift * receivers;

        for (int tempIndex = 0; tempIndex < receivers; ++tempIndex)
        {
            mama >> name;
            people[name] += gift;
        }
    }

    for (const std::string& name : peopleOrder)
    {
        tata << name << " " << people[name] << std::endl;
    }

    return 0;
}
