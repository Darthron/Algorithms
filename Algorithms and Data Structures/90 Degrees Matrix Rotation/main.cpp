#include <fstream>

int n;
int mat[10000][10000];

void
swap(int& a,
     int& b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;
}

void
rotate2()
{
    int i;
    int j;

    // Symmetrize the matrix with respect to the main diagonal
    // 1 2 3    1 4 7
    // 4 5 6 -> 2 5 8
    // 7 8 9    3 6 9

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            swap(mat[i][j],
                 mat[j][i]);
        }
    }

    // Symmetrize with respect to the median column

    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= (n - 1) / 2; j++)
        {
            swap(mat[i][j],
                 mat[i][n - 1 - j]);
        }
    }
}

void
rotate()
{
    int i;
    int k;

    // Reverse each line parallel to the the primary diagonal
    // eg: 1 2 3    9 6 3
    //     4 5 6 -> 8 5 2
    //     7 8 9    7 4 1
    
    for (i = 0; i <= (n - 1) / 2; i++)
    {
        swap(mat[i][i],
             mat[n - 1 - i][n - 1 - i]);
    }

    for (k = 1; k < n; k++)
    {
        for (i = 0; i <= (n - 1 - k)/ 2 && i + k < n; i++)
        {
            swap(mat[i][i + k],
                 mat[n - 1 - i - k][n - 1 - i]);
            swap(mat[i + k][i],
                 mat[n - 1 - i][n - 1 - i - k]);
        }
    }

    // Reverse each column

    for (i = 0; i < n; i++)
    {
        for (k = 0; k <= (n - 1)/ 2; k++)
        {
            swap(mat[k][i],
                 mat[n - 1 - k][i]);
        }
    }
}

int main()
{
    std::ifstream mama("matrix.in");
    std::ofstream tata("matrix.out");

    mama >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mama >> mat[i][j];
        }
    }

    rotate2();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tata << mat[i][j] << " ";
        }

        tata << std::endl;
    }

    return 0;
}
