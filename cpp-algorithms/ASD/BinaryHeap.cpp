#include "BinaryHeap.h"
#include <iostream>

using namespace std;

int BinaryHeap::getParent(int index)
{
    return (index - 1) / 2;
}

int BinaryHeap::getLeftChild(int index)
{
    return 2*index + 1;
}

int BinaryHeap::getRightChild(int index)
{
    return 2*index + 2;
}

void BinaryHeap::siftUp(int index)
{
    int parentIndex = getParent(index);

    Data* child = binaryTree.get(index);
    Data* parent = binaryTree.get(parentIndex);

    while(index > 0 && (*child > *parent))
    {
        swap(parent, child);
        index = parentIndex;
    }
    return;/*


    if(*child < *parent)
    {
        return;
    }

    swap(parent, child);
    if(parentIndex > 0)
    {
        siftUp(parentIndex);
    } else return;*/
}

void BinaryHeap::siftDown(int index)
{
    int leftChildIndex = getLeftChild(index);
    int rightChildIndex = getRightChild(index);
    int maxChildIndex = 0;


    if(*binaryTree.get(leftChildIndex) < *binaryTree.get(rightChildIndex))
    {
        maxChildIndex = rightChildIndex;
    } else
    {
        maxChildIndex = leftChildIndex;
    }

    Data* maxChild = binaryTree.get(maxChildIndex);
    Data* parent = binaryTree.get(index);

    if(*parent > *maxChild)
    {
        return;
    }

    swap(maxChild, parent);
    siftDown(maxChildIndex);
}