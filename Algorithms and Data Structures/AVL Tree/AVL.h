#ifndef AVL_H
#define AVL_H

class Node {
public :
            Node();
            Node(int);
            Node(int, Node*);
            ~Node();
    int     getHeight() const;
    int     getValue() const;
    Node*   getLeftChild() const;
    Node*   getRightChild() const;
    Node*   getParent() const;
    void    setParent(Node*);
    void    setLeftChild(Node*);
    void    setRightChild(Node*);
    void    setValue(int);
    void    setHeight(int);
    void    upgradeHeight();

private :
    int value;
    int height;
    Node *leftChild;
    Node *rightChild;
    Node *parent;
};

class AVL {
public :
            AVL();
            ~AVL();
    Node*   getRoot();
    Node*   getMax();
    Node*   getMin();
    void    deleteNode(int);
    void    insertNode(int);
    Node*   find(int);
    void    rebalance(Node*);

private :
    void    rotateLeft(Node*);
    void    rotateRight(Node*);
    void    deleteLeaf(Node*);
    void    insert(Node*, int);
    Node*   findNode(Node*, int);
    Node    *root;
};

#endif //AVL_H
