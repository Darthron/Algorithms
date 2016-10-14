#ifndef AVL_H
#define AVL_H

#include <vector>
#include <iostream>
#include <queue>

using uint = unsigned int;

bool t = false;

template <typename T>
class AVL
{
private:
    struct Node
    {
        T     info;
        Node* leftChild;
        Node* rightChild;
        Node* parent;
        uint  height;

        Node(T val)
            : info(val),
              leftChild(nullptr),
              rightChild(nullptr),
              parent(nullptr),
              height(1)
        {

        }
    };

public:
    AVL();
    ~AVL();

    AVL(std::vector <T> array);

    void
    insert(T value);

    void
    remove(T value);

    void
    printNodesByLevel();

private:
    void
    rotateLeft(Node* node);

    void
    rotateRight(Node* node);

    void
    deleteTree();

    uint
    getHeight(Node* node);

    void
    balanceHeight(Node* node);

    int
    balancingFactor(Node* node);

    void
    transplant(Node* oldNode,
               Node* newNode);

    Node*
    getSuccessor(Node* node);

    Node* root;
    uint  size;
};

template <typename T>
AVL <T>::AVL()
{
    root = nullptr;
    size = 0;
}

template <typename T>
AVL <T>::~AVL()
{
    deleteTree();
}

template <typename T>
AVL <T>::AVL(std::vector <T> array)
{
    for (auto el : array)
    {
        insert(el);
    }
}

template <typename T>
void
AVL <T>::rotateLeft(AVL <T>::Node* node)
{
    Node* rotatedNode;

    rotatedNode = node -> rightChild;

    if (not rotatedNode)
    {
        return;
    }

    if (node == root)
    {
        root = rotatedNode;
    }
    else
    {
        if (node == node -> parent -> leftChild)
        {
            node -> parent -> leftChild = rotatedNode;
        }
        else
        {
            node -> parent -> rightChild = rotatedNode;
        }
    }

    node -> rightChild = rotatedNode -> leftChild;
    if (rotatedNode -> leftChild)
    {
        rotatedNode -> leftChild -> parent = node;
    }

    rotatedNode -> leftChild = node;
    rotatedNode -> parent = node -> parent;
    node -> parent = rotatedNode;
    node -> height = std::max(getHeight(node -> leftChild),
                              getHeight(node -> rightChild)) + 1;
    rotatedNode -> height = std::max(getHeight(rotatedNode -> rightChild),
                                     getHeight(node)) + 1;
}

template <typename T>
void
AVL <T>::rotateRight(AVL <T>::Node* node)
{
    Node* rotatedNode;

    rotatedNode = node -> leftChild;

    if (not rotatedNode)
    {
        return;
    }
    
    if (node == root)
    {
        root = rotatedNode;
    }
    else
    {
        if (node == node -> parent -> leftChild)
        {
            node -> parent -> leftChild = rotatedNode;
        }
        else
        {
            node -> parent -> rightChild = rotatedNode;
        }
    }

    node -> leftChild = rotatedNode -> rightChild;
    if (rotatedNode -> rightChild)
    {
        rotatedNode -> rightChild -> parent = node;
    }

    rotatedNode -> rightChild = node;
    rotatedNode -> parent = node -> parent;
    node -> parent = rotatedNode;
    node -> height = std::max(getHeight(node -> leftChild),
                              getHeight(node -> rightChild)) + 1;
    rotatedNode -> height = std::max(getHeight(rotatedNode -> leftChild),
                                     getHeight(node)) + 1;
}

template <typename T>
void
AVL <T>::insert(T value)
{
    Node* nodeToLinkTo;
    Node* insertedNode;
    bool  right;

    if (nullptr == root)
    {
        root = new Node(value);
        size++;

        return;
    }

    nodeToLinkTo = root;

    while (true)
    {
        if (nodeToLinkTo -> info > value)
        {
            right = false;
            if (nodeToLinkTo -> leftChild)
            {
                nodeToLinkTo = nodeToLinkTo -> leftChild;
            }
            else
            {
                break;
            }
        }
        else if (nodeToLinkTo -> info < value)
        {
            right = true;
            if (nodeToLinkTo -> rightChild)
            {
                nodeToLinkTo = nodeToLinkTo -> rightChild;
            }
            else
            {
                break;
            }
        }
        // No duplicates
        else
        {
            return;
        }
    }

    insertedNode = new Node(value);
    insertedNode -> parent = nodeToLinkTo;
    if (right)
    {
        nodeToLinkTo -> rightChild = insertedNode;
    }
    else
    {
        nodeToLinkTo -> leftChild = insertedNode;
    }

    size++;
    balanceHeight(insertedNode -> parent);
}

template <typename T>
void
AVL <T>::transplant(Node* old,
                    Node* noob)
{
    if (old == root)
    {
        root = noob;
        noob -> parent = nullptr;
    }
    else
    {
        noob -> parent = old -> parent;
        if (old == old -> parent -> leftChild)
        {
            old -> parent -> leftChild = noob;
        }
        else
        {
            old -> parent -> rightChild = noob;
        }
    }
}

template <typename T>
void
AVL <T>::remove(T info)
{
    Node* node;
    Node* repairNode;
    Node* successor;

    node = root;
    while ( (node) and 
            (node -> info != info) )
    {
        if (node -> info > info)
        {
            node = node -> leftChild;
        }
        else
        {
            node = node -> rightChild;
        }
    }

    if (not node)
    {
        return;
    }

    if (not node -> leftChild)
    {
        repairNode = node -> parent;
        transplant(node,
                   node -> rightChild);
    }
    else if (not node -> rightChild)
    {
        repairNode = node -> parent;
        transplant(node,
                   node -> leftChild);
    }
    else
    {
        successor = getSuccessor(node);

        if (successor != node -> leftChild)
        {
            repairNode = successor -> parent;
            
            if (successor -> leftChild)
            {
                successor -> leftChild -> parent = successor -> parent;
                successor -> parent -> rightChild = successor -> leftChild;
            }

            successor -> leftChild = node -> leftChild;
            node -> leftChild -> parent = successor;
        
        }
        else
        {
            repairNode = successor;
        }

        successor -> rightChild = node -> rightChild;
        node -> rightChild -> parent = successor;

        successor -> parent = node -> parent;

        if (node == root)
        {
            root = successor;
        }
        else
        {
            if (node == node -> parent -> leftChild)
            {
                node -> parent -> leftChild = successor;
            }
            else
            {
                node -> parent -> rightChild = successor;
            }
        }
    }

    delete node;
    t = true;
    balanceHeight(repairNode);
}

template <typename T>
typename AVL <T>::Node*
AVL <T>::getSuccessor(Node* node)
{
    if (not node)
    {
        return nullptr;    
    }

    if (not node -> leftChild)
    {
        if ( not node -> rightChild )
        {
            return nullptr;
        }

        node = node -> rightChild;
        while (node -> leftChild)
        {
            node = node -> leftChild;
        }
    }
    else
    {
        node = node -> leftChild;
        while (node -> rightChild)
        {
            node = node -> rightChild;
        }
    }

    return node;
}

template <typename T>
void
AVL <T>::deleteTree()
{

}

template <typename T>
uint
AVL <T>::getHeight(Node* node)
{
    if (not node)
    {
        return 0;
    }
    
    return node -> height;
}

template <typename T>
int
AVL <T>::balancingFactor(Node* u)
{
    if (not u)
    {
        return 0;
    }

    return ((int) getHeight(u -> leftChild) - (int)getHeight(u -> rightChild));
}

template <typename T>
void
AVL <T>::balanceHeight(Node* node)
{
    int   balance;
    Node* parent;

    if ( not node )
    {
        return;
    }

    parent = node -> parent;
    node -> height = std::max(getHeight(node -> leftChild),
                              getHeight(node -> rightChild)) + 1;
    balance = balancingFactor(node);
    if (balance < -1)
    {
        if (balancingFactor(node -> rightChild) > 0)
        {
            rotateRight(node -> rightChild);
        }

        rotateLeft(node);
    }
    else if (balance > 1)
    {
        if (balancingFactor(node -> leftChild) < 0)
        {
            rotateLeft(node -> leftChild);
        }

        rotateRight(node);
    }

    balanceHeight(parent);
}

template <typename T>
void
AVL <T>::printNodesByLevel()
{
    std::queue <Node*> q;
    Node*              node;

    node = root;
    q.push(node);

    while (not q.empty())
    {
        node = q.front();
        q.pop();

        if (node -> leftChild)
        {
            q.push(node -> leftChild);
        }
        if (node -> rightChild)
        {
            q.push(node -> rightChild);
        }

        std::cout << node -> info << " " << node -> height << std::endl;
    }
}

#endif // AVL_H
