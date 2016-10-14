/*
ID: razvan_10
PROG: palsquare
LANG: C++11
*/

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string.h>

const char                      digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
int                             b;
char                            num[100] = {1, '1'};
char                            square[100] = {0};
char                            temp1[100];
char                            temp2[100];
std::unordered_map <char, int>  digVal;

void
nextNum()
{
    int c;
    int index;

    if (digVal[num[1]] + 1 >= b)
    {
        c = 1;
        num[1] = '0';
    }
    else
    {
        num[1] = digits[digVal[num[1]] + 1];
        return;
    }
    
    index = 2;
    while ( (index <= num[0]) and
            (c) )
    {
        if (digVal[num[index]] == b - 1)
        {
            num[index] = '0';
        }
        else
        {
            num[index] = digits[digVal[num[index]] + 1];
            c = 0;
        }
        ++index;
    }
    
    if (c)
    {
        num[(int)num[0] + 1] = '1';
        ++num[0];
    }
}

bool
squarePalindrome()
{
    int c;
    int index;
    int tempIndex;
    int calibre;

    index = 1;
    c = 0;
    while (index <= num[0])
    {
        int tempC = (digVal[num[1]] * digVal[num[index]] + c) / b;

        temp1[index] = digits[(digVal[num[1]] * digVal[num[index]] + c) % b];
        c = tempC;
        ++index;
    }
    if (c)
    {
        temp1[index] = digits[c];
        temp1[0] = num[0] + 1;
        c = 0;
    }
    else
    {
        temp1[0] = num[0];
    }

    for (index = 2, calibre = 1; index <= num[0]; ++index, ++calibre)
    {
        tempIndex = 1;
        c = 0;
        temp2[calibre] = 0;
        while (tempIndex <= num[0])
        {
            int tempC = (digVal[num[index]] * digVal[num[tempIndex]] + c) / b;

            temp2[tempIndex + calibre] = digits[(digVal[num[index]] * digVal[num[tempIndex]] + c) % b];
            c = tempC;
            ++tempIndex;
        }
        if (c)
        {
            temp2[tempIndex + calibre] = digits[c];
            temp2[0] = num[0] + 1 + calibre;
            c = 0;
        }
        else
        {
            temp2[0] = num[0] + calibre;
        }

        for (c = 0, tempIndex = 1; tempIndex <= temp2[0]; ++tempIndex)
        {
            int tempC = (digVal[temp1[tempIndex]] + digVal[temp2[tempIndex]] + c) / b;
            temp1[tempIndex] = digits[(digVal[temp1[tempIndex]] + digVal[temp2[tempIndex]] + c) % b];
            c = tempC;
        }
        if (c)
        {
            temp1[tempIndex] = digits[c];
            temp1[0] = temp2[0] + 1;
        }
        else
        {
            temp1[0] = temp2[0];
        }
    }

    for (index = (int) temp1[0]; (temp1[index] == 0) or (temp1[index] == '0'); --index)
    {
        --temp1[0];
    }

    for (index = 1; index <= temp1[0] / 2; ++index)
    {
        if (temp1[index] != temp1[temp1[0] + 1 - index])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::ifstream mama("palsquare.in");
    std::ofstream tata("palsquare.out");

    int index;

    mama >> b;

    for (index = 0; index < 10; ++index)
    {
        digVal['0' + index] = index;
        digVal['A' + index] = index + 10;
    }

    for (index = 0; index < 1300; ++index)
    {
        if (squarePalindrome())
        {
            for (int index = (int) num[0]; index > 0; --index)
            {
                tata << num[index];
            }
            tata << ' ';
            for (int index = 1; index <= (int) temp1[0]; ++index)
            {
                tata << temp1[index];
            }
            tata << std::endl;
        }
        memset(temp1, 0, 100);
        memset(temp2, 0, 100);
        nextNum();
    }
        
    squarePalindrome();

    return 0;
}
