#include <iostream>
#include <algorithm>

int main()
{
    int n;
    int arr[1000];
    int index;
    int counter;
    int tempN;

    std::cin >> n;
    
    for (index = 0; index < n; ++index)
    {
        std::cin >> arr[index];
    }

    std::sort(arr,
              arr + n);

    std::cout << n << '\n';
    
    index = 0;
    tempN = n;
    while (index != n - 1)
    {
        counter = 1;
        while ( (index != n - 1) and
                (arr[index] == arr[index + 1]) )
        {
            ++index;
            ++counter;
        }

        if (index != n - 1)
        {
            tempN -= counter;
            ++index;
            
            std::cout << tempN << '\n';
        }
    }
    
    return 0;
}
