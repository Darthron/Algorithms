#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

// Binary search tree that holds unique elements

using uint = unsigned int;

template <typename T>
class BST
{
private:
    struct Node
    {
        T     info;
        Node* leftChild;
        Node* rightChild;
        Node* parent;

        Node(T val,
             Node* p)
        {
            info = val;
            parent = p;
            leftChild = nullptr;
            rightChild = nullptr;
        }

        Node(T val)
        {
            info = val;
            parent = nullptr;
            leftChild = nullptr;
            rightChild = nullptr;
        }

        Node(const Node& that)
        {
            info = that.info;
            leftChild = that.leftChild;
            rightChild = that.rightChild;
            parent = that.parent;
        }

        Node()
        {
            parent = nullptr;
        }
    };

public:

    class Iterator
    {
    public:
        Iterator()
            : bst(nullptr),
              current(nullptr)
        {
        }

        explicit Iterator(BST* b,
                          Node* c)
            : bst(b),
              current(c)
        {

        }

        explicit Iterator(BST* b)
            : bst(b),
              current(nullptr)
        {

        }

        ~Iterator()
        {

        }

        T&
        operator*() const
        {
            return current -> info;
        }

        Iterator&
        operator++()
        {
            if (current == bst -> pseudoroot)
            {
                return *this;
            }

            if (current -> rightChild)
            {
                current = current -> rightChild;

                while (current -> leftChild)
                {
                    current = current -> leftChild;
                }
            }
            else
            {
                while ( (current -> parent != bst -> pseudoroot) and
                        (current == current -> parent -> rightChild) )
                {
                    current = current -> parent;
                }
                
                if (current != bst -> pseudoroot)
                {
                    current = current -> parent;
                }
            }
            return *this;
        }

        Iterator&
        operator--()
        {
            if (*this == bst -> begin())
            {
                return *this;
            }

            if (current -> leftChild)
            {
                current = current -> leftChild;

                while (current -> rightChild)
                {
                    current = current -> rightChild;
                }
            }
            else
            {
                while ( (current -> parent != bst -> pseudoroot) and
                        (current == current -> parent -> leftChild) )
                {
                    current = current -> parent;
                }

                if (current)
                {
                    current = current -> parent;
                }
            }
            return *this;
        }

        Iterator&
        operator=(const Iterator& that)
        {
            if (this != &that)
            {
                bst = that.bst;
                current = that.current;
            }
            return *this;
        }

        Iterator(const Iterator& that)
            : bst(that.bst),
              current(that.current)
        {

        }

        bool
        isValid() const
        {
            return (current != bst -> pseudoroot);
        }

        bool
        operator==(Iterator that)
        {
            return (current == that.current);
        }

        bool
        operator!=(Iterator that)
        {
            return (current != that.current);
        }

    private:
        BST*  bst;
        Node* current;
    };

    // Default constructor
    BST();

    // Default destructor
    virtual ~BST();

    inline uint
    getSize() const
    {
        return size;
    }

    void
    insert(T value);

    void
    remove(T value);

    std::vector <T>
    getElementsInfix() const;
    
    bool
    exists(T value) const;

    Iterator
    begin();

    inline Iterator
    end()
    {
        return Iterator(this,
                        pseudoroot);
    }

    std::vector <T>
    getElementsByLevels() const;

    Iterator
    find(T value) const;
    
    BST <T>&
    operator=(const BST& that); 

    // Copy constructor
    BST(const BST& that);

    void
    copyTree(const BST& that);

    void
    deleteBST();

    inline Node*
    getRoot() const
    {
        return root;
    }

private:

    Node*
    getSuccessor(Node* currentNode);

    Node*
    duplicateNodeLinkParent(Node* nodeToDuplicate,
                            Node* parent);
    Node* root;
    Node* pseudoroot;
    uint  size;
};

// Implementation

template <typename T>
BST <T>::BST()
{
    size = 0;
    root = nullptr;
}

template <typename T>
BST <T>::~BST()
{ 
    deleteBST();
}

template <typename T>
void
BST <T>::deleteBST()
{
    std::stack  <BST <T>::Node*>    stack;
    bool                            done;
    BST <T>::Node*                  tempNode;
    BST <T>::Node*                  child;

    done = false;
    tempNode = this -> root;
    while (not done)
    {
        if (tempNode)
        {
            stack.push(tempNode);
            tempNode = tempNode -> leftChild;
        }
        else if (stack.empty())
        {
            done = true;
        }
        else
        {
            tempNode = stack.top();
            stack.pop();
         
            child = tempNode -> rightChild;
            delete tempNode;

            tempNode = child;
        }
    }

    delete pseudoroot;
    pseudoroot = nullptr;
    root = nullptr;
}

template <typename T>
BST <T>&
BST <T>::operator=(const BST& that)
{
    deleteBST();

    copyTree(that);
    return *this;
}

template <typename T>
BST <T>::BST(const BST& that)
{
    root = nullptr;
    copyTree(that);
}

template <typename T>
void
BST <T>::copyTree(const BST& that)
{
    /*for (auto el : that.getElementsByLevels())
    {
        this -> insert(el);
    }*/

    if (that.getSize() == 0)
    {
        return;
    }

    pseudoroot = new BST<T>::Node();
    root = new BST<T>::Node(that.getRoot() -> info);
    root -> parent = pseudoroot;
    root -> leftChild = duplicateNodeLinkParent(that.getRoot() -> leftChild,
                                                root);
    root -> rightChild = duplicateNodeLinkParent(that.getRoot() -> rightChild,
                                                 root);
}

template <typename T>
typename BST <T>::Node*
BST <T>::duplicateNodeLinkParent(BST <T>::Node* nodeToDuplicate,
                                 BST <T>::Node* parent)
{
    Node* nodeToCreate;

    if (not nodeToDuplicate)
    {
        return nullptr;
    }

    nodeToCreate = new BST <T>::Node(nodeToDuplicate -> info);
    nodeToCreate -> parent = parent;
    nodeToCreate -> leftChild = duplicateNodeLinkParent(nodeToDuplicate -> leftChild,
                                                        nodeToCreate);
    nodeToCreate -> rightChild = duplicateNodeLinkParent(nodeToDuplicate -> rightChild,
                                                         nodeToCreate);

    return nodeToCreate;
}

template <typename T>
void
BST <T>::insert(T value)
{
    BST<T>::Node* tempNode;
    bool          right;

    
    if ( not root )
    {
        root = new BST<T>::Node(value);
        root -> parent = new BST<T>::Node();
        pseudoroot = root -> parent;
        pseudoroot -> leftChild = root;
        pseudoroot -> rightChild = root;
        this -> size++;
        return;
    }

    tempNode = root;
    while ( true )
    {
        if ( value < tempNode -> info )
        {
            if ( not tempNode -> leftChild )
            {
                right = false;
                break;
            }

            tempNode = tempNode -> leftChild;
        }
        else if ( value > tempNode -> info )
        {
            if ( not tempNode -> rightChild )
            {
                right = true;
                break;
            }

            tempNode = tempNode -> rightChild;
        }
        else // Already exists
        {
            return;
        }
    }

    if ( right )
    {
        tempNode -> rightChild = new BST<T>::Node(value,
                                                  tempNode);
    }
    else
    {
        tempNode -> leftChild = new BST<T>::Node(value,
                                                 tempNode);
    }

    this -> size++;
}


template <typename T>
void
BST <T>::remove(T value)
{
    BST<T>::Node* tempNode;
    BST<T>::Node* successor;
    bool          right;

    tempNode = root;
    while ( tempNode )
    {
        if ( value == tempNode -> info )
        {
            break;
        }
        else if ( value < tempNode -> info )
        {
            tempNode = tempNode -> leftChild;
            right = false;
        }
        else
        {
            tempNode = tempNode -> rightChild;
            right = true;
        }
    }

    // Doesn't exit
    if ( not tempNode )
    {
        return;
    }

    // Delete root. Only node
    if ( (tempNode == root) and
         (this -> size == 1) )
    {
        delete root;
        delete pseudoroot;

        root = nullptr;
        pseudoroot = nullptr;

        return;
    }

    successor = getSuccessor(tempNode);

    if (successor)
    {
        if (successor == successor -> parent -> leftChild)
        {
            // The successor is the node to be deleted's child
            if (successor == tempNode -> leftChild)
            {
                successor -> rightChild = tempNode -> rightChild;
                if (tempNode -> rightChild)
                {
                    tempNode -> rightChild -> parent = successor;
                }
            }
            // The successor can't be the node to be deleted's child
            // It is in the right subtree of tempNode
            else
            {
                if (successor -> rightChild)
                {
                    successor -> rightChild -> parent = successor -> parent;
                }
                successor -> parent -> leftChild = successor -> rightChild;
                
                successor -> leftChild = tempNode -> leftChild;
                successor -> rightChild = tempNode -> rightChild;

                tempNode -> rightChild -> parent = successor;
                if (tempNode -> leftChild)
                {
                    tempNode -> leftChild -> parent = successor;
                }
            }
        }
        else
        {
            // The successor is the node to be deleted's child
            if (successor == tempNode -> rightChild)
            {
                successor -> leftChild = tempNode -> leftChild;
                if (tempNode -> leftChild)
                {
                    tempNode -> leftChild -> parent = successor;
                }
            }
            // The successor can't be the node to be deleted's child
            // It is in the left subtree of tempNode
            else
            {
                if (successor -> leftChild)
                {
                    successor -> leftChild -> parent = successor -> parent;
                }
                successor -> parent -> rightChild = successor -> leftChild;

                successor -> leftChild = tempNode -> leftChild;
                successor -> rightChild = tempNode -> rightChild;

                tempNode -> leftChild -> parent = successor;
                if (tempNode -> rightChild)
                {
                    tempNode -> rightChild -> parent = successor;
                }

            }
        }

        successor -> parent = tempNode -> parent;
    }

    if (this -> root == tempNode)
    {
        root = successor;
        successor -> parent = pseudoroot;
        pseudoroot -> leftChild = root;
        pseudoroot -> rightChild = root;
    }
    else
    {
        if (right)
        {
            tempNode -> parent -> rightChild = successor;
        }
        else
        {
            tempNode -> parent -> leftChild = successor;
        }
    }

    delete tempNode;
    this -> size--;
}

template <typename T>
typename BST <T>::Node*
BST <T>::getSuccessor(BST <T>::Node* currentNode)
{
    BST <T>::Node* tempNode;

    // Get minimum of right subtree if the current node has no left child
    if ( not currentNode -> leftChild )
    {
        tempNode = currentNode -> rightChild;
        
        if ( not tempNode )
        {
            return nullptr;
        }

        while ( tempNode -> leftChild )
        {
            tempNode = tempNode -> leftChild;
        }

        return tempNode;
    }

    // The current node has a left child, so we'll get the maximum from the
    // subtree whose root it is
    tempNode = currentNode -> leftChild;

    while ( tempNode -> rightChild )
    {
        tempNode = tempNode -> rightChild;
    }

    return tempNode;
}

template <typename T>
std::vector <T>
BST <T>::getElementsByLevels() const
{
    std::vector <T>             res;
    std::queue <BST <T>::Node*> q;
    BST <T>::Node*              tempNode;

    q.push(root);
    while (not q.empty())
    {
        tempNode = q.front();
        q.pop();

        if (tempNode)
        {
            q.push(tempNode -> leftChild);
            q.push(tempNode -> rightChild);
        }

        if (tempNode)
        {
            res.push_back(tempNode -> info);
        }
    }
    return res;
}

template <typename T>
std::vector <T>
BST <T>::getElementsInfix() const
{
    std::vector <T>                 elements;
    std::stack  <BST <T>::Node*>    stack;
    bool                            done;
    BST <T>::Node*                  tempNode;

    done = false;
    tempNode = this -> root;
    while (not done)
    {
        if (tempNode)
        {
            stack.push(tempNode);
            tempNode = tempNode -> leftChild;
        }
        else if (stack.empty())
        {
            done = true;
        }
        else
        {
            tempNode = stack.top();
            stack.pop();
            
            elements.push_back(tempNode -> info);
            tempNode = tempNode -> rightChild;
        }
    }

    return elements;
}

template <typename T>
bool
BST <T>::exists(T value) const
{
    BST <T>::Node* tempNode;

    tempNode = this -> root;

    while ( tempNode and
            (tempNode -> info != value) )
    {
        if ( tempNode -> info > value )
        {
            tempNode = tempNode -> leftChild;
        }
        
        else
        {
            tempNode = tempNode -> rightChild;
        }
    }

    return (tempNode != nullptr);
}

template <typename T>
typename BST <T>::Iterator
BST <T>::begin()
{
    BST <T>::Node* tempNode;

    if (not root)
    {
        return Iterator(this);
    }

    tempNode = root;
    while (tempNode -> leftChild)
    {
        tempNode = tempNode -> leftChild;
    }

    return Iterator(this,
                    tempNode);
}

template <typename T>
typename BST <T>::Iterator
BST <T>::find(T value) const
{
    BST <T>::Node* tempNode;

    tempNode = root;
    while ( (tempNode) and
            (tempNode -> info != value) )
    {
        if (tempNode -> info < value)
        {
            tempNode = tempNode -> rightChild;
        }
        else
        {
            tempNode = tempNode -> leftChild;
        }
    }

    return Iterator(this,
                    tempNode);
}

#endif // BST_H
