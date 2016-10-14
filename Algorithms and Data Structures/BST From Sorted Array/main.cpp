#include <fstream>

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

Node*
createBSTFromSortedArray(int* arr,
                         int  beg,
                         int  end)
{
    int   mid;
    Node* node;

    if (beg == end)
    {
        return (new Node(arr[beg]));
    }

    mid = (beg + end) / 2;

    node = new Node(arr[mid]);
    node -> leftChild = createBSTFromSortedArray(arr,
                                                 beg,
                                                 mid - 1);
    node -> rightChild = createBSTFromSortedArray(arr,
                                                  mid + 1,
                                                  end);

    return node;
}

int main()
{
    Node* root;
    int   n;
    int   arr[10000];
    int   i;

    std::ifstream mama("input.in");
    std::ofstream tata("output.out");

    mama >> n;
    for (i = 0; i < n; i++)
    {
        mama >> arr[i];
    }

    root = createBSTFromSortedArray(arr,
                                    0,
                                    n - 1);
    return 0;
}
