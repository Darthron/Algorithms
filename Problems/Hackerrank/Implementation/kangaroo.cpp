#include <iostream>

int main()
{
    int x1, v1, x2, v2;

    std::cin >> x1 >> v1 >> x2 >> v2;

    if (x1 == x2)
    {
        std::cout << "YES";
    }
    else if ( (x1 > x2) and
         (v1 >= v2) )
    {
        std::cout << "NO";
    }
    else if ( (x1 < x2) and
              (v1 <= v2) )
    {
        std::cout << "NO";
    }
    else if ( 0 == (x1 - x2) % (v2 - v1) )
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
    return 0;
}
