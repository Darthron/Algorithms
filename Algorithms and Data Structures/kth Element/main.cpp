#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

int
getMedian(std::vector <int> array)
{
    std::vector <int> elements;
    unsigned int      index;
    unsigned int      groupsOfFive;

    if (array.size() < 5)
    {
        sort(array.begin(),
             array.end());

        return array[(array.size() - 1)/ 2];
    }

    groupsOfFive = array.size() - array.size() % 5;
    for (index = 0; index < groupsOfFive; index += 5)
    {
        sort(array.begin() + index,
             array.begin() + index + 5);
        
        elements.push_back(array[index + 2]); 
    }
    
    sort(array.begin() + index,
         array.end());

    elements.push_back(array[index + (array.size() % 5 - 1) / 2]);

    return getMedian(elements);
}

int
kthElement(std::vector <int>& array,
           int k)
{
    std::vector <int> elements;
    int               pivot;
    int               rank;

    if (array.size() == 1)
    {
        return array[0];
    }

    pivot = getMedian(array);
    
    for (auto el : array)
    {
        if (el <= pivot)
        {
            elements.push_back(el);
        }
    }

    rank = elements.size();
    if (rank == k)
    {
        return pivot;
    }
    else if (rank > k)
    {
        return kthElement(elements,
                          k);
    }
    else
    {
        elements.clear();
        for (auto el : array)
        {
            if (el > pivot)
            {
                elements.push_back(el);
            }
        }

        return kthElement(elements,
                          k - rank);
    }
}

int main()
{
    std::vector <int>   array;
    int                 n;
    int                 k;

    std::ifstream mama("sdo.in");
    std::ofstream tata("sdo.out");

    mama >> n;
    mama >> k;
    for (int i = 0; i < n; i++)
    {
        int number;

        mama >> number;
        array.push_back(number);
    }

    tata << kthElement(array,
                       k);
}
