/*
ID: razvan_10
PROG: transform
LANG: C++11
*/

#include <fstream>
#include <iostream>

char temp[10][10];
char mat[10][10];
char out[10][10];
int n;

std::ifstream mama("transform.in");
std::ofstream tata("transform.out");

bool
equals()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (temp[i][j] != out[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

void
rot90()
{
    int i;
    int j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            temp[j][n - 1 - i] = mat[i][j];
        }
    }

    if (equals())
    {
        tata << 1 << std::endl;
        exit(0);
    }

}

void
rot180()
{
    int i;
    int j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            temp[n - 1 - i][n - 1 - j] = mat[i][j];
        }
    }

    if (equals())
    {
        tata << 2 << std::endl;
        exit(0);
    }
}

void
rot270()
{
    int i;
    int j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            temp[n - 1 - j][i] = mat[i][j];
        }
    }

    if (equals())
    {
        tata << 3 << std::endl;
        exit(0);
    }
}

void
ref()
{
    int i;
    int j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            temp[i][n - 1 - j] = mat[i][j];
        }
    }

    if (equals())
    {
        tata << 4 << std::endl;
        exit(0);
    }
}

void
comb()
{
    int i;
    int j;
       

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            temp[i][n - 1 - j] = mat[i][j];
        }
    }
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            mat[i][j] = temp[i][j];
        }
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            temp[j][n - 1 - i] = mat[i][j];
        }
    }

    if (equals())
    {
        tata << 5 << std::endl;
        exit(0);
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            mat[i][j] = temp[i][j];
        }
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            temp[j][n - 1 - i] = mat[i][j];
        }
    }

    if (equals())
    {
        tata << 5 << std::endl;
        exit(0);
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            mat[i][j] = temp[i][j];
        }
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            temp[j][n - 1 - i] = mat[i][j];
        }
    }

    if (equals())
    {
        tata << 5 << std::endl;
        exit(0);
    }
}

int main()
{
    bool ok;
    int index;
    int jndex;

    mama >> n;
    for (index = 0; index < n; ++index)
    {
        for (jndex = 0; jndex < n; ++jndex)
        {
            mama >> mat[index][jndex];
        }
    }

    for (index = 0; index < n; ++index)
    {
        for (jndex = 0; jndex < n; ++jndex)
        {
            mama >> out[index][jndex];
        }
    }

    ok = true;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (mat[i][j] != out[i][j])
            {
                ok = false;
            }
        }
    }


    rot90();
    rot180();
    rot270();
    ref();
    comb();
    if (ok)
    {
        tata << 6 << std::endl;
        return 0;
    }

    tata << 7 << std::endl;

    return 0;
}
