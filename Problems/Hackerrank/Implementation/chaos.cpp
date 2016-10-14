#include <iostream>

int main()
{
    int  t;
    int  n;
    int  arr[100000];
    int  index;
    int  numIndex;
    bool ok;
    int  counter;
    int  tempN;

    std::cin >> t;

    for (index = 0; index < t; ++index)
    {
        std::cin >> n;

        ok = true;
        for (numIndex = 0; numIndex < n; ++numIndex)
        {
            std::cin >> arr[numIndex];
            if (arr[numIndex] - numIndex > 3)
            {
                ok = false;
            }
        }

        if (not ok)
        {
            std::cout << "Too chaotic\n";
            continue;
        }

        ok = true;
        tempN = 0;
        counter = 0;
        while (ok)
        {
            ok = false;
            for (numIndex = n - 1; numIndex > tempN; --numIndex)
            {
                if (arr[numIndex] < arr[numIndex - 1])
                {
                    int temp;

                    temp = arr[numIndex];
                    arr[numIndex] = arr[numIndex - 1];
                    arr[numIndex - 1] = temp;
                    ++counter;
                    ok = true;
                }
            }

            ++tempN;
        }

        std::cout << counter << '\n';
    }
}
