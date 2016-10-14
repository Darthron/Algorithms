#include <iostream>

int main()
{
    int n;
    int sumPrincipal;
    int sumSecondary;
    int x;

    std::cin >> n;

    sumPrincipal = 0;
    sumSecondary = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cin >> x;

            if (i == j)
            {
                sumPrincipal += x;
            }
            
            if (i == n - 1 - j)
            {
                sumSecondary += x;
            }
        }
    }

    std::cout << sumPrincipal << " " << sumSecondary << '\n';
    std::cout << abs(sumPrincipal - sumSecondary);
}
