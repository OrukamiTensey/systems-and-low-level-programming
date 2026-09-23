#include <iostream>

#define N 8
using namespace std;

struct Stack
{
    int innerArray[N];
    int head = -1;

    void push(int elem)
    {
        if (head == N - 1) cout << "Stack is full!\n";
        else innerArray[++head] = elem;
    }
    void pop()
    {
        if (head >= 0) head--;
        else cout << "Stack is already empty!\n";
    }
    bool empty()
    {
        if (head == -1) return true;
        else return false;
    }
    int size()
    {
        return head + 1;
    }
    void clear()
    {
        head = -1;
        cout << "Stack is cleared\n";
    }
    int top()
    {
        if (head >= 0)
        {
            return innerArray[head];
        }
        else cout << "Stack is empty\n";
        return 0;
    }
};

struct Queue
{
    Stack inputStack;
    Stack outputStack;
    int diff = 0;

    void push(const int& elem)
    {
        if (diff == N)
        {
            cout << "Queue is full!\n";
            return;
        }
        inputStack.push(elem);
        diff++;
    }
    void pop()
    {
        if (diff == 0) 
        {
            cout << "Queue is already empty!\n";
            return;
        }
        if (outputStack.empty())
        {
            while (!inputStack.empty())
            {
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }
        outputStack.pop();
        diff--;
    }
    bool empty()
    {
        if (diff == 0) return true;
        else return false;
    }
    int size()
    {
        return diff;
    }
    void clear()
    {
        diff = 0;
        cout << "Queue is cleared\n";
    }
    int front()
    {
        if (diff == 0)
        {
            cout << "Queue is empty!\n";
            return 0;
        }
        if (outputStack.empty()) 
        {
            while (!inputStack.empty()) 
            {
                outputStack.push(inputStack.top()); 
                inputStack.pop(); 
            }
        }
        return outputStack.top();
    }
};

void print(Queue queueCopy)
{
    if (!queueCopy.empty())
    {
        cout << "Print:\n";
        while (!queueCopy.empty())
        {
            cout << queueCopy.front() << " ";
            queueCopy.pop();
        }
        cout << "\n";
    }
    else cout << "Queue is empty\n";
}

int main()
{
    Queue queue;
    print(queue); 

    queue.push(1);
    queue.push(2); 
    queue.push(3);
    queue.push(4);

    print(queue);

    queue.push(5);
    queue.push(6);
    queue.push(7);
    queue.push(8);
    queue.push(9);

    print(queue); 

    queue.pop();
    queue.pop();

    print(queue); 

    queue.push(200);

    print(queue); 

    for (int i = 0; i < 8; i++)
    {
        queue.pop();
    }
    print(queue);
}

