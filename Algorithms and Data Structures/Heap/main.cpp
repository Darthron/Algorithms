#include "Heap.h"
#include <iostream>

int main()
{
    std::vector <int> v = {4, 7, 1, 9, 5, 3, 10};
    Heap <int>        h(v);

    h.insert(13);
    for (auto it : h.getElements())
    {
        std::cout << it << std::endl;
    }

    return 0;
}
