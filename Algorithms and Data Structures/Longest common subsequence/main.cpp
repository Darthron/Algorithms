// http://www.infoarena.ro/problema/cmlsc

#include <fstream>

std::ifstream mama("cmlsc.in");
std::ofstream tata("cmlsc.out");

int lcs[1024][1024];

void
buildLCSMatrix(int* v1,
               int length1,
               int* v2,
               int length2)
{
    int i;
    int j;

    // Building the first row and column
    lcs[0][0] = (v1[0] == v2[0]) ? 1 : 0;

    for (j = 1; j < length2; j++)
    {
        lcs[0][j] = (v1[0] == v2[j]) ? 1 : lcs[0][j - 1];
    }

    for (i = 1; i < length1; i++)
    {
        lcs[i][0] = (v2[0] == v1[i]) ? 1 : lcs[i - 1][0];
    }

    // Building the rest of the matrix
    for (i = 1; i < length1; i++)
    {
        for (j = 1; j < length2; j++)
        {
            if (v1[i] == v2[j])
            {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            }
            else
            {
                lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }
}

int main()
{
    int length1;
    int length2;
    int v1[1024];
    int v2[1024];
    int sol[1024];
    int index;
    int i;
    int j;

    mama >> length1;
    mama >> length2;

    for (index = 0; index < length1; index++)
    {
        mama >> v1[index];
    }

    for (index = 0; index < length2; index++)
    {
        mama >> v2[index];
    }

    buildLCSMatrix(v1,
                   length1,
                   v2,
                   length2);
    
    index = lcs[length1 - 1][length2 - 1] - 1;
    i = length1 - 1;
    j = length2 - 1;

    while ( (i > 0) and 
            (j > 0) )
    {
        if (v1[i] == v2[j])
        {
            sol[index] = v1[i];
            i--;
            j--;
            index--;
        }
        else
        {
            if (lcs[i][j - 1] > lcs[i - 1][j])
            {
                j--;
            }
            else
            {
                i--;
            }
        }
    }

    if (lcs[i][j] == 1)
    {
        if (i == 0)
        {
            sol[0] = v1[0];
        }
        else
        {
            sol[0] = v2[0];
        }
    }

    tata << lcs[length1 - 1][length2 - 1] << std::endl;

    for (index = 0; index < lcs[length1 - 1][length2 - 1]; index++)
    {
        tata << sol[index] << " ";
    }

    return 0;
}
