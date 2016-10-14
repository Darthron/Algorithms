// http://www.infoarena.ro/problema/evaluare

#include <cstdio>

const int   MAX_LENGTH = 100001;
char        str[MAX_LENGTH];
const char* pStr = str;
const int   MAX_PRIORITY = 2;

long
termen();

long
factor();

// Deals with addition and subtraction

long
eval()
{
    long res;

    res = termen();
    while ( (*pStr == '+') or
            (*pStr == '-') )
    {
        if (*pStr == '+')
        {
            pStr++;
            res += termen();
        }
        else
        {
            pStr++;
            res -= termen();
        }
    }

    return res;
}

// Deals with multiplication and division

long
termen()
{
    long res;

    res = factor();
    while ( (*pStr == '*') or
            (*pStr == '/') )
    {
        if (*pStr == '*')
        {
            pStr++;
            res *= factor();
        }
        else
        {
            pStr++;
            res /= factor();
        }
    }

    return res;
}

// Yields a number representing the result of an expression, either enclosed by brackets or a number

long
factor()
{
    long res;

    res = 0;
    if (*pStr == '(')
    {
        pStr++;
        res = eval();
        pStr++; // Jumps over the closing bracket
    }
    else
    {
        while ( (*pStr >= '0') and
                (*pStr <= '9') )
        {
            res = res * 10 + *pStr - '0';
            pStr++;
        }
    }

    return res;
}

int main()
{
    fgets(str, MAX_LENGTH, fopen("evaluare.in", "r"));
    fprintf(fopen("evaluare.out", "w"), "%ld\n", eval());

    return 0;
}
