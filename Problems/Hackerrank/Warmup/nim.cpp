#include <iostream>

/*
 * 5 august - 5 s 2 d
 * 6 august - 3 s 3 d
 */

int main()
{
    int t;
    int n;
    int stones;
    int index;
    int xorSum;
    int ones;

    std::cin >> n;
    for (index = 0; index < n; ++index)
    {
        std::cin >> t;
        
        ones = 0;
        xorSum = 0;
        for (int j = 0; j < t; ++j)
        {
            std::cin >> stones;
            
            xorSum ^= stones;
            if (1 == stones)
            {
                ++ones;
            }
        }

        if (ones == t)
        {
            if (1 == xorSum)
            {
                std::cout << "Second" << std::endl;
            }
            else
            {
                std::cout << "First" << std::endl;
            }
        }
        else
        {
            if (0 == xorSum)
            {
                std::cout << "Second" << std::endl;
            }
            else
            {
                std::cout << "First" << std::endl;
            }
        }
    }

    return 0;
}
