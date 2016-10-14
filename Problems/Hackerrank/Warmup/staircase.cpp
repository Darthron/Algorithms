#include <iostream>

int main()
{
    int n;
    int i;
    int j;

    std::cin >> n;

    for (i = 1; i <= n; ++i)
    {
        j = 1;

        while (j <= n - i)
        {
            std::cout << ' ';
            ++j;
        }

        while (j <= n)
        {
            std::cout << '#';
            ++j;
        }

        std::cout << std::endl;
    }
}
