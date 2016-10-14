#include <iostream>

int main()
{
    int n, k, q;
    int arr[100000];
    int index;
    int pos;

    std::cin >> n >> k >> q;

    k %= n;
    for (index = 0; index < n; ++index)
    {
        std::cin >> arr[index];
    }

    for (index = 0; index < q; ++index)
    {
        std::cin >> pos;

        std::cout << arr[(pos + n - k) % n] << std::endl;
    }
}
