/*
ID: razvan_10
PROG: namenum
LANG: C++11
*/

#include <fstream>
#include <set>
#include <iostream>
#include <string.h>

std::ifstream mama("namenum.in");
std::ofstream tata("namenum.out");
std::ifstream dict("dict.txt");

const char              letters[8][3] = { {'A', 'B', 'C'}, {'D', 'E', 'F'}, {'G', 'H', 'I'}, {'J', 'K', 'L'}, {'M', 'N', 'O'}, {'P', 'R', 'S'}, {'T', 'U', 'V'}, {'W', 'X', 'Y'} };
int                     res[12];
bool                    none;
std::string             str;
std::set <std::string>  dictionary;

void
check()
{
    std::string name;

    name = "";

    for (unsigned int index = 0; index < str.size(); ++index)
    {
        name += letters[str[index] - '2'][res[index]];
    }

    if (dictionary.count(name))
    {
        none = false;
        tata << name << std::endl;
    }
}

void
gogogo()
{
    int index;
    int size;

    size = str.size();
    memset(res, -1, 48);

    index = 0;
    while (index > -1)
    {
        ++res[index];

        ++index;
        if (index == size)
        {
            check();

            while ( (index > -1) and
                    (2 == res[--index]) )
            {
                res[index] = -1;
            }
        }
    }

}

int main()
{
    std::string name;

    mama >> str;

    none = true;
    while ( (dict >> name) )
    {
        dictionary.insert(name);
    }

    gogogo();

    if (none)
    {
        tata << "NONE" << std::endl;
    }

    return 0;
}
