#include <iostream>
#include <limits>

int main()
{
    int                N;
    int                index;
    unsigned long long number;
    unsigned long long result;
    unsigned long long sumOfTwos;
    
    std::cin >> N;

    for (index = 0; index < N; ++index)
    {
        // number is also unsigned long long so that the result
        // is of the same type
        
        std::cin >> number;

        if (number & 1)
        {
            result = ((number + 1) / 2) * number;
        }
        else
        {
            result = (number / 2) * (number + 1);
        }

        // sumOfTwos will become the first power of two greater than number
        // The number we need to substract is 2 * (sumOfTwos - 1), because
        // of the geometric series and the fact that we have already sumed the
        // twos once

        for (sumOfTwos = 1; sumOfTwos <= number; sumOfTwos <<= 1);

        sumOfTwos = 2 * (sumOfTwos - 1);
        
        if (number < 10)
        {
            std::cout << int(result) - int(sumOfTwos) << std::endl;
        }
        else
        {
            std::cout << result - sumOfTwos << std::endl;
        }
    }

    return 0;
}
