#include <fstream>
#include <iostream>
#include <limits>

struct Node
{
    int   info;
    Node* leftChild;
    Node* rightChild;

    Node(int val)
        : info(val),
          leftChild(nullptr),
          rightChild(nullptr)
    {

    }
};

std::ifstream mama("bst.in");
std::ofstream tata("bst.out");

int   n;
int   index;
int   arr[10000];
Node* root;

Node*
constructTree(int min,
              int max,
              int val)
{
    Node* node;

    if (index == n)
    {
        return nullptr;
    }

    node = nullptr;
    
    if ( (val > min) and
         (val < max) )
    {
        node = new Node(val);
        index++;

        node -> leftChild = constructTree(min,
                                          val,
                                          arr[index]);

        node -> rightChild = constructTree(val,
                                           max,
                                           arr[index]);
    }

    return node;
}
    
void
print(Node* node)
{
    if (not node)
    {
        return;
    }

    print(node -> leftChild);
    tata << node -> info << " ";
    print(node -> rightChild);
}

int main()
{
    mama >> n;
    for (index = 0; index < n; index++)
    {
        mama >> arr[index];
    }

    index = 0;
    root = constructTree(std::numeric_limits<int>::min(),
                         std::numeric_limits<int>::max(),
                         arr[0]);
    print(root);
    return 0;
}
    
