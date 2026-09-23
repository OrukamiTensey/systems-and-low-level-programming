#ifndef ASD2LAB3_BINARYHEAP_H
#define ASD2LAB3_BINARYHEAP_H

#include <iostream>
#include "DynamicArray.h"
using namespace std;

struct BinaryHeap
{
    DynamicArray binaryTree;

    int getParent(int index);
    int getLeftChild(int index);
    int getRightChild(int index);

    void siftUp(int index);
    void siftDown(int index);
};

#endif //ASD2LAB3_BINARYHEAP_H
