#include <iostream>

int main()
{
    int n;
    int k;
    int mod[100];
    int index;
    int x;
    int counter;

    std::cin >> n;
    std::cin >> k;

    for (index = 0; index < k; ++index)
    {
        mod[index] = 0;
    }

    for (index = 0; index < n; ++index)
    {
        std::cin >> x;
        ++mod[x % k];
    }

    counter = (mod[0] > 0) ? 1 : 0;

    for (index = 1; index < k / 2; ++index)
    {
        counter += std::max(mod[index],
                            mod[k - index]);
    }

    if (k == 1)
    {
        goto print;
    }

    if (k & 1)
    {
        counter += std::max(mod[index],
                            mod[k - index]);
    }
    else
    {
        counter += (mod[k / 2] > 0) ? 1 : 0;
    }

print:
    std::cout << counter;
    return 0;
}
