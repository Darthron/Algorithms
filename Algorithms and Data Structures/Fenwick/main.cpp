#include <iostream>

int fen[10005];
int n;

void
update(int index,
       int val)
{
    while (index <= n)
    {
        fen[index] += val;
        index += (index & -index);
    }
}

void
getSum(int index)
{
    int sum;

    sum = 0;
    while (index)
    {
        sum += fen[index];
        index -= (index & -index);
    }
}

int main()
{
    int arr[10001];
    int index;

    std::cin >> n;

    for (index = 1; index <= n; ++index)
    {
        std::cin >> arr[index];
        update(index, arr[index]);
    }
}
