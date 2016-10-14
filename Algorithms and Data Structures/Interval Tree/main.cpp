// http://www.infoarena.ro/problema/arbint

#include <fstream>
#include <iostream>

std::ifstream mama("arbint.in");
std::ofstream tata("arbint.out");

struct Tree
{
    int     beg;
    int     end;
    int     max;
    Tree*   left;
    Tree*   right;

    Tree (int b,
          int e)
        : beg(b),
          end(e)
    {
        left = nullptr;
        right = nullptr;
    }
};

int     n;
int     m;
int     arr[100000];
Tree*   tree;

void
buildMax(Tree* t)
{
    if (nullptr == t)
    {
        return;
    }

    if (t -> beg == t -> end)
    {
        t -> max = arr[t -> beg - 1];
    }
    else
    {
        buildMax(t -> left);
        buildMax(t -> right);

        t -> max = std::max(t -> left -> max,
                            t -> right -> max);
    }
}

Tree*
generateTree(int beg,
             int end)
{
    Tree* t;

    if (beg > end)
    {
        return nullptr;
    }

    t = new Tree(beg,
                 end);

    if (beg == end)
    {
        t -> left = nullptr;
    }
    else
    {
        t -> left = generateTree(beg,
                                (beg + end) / 2);
    }
    t -> right = generateTree( (beg + end) / 2 + 1,
                               end);

    return t;
}

void
updateElement(int pos,
              int val,
              Tree* t)
{
    if (nullptr == t)
    {
        return;
    }

    if ( (t -> beg > pos) or
         (t -> end < pos) )
    {
        return;
    }

    if ( (t -> beg == pos) and
         (t -> end == pos) )
    {
        t -> max = val;
        return;
    }

    if ( (t -> beg + t -> end) / 2 >= pos)
    {
        updateElement(pos,
                      val,
                      t -> left);
    }
    else
    {
        updateElement(pos,
                      val,
                      t -> right);
    }

    t -> max = std::max(t -> left -> max,
                        t -> right -> max);
}

int
getMax(int beg,
       int end,
       Tree* t)
{
    int mid;

    if ( (t -> beg == beg) and
         (t -> end == end) )
    {
        return t -> max;
    }

    mid = (t -> beg + t -> end) / 2;

    if ( (mid + 1 > beg) and
         (mid + 1 <= end) )
    {
        return std::max(getMax(beg,
                               mid,
                               t -> left),
                        getMax(mid + 1,
                               end,
                               t -> right) );
    }
    else if ( mid >= end )
    {
        return getMax(beg,
                      end,
                      t -> left);
    }
    else if ( mid < beg )
    {
        return getMax(beg,
                      end,
                      t -> right);
    }

    return 0;
}

void
test(Tree* t)
{
    if (!t)
    {
        return;
    }

    std::cout << t -> beg << " " << t -> end << " " << t -> max << std::endl;
    test(t -> left);
    test(t -> right);
}

int main()
{
    int index;
    int op;
    int par1;
    int par2;

    mama >> n;
    mama >> m;
    
    for (index = 0; index < n; index++)
    {
        mama >> arr[index];
    }

    tree = generateTree(1,
                        n);
    buildMax(tree);

    for (index = 0; index < m; index++)
    {
        mama >> op;
        mama >> par1;
        mama >> par2;

        if (op == 0)
        {
            tata << getMax(par1,
                           par2,
                           tree) << std::endl;
        }
        else
        {
            updateElement(par1,
                          par2,
                          tree);
        }
    }

    return 0;
}
