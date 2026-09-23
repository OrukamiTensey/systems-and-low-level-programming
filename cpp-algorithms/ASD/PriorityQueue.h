#ifndef ASD2LAB3_PRIORITYQUEUE_H
#define ASD2LAB3_PRIORITYQUEUE_H

#include "BinaryHeap.h"
#include <iostream>

using namespace std;

struct PriorityQueue
{
    BinaryHeap myHeap;

    void push(const Data &object);
    Data top();
    Data* pop();
    int size();
    bool     empty();
    void clean();
};

#endif //ASD2LAB3_PRIORITYQUEUE_H
