#ifndef HEAP_H
#define HEAP_H

#include <vector>

using uint = unsigned int;

template <typename T>
class Heap
{
public:
    Heap();
    ~Heap();

    Heap(std::vector <T> array);

    void
    insert(T value);

    inline T
    getTop() const
    {
        // Automatically throws OutOfBoundsException if called
        return container[0];
    }

    void
    popTop();
    
    inline std::vector <T>
    getElements() const
    {
        return container;
    }

private:
    // Takes the element on position index and places it in its position
    void
    swim(uint index);

    // Takes the element on position index and places it in its position
    void
    sink(uint index);

    std::vector <T> container;
    uint            size;
};

// --------------------------------------------------------- Implementation ----

template <typename T>
Heap <T>::Heap()
{
    size = 0;
}

template <typename T>
Heap <T>::~Heap()
{

}

template <typename T>
Heap <T>::Heap(std::vector <T> array)
{
    uint index;

    // Dummy element
    if (array.size())
    {
        container.push_back(array[0]);
    }

    size = 0;
    for (index = 0; index < array.size(); index++)
    {
        container.push_back(array[index]);
        this -> size++;

        swim(size);
    }
}

template <typename T>
void
Heap <T>::swim(uint index)
{
    T tempForSwap;

    while ( (index > 1) and
            (container[index / 2] < container[index]) )
    {
        tempForSwap = container[index / 2];
        container[index / 2] = container[index];
        container[index] = tempForSwap;

        index /= 2;
    }
}

template <typename T>
void
Heap <T>::sink(uint index)
{
    T tempForSwap;
    T maximum;

    while (2 * index <= size)
    {
        if (2 * index + 1 <= size)
        {
            maximum = (container[2 * index] > container[2 * index + 1]) ? 2 * index : 2 * index + 1;
        }
        else
        {
            maximum = 2 * index;
        }
        
        if (container[index] < container[maximum])
        {
            tempForSwap = container[index];
            container[index] = container[maximum];
            container[maximum] = tempForSwap;

            index = maximum;
        }
        else
        {
            index = size;
        }
    }
}

template <typename T>
void
Heap <T>::popTop()
{
    T tempForSwap;

    if (size == 0)
    {
        return;
    }

    if (size == 1)
    {
        // Also delete dummy
        container.erase(container.begin() + 1);
        container.erase(container.begin());
        size--;
        return;
    }

    // Swap the element on the last position with the top one
    tempForSwap = container[1];
    container[1] = container[size];
    container[size] = tempForSwap;
    
    // Delete the element on the last position (i.e. the old top)
    container.erase(container.begin() + size);
    size--;

    // Sink the new top so that the heap propriety holds
    sink(1);
}

template <typename T>
void
Heap <T>::insert(T value)
{
    if (this -> size == 0)
    {
        // Also insert dummy
        container.push_back(value);
    }

    container.push_back(value);
    size++;

    swim(size);

}

#endif // HEAP_H
