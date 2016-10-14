#include "RedBlackTree.h"

int main()
{
    RedBlackTree <int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    tree.remove(4);
    tree.remove(2);
    
    for (auto it : tree.getElementsByLevels())
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    return 0;
}
