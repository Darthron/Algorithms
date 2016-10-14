#include <iostream>

int main()
{
    int n;
    int zeros;
    int neg;
    int pos;
    int x;

    zeros = 0;
    pos = 0;
    neg = 0;

    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> x;

        if (0 == x)
        {
            ++zeros;
        }
        else if (0 > x)
        {
            ++neg;
        }
        else
        {
            ++pos;
        }
    }

    std::cout << double(pos) / n << '\n';
    std::cout << double(neg) / n << '\n';
    std::cout << double(zeros) / n << '\n';
    return 0;
}
