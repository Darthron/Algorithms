#include <fstream>

std::ifstream mama("ssm.in");
std::ofstream tata("ssm.out");

int main()
{
    int n;
    int number;
    int index;
    int beg;
    int end;
    int tempIndex;
    int sum;
    int bestSum;

    bestSum = (1 << 31);
    sum = 0;
    beg = 0;
    end = 0;

    mama >> n;
    for (index = 0; index < n; index++)
    {
        mama >> number;

        if (sum < 0)
        {
            sum = number;
            tempIndex = index;
        }
        else
        {
            sum += number;
        }

        if (sum > bestSum)
        {
            bestSum = sum;
            beg = tempIndex;
            end = index;
        }
    }

    tata << bestSum << " " << beg + 1 << " " << end + 1;
    return 0;
}
