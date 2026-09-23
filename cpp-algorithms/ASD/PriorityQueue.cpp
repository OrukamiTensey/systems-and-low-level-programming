#include "PriorityQueue.h"
#include <iostream>

using namespace std;

void PriorityQueue::push(const Data &object)
{
    myHeap.binaryTree.push_back(object);
    myHeap.siftUp(myHeap.binaryTree.size() - 1);
}

Data PriorityQueue::top()
{
    return *myHeap.binaryTree.get(0);
}

Data* PriorityQueue::pop()
{
    Data* parent = myHeap.binaryTree.get(0);
    Data* lastElement = myHeap.binaryTree.get(myHeap.binaryTree.size() - 1);

    swap(lastElement, parent);

    myHeap.siftDown(0);

    myHeap.binaryTree.pop_back();
}

int PriorityQueue::size()
{
    return myHeap.binaryTree.size();
}

bool PriorityQueue::empty()
{
    return myHeap.binaryTree.size();
}

void PriorityQueue::clean()
{
    myHeap.binaryTree.clear();
}

/*
struct Queue
{
    Goods queueArr[N];
    int head = -1;
    int tail = -1;
    int sizeArr = 0;

    bool isFull(int sizeArr)
    {
        if(sizeArr > N)
        {
            return 1;
        } else
        {
            return 0;
        }
    }

    void push(Goods value)
    {
        if(head == -1) head++;

        if(isFull(sizeArr+1) == 0)
        {
            if(tail+1 == N) tail = -1;

            tail++;
            queueArr[tail] = value;
            sizeArr++;
        } else
        {
            cout << "Queue is full!\n";
        }
    }

    void pop()
    {
        if(empty() == 0)
        {
            if(head+1 == N) head = -1;      // ïåðåâ³ðêà íà âèõ³ä çà ìåæ³ ìàñèâó òà ïåðåì³ùåííÿ ³íäåêñó íà ïî÷àòîê ìàñèâó

            head++;
            sizeArr--;      // çìåíøåííÿ ðîçì³ðó ÷åðãè, áî âèäàëèëè åëåìåíò
        } else
        {
            cout << "There are no elements to delete!\n";
        }
    }

    Goods front()
    {
        if(empty() == 0)
        {
            return queueArr[head];
        } else
        {
            cout << "There are no elements to print!\n";
        }
    }

    int size()
    {
        return sizeArr;
    }

    bool empty()
    {
        return sizeArr == 0;
    }

    void clear()
    {
        head = -1;
        tail = -1;
        sizeArr = 0;
    }
};
*/