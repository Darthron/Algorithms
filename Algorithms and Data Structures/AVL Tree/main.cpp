#include <iostream>
#include "AVL.h"

using namespace std;

void print(Node *node)
{
    if (node == NULL)
        return;
    cout << ((*node).getValue()) << " ";
    print ((*node).getLeftChild());
    print ((*node).getRightChild());
}

int main()
{
    AVL tree;

    tree.insertNode(5);
    tree.insertNode(4);
    tree.insertNode(10);
    tree.insertNode(7);
    tree.insertNode(11);
    //tree.insertNode(6);
    //tree.deleteNode(4);
    tree.insertNode(1);
    tree.insertNode(2);
    print(tree.getRoot());
    return 0;
}
