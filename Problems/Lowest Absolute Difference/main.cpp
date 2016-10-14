#include <iostream>
#include <algorithm>

// Given two arrays,
// find the numbers with the lowest absolute difference

struct Pair
{
    int x;
    int y;
};

// Given a value and a sorted array, this method returns the
// first number less than the value, or the first number larger,
// if the value is less than any number in the array;

// Preconditions: val is not in the array

int
getBinarySearchLower(int arr[],
                     int n,
                     int val)
{
    int tempIndex;
    int index;

    if (val < arr[0])
    {
        return arr[0];
    }

    for (tempIndex = 1; tempIndex < n; tempIndex <<= 1);

    for (index = 0; tempIndex; tempIndex >>= 1)
    {
        if ( (tempIndex + index < n) and
             (arr[tempIndex + index] < val) )
        {
            index += tempIndex;
        }
    }

    return arr[index];
}

Pair
getNumbersWithLowestAbsoluteDifference(int arr1[],
                                       int n,
                                       int arr2[],
                                       int m)
{
    int  index;
    Pair pair;
    int  min;

    std::sort(arr2,
              arr2 + m);

    pair.x = arr1[0];
    pair.y = arr2[0];
    min = abs(arr1[0] - arr2[0]);

    for (index = 0; index < n; index++)
    {
        int foundNo;

        foundNo = getBinarySearchLower(arr2,
                                       m,
                                       arr1[index]);
        if (abs(arr1[index] - foundNo) < min)
        {
            min = abs(arr1[index] - foundNo);
            pair.x = arr1[index];
            pair.y = foundNo;
        }
    }

    return pair;
}

int main()
{
    int  arr1[1000];
    int  arr2[1000];
    int  n;
    int  m;
    int  index;
    Pair pair;

    std::cin >> n;
    std::cin >> m;

    for (index = 0; index < n; index++)
    {
        std::cin >> arr1[index];
    }

    for (index = 0; index < m; index++)
    {
        std::cin >> arr2[index];
    }

    // We will sort the smaller array because
    // L * log (l) + l * log (l) < l * log (L) + L * log (L)
    if (n > m)
    {
        pair = getNumbersWithLowestAbsoluteDifference(arr1,
                                                      n,
                                                      arr2,
                                                      m);
    }
    else
    {
        pair = getNumbersWithLowestAbsoluteDifference(arr2,
                                                      m,
                                                      arr1,
                                                      n);
    }

    std::cout << pair.x << " " << pair.y;

    return 0;
}
