#include "BST.h"

int main()
{
    BST<int> tree;
/*
        1
    -10      20
   -20 -5  10   50
               30 70
*/
    tree.insert(1);
    tree.insert(20);
    tree.insert(-10);
    tree.insert(50);
    tree.insert(30);
    tree.insert(-20);
    tree.insert(-5);
    tree.insert(70);
    tree.insert(10);

    tree.remove(1);
    
    BST <int> newTree;

    newTree = tree;
    for (auto it = newTree.begin(); it != newTree.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    newTree.insert(-6);
    newTree.remove(50);
    newTree.remove(-5); 
    newTree.remove(-6);
    newTree.remove(-10);
    newTree.insert(1);
    newTree.remove(-20); 

    for (auto it = newTree.end(); it != newTree.begin(); --it)
    {
        std::cout << *it << " ";
    }

    return 0;
}
