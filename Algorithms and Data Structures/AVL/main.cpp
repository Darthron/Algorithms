#include "AVL.h"

int main()
{
    AVL <int> tree;

    tree.insert(30);
    tree.insert(22);
    tree.insert(40);
    tree.insert(25);
    tree.insert(35);
    tree.insert(50);
    tree.insert(38);

    tree.remove(22);

    tree.printNodesByLevel();
    return 0;
}
