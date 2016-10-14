#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <vector>
#include <functional>
#include <iostream>
#include <queue>

using uint = unsigned int;

template <typename T, typename Comp = std::less <T> >
class RedBlackTree
{
public:
    enum kColour
    { 
        RED, 
        BLACK 
    };

private:
    struct Node
    {
        T       info;
        Node*   parent;
        Node*   leftChild;
        Node*   rightChild;
        kColour colour;

        Node(T val)
            : info(val),
              parent(nullptr),
              leftChild(nullptr),
              rightChild(nullptr),
              colour(kColour::RED)
        {

        }
        
        Node(T val,
             kColour col)
            : info(val),
              parent(nullptr),
              leftChild(nullptr),
              rightChild(nullptr),
              colour(col)
        {

        }

        Node(kColour col)
            : parent(nullptr),
              leftChild(nullptr),
              rightChild(nullptr),
              colour(col)
        {

        }
    };

public:
    // Default constructor
    RedBlackTree();

    // Destructor
    ~RedBlackTree();

    // Constructor from array
    RedBlackTree(std::vector <T> array);

    // Insert
    void
    insert(T val);

    // Remove
    void
    remove(T val);
    
    // Elements by level
    std::vector <T>
    getElementsByLevels() const;

private:
    void
    repairDeletion(Node* node);

    void
    repairInsert(Node* node);

    void
    deleteTree();

    void
    rotateLeft(Node* node);

    void
    rotateRight(Node* node);

    Node*
    getSuccessor(Node* node);

    void
    transplant(Node* u,
               Node* v);

    Node* root;
    Node* pseudoroot;
    Node* nil; 
    Comp  comp;
    uint  size;
};

template <typename T, typename Comp>
RedBlackTree <T, Comp>::RedBlackTree()
{
    pseudoroot = nullptr;
    size = 0;
    nil = new Node(kColour::BLACK);
    root = nil;
}

template <typename T, typename Comp>
RedBlackTree <T, Comp>::~RedBlackTree()
{
    deleteTree();
}

template <typename T, typename Comp>
RedBlackTree <T, Comp>::RedBlackTree(std::vector <T> array)
{
    for (auto it : array)
    {
        this -> insert(it);
    }
}

template <typename T, typename Comp>
void
RedBlackTree <T, Comp>::insert(T val)
{
    Node* tempNode;
    Node* insertedNode;
    bool  right;

    if (root == nil)
    {
        root = new Node(val,
                        kColour::BLACK);
        pseudoroot = new Node(val);

        root -> parent = pseudoroot;
        root -> rightChild = nil;
        root -> leftChild = nil;
        pseudoroot -> leftChild = root;
        pseudoroot -> rightChild = root;

        this -> size++;

        return;
    }
    
    tempNode = root;

    while (true)
    {
        if ( comp(tempNode -> info,
                    val) )
        {
            if (tempNode -> rightChild == nil)
            {
                right = true;
                break;
            }
            
            tempNode = tempNode -> rightChild;
        }
        // Unique values, so we exit the insert function
        else if (tempNode -> info == val)
        {
            return;
        }
        else
        {
            if (tempNode -> leftChild == nil)
            {
                right = false;
                break;
            }
            
            tempNode = tempNode -> leftChild;
        }
    }
    
    insertedNode = new Node(val,
                            kColour::RED);
    this -> size++;
    if (right)
    {
        tempNode -> rightChild = insertedNode; 
    }
    else
    {
        tempNode -> leftChild = insertedNode;
    }

    insertedNode -> leftChild = nil;
    insertedNode -> rightChild = nil;
    insertedNode -> parent = tempNode;

    repairInsert(insertedNode);
}

template <typename T, typename Comp>
void
RedBlackTree <T, Comp>::repairInsert(Node* node)
{
    Node* uncle;

    while ( (node != root) and
            (node -> parent -> colour == kColour::RED) )
    {
        // If the parent of our node is the leftChild of the grandparent.
        // It does not interfere with the pseudoroot since the root's colour is BLACK,
        // so node will never be one of the root's children
        if (node -> parent == node -> parent -> parent -> leftChild)
        {
            uncle = node -> parent -> parent -> rightChild;
            if (uncle -> colour == kColour::RED)
            {
                node -> parent -> colour = kColour::BLACK;
                uncle -> colour = kColour::BLACK;
                node -> parent -> parent -> colour = kColour::RED;

                node = node -> parent -> parent;
            }
            else
            {
                if (node == node -> parent -> rightChild)
                {
                    node = node -> parent;
                    rotateLeft(node);
                }
                node -> parent -> colour = kColour::BLACK;
                node -> parent -> parent -> colour = kColour::RED;
                rotateRight(node -> parent -> parent);
            }
        }
        else
        {
            uncle = node -> parent -> parent -> leftChild;
            if (uncle -> colour == kColour::RED)
            {
                node -> parent -> colour = kColour::BLACK;
                uncle -> colour = kColour::BLACK;
                node -> parent -> parent -> colour = kColour::RED;

                node = node -> parent -> parent;
            }
            else
            {
                if (node == node -> parent -> leftChild)
                {
                    node = node -> parent;
                    rotateRight(node);
                }
                node -> parent -> colour = kColour::BLACK;
                node -> parent -> parent -> colour = kColour::RED;
                rotateLeft(node -> parent -> parent);
            }
        }
    }

    root -> colour = kColour::BLACK;
}

template <typename T, typename Comp>
void
RedBlackTree <T, Comp>::rotateLeft(Node* node)
{
    Node* rotatedNode;

    rotatedNode = node -> rightChild;

    if (node == root)
    {
        pseudoroot -> leftChild = rotatedNode;
        pseudoroot -> rightChild = rotatedNode;
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
    node -> rightChild -> parent = node;
    rotatedNode -> leftChild = node;
    rotatedNode -> parent = node -> parent;
    node -> parent = rotatedNode;

}

template <typename T, typename Comp>
std::vector <T>
RedBlackTree <T, Comp>::getElementsByLevels() const
{
    std::vector <T>                  res;
    std::queue <RedBlackTree::Node*> q;
    RedBlackTree::Node*              tempNode;

    q.push(root);
    while (not q.empty())
    {
        tempNode = q.front();
        q.pop();

        if (tempNode != nil)
        {
            q.push(tempNode -> leftChild);
            q.push(tempNode -> rightChild);
        }

        if (tempNode != nil)
        {
            res.push_back(tempNode -> info);
        }
    }

    return res;
}

template <typename T, typename Comp>
void
RedBlackTree <T, Comp>::rotateRight(Node* node)
{
    Node* rotatedNode;

    rotatedNode = node -> leftChild;

    node -> leftChild = rotatedNode -> rightChild;
    node -> leftChild -> parent = node;
    rotatedNode -> rightChild = node;
    rotatedNode -> parent = node -> parent;
    node -> parent = rotatedNode;

    if (node == root)
    
    {
        pseudoroot -> leftChild = rotatedNode;
        pseudoroot -> rightChild = rotatedNode;
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
}

template <typename T, typename Comp>
void
RedBlackTree <T, Comp>::remove(T val)
{
    Node*   nodeToDelete;
    Node*   repairNode;
    Node*   successor;
    kColour deletedColour;

    nodeToDelete = root;
    while ( (nodeToDelete != nil) and
            (nodeToDelete -> info != val) )
    {
        if ( comp(nodeToDelete -> info, val) )
        {
            nodeToDelete = nodeToDelete -> rightChild;
        }
        else
        {
            nodeToDelete = nodeToDelete -> leftChild;
        }
    }

    // Doesn't exist
    if (nodeToDelete == nil)
    {
        return;
    }

    deletedColour = nodeToDelete -> colour;

    if (nodeToDelete -> leftChild == nil)
    {
        repairNode = nodeToDelete -> rightChild;
        transplant(nodeToDelete,
                   nodeToDelete -> rightChild);
    }
    else if (nodeToDelete -> rightChild == nil)
    {
        repairNode = nodeToDelete -> leftChild;
        transplant(nodeToDelete,
                   nodeToDelete -> leftChild);
    }
    else
    {
        successor = getSuccessor(nodeToDelete);

        deletedColour = successor -> colour;
        repairNode = successor -> leftChild;

        if (successor -> parent == nodeToDelete)
        {
            repairNode -> parent = successor;
        }
        else
        {
            transplant(successor,
                       repairNode);
            successor -> leftChild = nodeToDelete -> leftChild;
            successor -> leftChild -> parent = successor;
        }
        transplant(nodeToDelete,
                   successor);
        successor -> rightChild = nodeToDelete -> rightChild;
        successor -> rightChild -> parent = successor;
        successor -> colour = nodeToDelete -> colour;
    }

    if (kColour::BLACK == deletedColour)
    {
        repairDeletion(repairNode);
    }
}

// Replaces the subtree whose root is u
// with the subtree whose root is v
template <typename T, typename Comp>
void
RedBlackTree <T, Comp>::transplant(Node* u,
                                   Node* v)
{
    if (u == root)
    {
        root = v;
        pseudoroot -> rightChild = v;
        pseudoroot -> leftChild = v;
    }
    else if (u == u -> parent -> leftChild)
    {
        u -> parent -> leftChild = v;
    }
    else
    {
        u -> parent -> rightChild = v;
    }

    v -> parent = u -> parent;
}

template <typename T, typename Comp>
void
RedBlackTree <T, Comp>::repairDeletion(Node* node)
{
    Node* brother;

    while ( (root != node) and
            (node -> colour == kColour::BLACK) )
    {
        if (node == node -> parent -> leftChild)
        {
            brother = node -> parent -> rightChild;
            if (kColour::RED == brother -> colour)
            {
                brother -> colour = kColour::BLACK;
                node -> parent -> colour = kColour::RED;

                rotateLeft(node -> parent);
                brother = node -> parent -> rightChild;
            }
            if ( (kColour::BLACK == brother -> leftChild -> colour) and
                 (kColour::BLACK == brother -> rightChild -> colour) )
            {
                brother -> colour = kColour::RED;
                node = node -> parent;
            }
            else
            {
                if (kColour::BLACK == brother -> rightChild -> colour)
                {
                    brother -> leftChild -> colour = kColour::BLACK;
                    brother -> colour = kColour::RED;

                    rotateRight(brother);
                    brother = node -> parent -> rightChild;
                }

                brother -> colour = node -> parent -> colour;
                node -> parent -> colour = kColour::BLACK;
                brother -> rightChild -> colour = kColour::BLACK;

                rotateLeft(node -> parent);

                node = root;
            }
        }
        else
        {
            brother = node -> parent -> leftChild;
            if (kColour::RED == brother -> colour)
            {
                brother -> colour = kColour::BLACK;
                node -> parent -> colour = kColour::BLACK;

                rotateRight(node -> parent);
                brother = node -> parent -> leftChild;
            }
            if ( (kColour::BLACK == brother -> leftChild -> colour) and
                 (kColour::BLACK == brother -> rightChild -> colour) )
            {
                brother -> colour = kColour::RED;
                node = node -> parent;
            }
            else
            {
                if (kColour::BLACK == brother -> leftChild -> colour)
                {
                    brother -> rightChild -> colour = kColour::BLACK;
                    brother -> colour = kColour::RED;

                    rotateLeft(brother);
                    brother = node -> parent -> leftChild;
                }

                brother -> colour = node -> parent -> colour;
                node -> parent -> colour = kColour::BLACK;
                brother -> leftChild -> colour = kColour::BLACK;

                rotateRight(node -> parent);

                node = root;
            }
        }
    }

    node -> colour = kColour::BLACK;
}

template <typename T, typename Comp>
void
RedBlackTree <T, Comp>::deleteTree()
{

}

template <typename T, typename Comp>
typename RedBlackTree <T, Comp>::Node*
RedBlackTree <T, Comp>::getSuccessor(Node* node)
{
    Node* successor;

    // If the node does not have a left child,
    // look for the successor in the right subtree
    if (node -> leftChild == nil)
    {
        successor = node -> rightChild;

        if (successor == nil)
        {
            return successor;
        }

        while (successor -> leftChild != nil)
        {
            successor = successor -> leftChild;
        }
    }
    else
    {
        successor = node -> leftChild;

        while (successor -> rightChild != nil)
        {
            successor = successor -> rightChild;
        }
    }

    return successor;

}

#endif // REDBLACKTREE_H
