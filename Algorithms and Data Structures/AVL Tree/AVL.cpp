#include "AVL.h"
#include <stdlib.h>
#include <iostream>

Node::Node() {
    value = 0;
    height = 0;
    leftChild = NULL;
    rightChild = NULL;
    parent = NULL;
}

Node::Node(int val) {
    value = val;
    height = 0;
    leftChild = NULL;
    rightChild = NULL;
    parent = NULL;
}

Node::Node(int val, Node *p) {
    value = val;
    height = 0;
    leftChild = NULL;
    rightChild = NULL;
    parent = p;
}

Node::~Node() {

}

int     Node::getHeight() const {
    if (this == NULL)
        return -1;
    return height;
}

int     Node::getValue() const {
    return value;
}

Node*    Node::getLeftChild() const {
    return leftChild;
}

Node*    Node::getRightChild() const {
    return rightChild;
}

Node*    Node::getParent() const {
    return parent;
}

void    Node::setParent(Node* p) {
    parent = p;
}

void    Node::setLeftChild(Node *child) {
    leftChild = child;
}

void    Node::setRightChild(Node* child) {
    rightChild = child;
}

void    Node::setValue(int val) {
    value = val;
}

void    Node::setHeight(int h) {
    height = h;
}

void    Node::upgradeHeight() {
    int newHeight;

    newHeight = std::max((this -> getLeftChild()) -> getHeight(),
                    (this -> getRightChild()) -> getHeight()) + 1;
    this -> setHeight(newHeight);
    if (this -> getParent())
        (this -> getParent()) -> upgradeHeight();
}

AVL::AVL() {
    root = NULL;
}

AVL::~AVL() {

}

Node*   AVL::getRoot() {
    return root;
}

Node*   AVL::getMax() {
    Node *node;

    node = root;
    if (NULL == root)
        return NULL;
    while (node -> getRightChild())
        node = node -> getRightChild();
    return node;
}

Node*   AVL::getMin() {
    Node *node;

    node = root;
    if (NULL == root)
        return NULL;
    while (node -> getLeftChild())
        node = node -> getLeftChild();
    return node;
}

void    AVL::deleteNode(int val) {
    Node *node;
    Node *temp;
    Node *t;
    int v;

    node = find(val);
    if (NULL == node)
        return;
    else if (0 == node -> getHeight())
    {
        temp = node -> getParent();
        deleteLeaf(node);
        rebalance(temp);
    }
    else if (node -> getLeftChild() and node -> getRightChild())
    {
        temp = root;
        if ((node -> getLeftChild()) -> getHeight() > (node -> getRightChild()) -> getHeight())
        {
            root = node -> getLeftChild();
            t = getMax();
            v = t -> getValue();
            deleteNode(v);
            t = t -> getParent();
            node -> setValue(v);
            root = temp;
            rebalance(t);
        }
        else
        {
            root = node -> getRightChild();
            t = getMin();
            v = t -> getValue();
            deleteNode(v);
            t = t -> getParent();
            node -> setValue(v);
            root = temp;
            rebalance(t);
        }
    }
    else
    {
        t = node -> getParent();
        if (NULL == node -> getLeftChild())
        {
            if ((node -> getParent()) -> getLeftChild() == node)
                (node -> getParent()) -> setLeftChild(node -> getRightChild());
            else
                (node -> getParent()) -> setRightChild(node -> getRightChild());
        }
        else
        {
            if ((node -> getParent()) -> getLeftChild() == node)
                (node -> getParent()) -> setLeftChild(node -> getLeftChild());
            else
                (node -> getParent()) -> setRightChild(node -> getLeftChild());
        }
        rebalance(t);
    }
}

void    AVL::insertNode(int val) {
    if (root == NULL)
        root = new Node(val);
    else
        insert(root, val);
}

Node*   AVL::find(int value) {
    return findNode(root, value);
}

void    AVL::rebalance(Node* node) {
    while (NULL != node and (1 >= abs((node -> getLeftChild()) -> getHeight() -
               (node -> getRightChild()) -> getHeight())))
        node = node -> getParent();
    if (NULL == node)
        return;
    if ((node -> getLeftChild()) -> getHeight() <
        (node -> getRightChild()) -> getHeight())
    {
        if (((node -> getRightChild()) -> getLeftChild()) -> getHeight() <=
            ((node -> getRightChild()) -> getRightChild()) -> getHeight())
            rotateLeft(node);
        else
        {
            rotateRight(node -> getRightChild());
            rotateLeft(node);
        }
    }
    else
    {
        if (((node -> getLeftChild()) -> getLeftChild()) -> getHeight() >=
            ((node -> getLeftChild()) -> getRightChild()) -> getHeight())
            rotateRight(node);
        else
        {
            rotateLeft(node -> getLeftChild());
            rotateRight(node);
        }
    }

}

void    AVL::rotateLeft(Node* node) {
    Node *a;
    Node *b;

    a = node -> getRightChild();
    b = node -> getParent();
    a -> setParent(b);
    if (b)
    {
        if (b -> getLeftChild() == node)
            b -> setLeftChild(a);
        else
            b -> setRightChild(a);
    }
    node -> setRightChild(a -> getLeftChild());
    if (a -> getLeftChild())
        (a -> getLeftChild()) -> setParent(node);
    a -> setLeftChild(node);
    node -> setParent(a);
    node -> upgradeHeight();
    if (node == root)
        root = a;
}

void    AVL::rotateRight(Node* node) {
    Node *a;
    Node *b;

    a = node -> getLeftChild();
    b = node -> getParent();
    a -> setParent(b);
    if (b)
    {
        if (b -> getLeftChild() == node)
            b -> setLeftChild(a);
        else
            b -> setRightChild(a);
    }
    node -> setLeftChild(a -> getRightChild());
    if (a -> getRightChild())
        (a -> getRightChild()) -> setParent(node);
    a -> setRightChild(node);
    node -> setParent(a);
    node -> upgradeHeight();
    if (node == root)
        root = a;
}

void    AVL::deleteLeaf(Node *leaf)
{
    if (leaf -> getValue() > (leaf -> getParent()) -> getValue())
        (leaf -> getParent()) -> setRightChild(NULL);
    else
        (leaf -> getParent()) -> setLeftChild(NULL);
    leaf -> setParent(NULL);
}

void    AVL::insert(Node *node, int val) {
    if ((*node).getValue() > val and (*node).getLeftChild() == NULL)
    {
        (*node).setLeftChild(new Node(val, node));
        (*((*node).getLeftChild())).upgradeHeight();
        rebalance(node -> getLeftChild());
    }
    else if ((*node).getValue() > val)
        insert((*node).getLeftChild(), val);
    else if ((*node).getValue() < val and (*node).getRightChild() == NULL)
    {
        (*node).setRightChild(new Node(val, node));
        (*((*node).getRightChild())).upgradeHeight();
        rebalance(node -> getRightChild());
    }
    else if ((*node).getValue() < val)
        insert((*node).getRightChild(), val);
}

Node*   AVL::findNode(Node *node, int val)
{
    if (node == NULL)
        return NULL;
    if ((*node).getValue() == val)
        return node;
    if ((*node).getValue() > val)
        return findNode((*node).getLeftChild(), val);
    else
        return findNode((*node).getRightChild(), val);
}

