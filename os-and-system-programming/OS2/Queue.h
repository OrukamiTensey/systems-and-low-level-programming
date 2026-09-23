#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template<typename T>
struct Node 
{
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template<typename T>
class Queue 
{
private:
    Node<T>* front;
    Node<T>* rear;
    int count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}

    void enqueue(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else 
        {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    T dequeue()
    {
        if (isEmpty()) throw runtime_error("Queue is empty!");
        Node<T>* temp = front;
        T value = temp->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        count--;
        return value;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    int size() const 
    {
        return count;
    }

    void print() const
    {
        Node<T>* temp = front;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~Queue() 
    {
        while (!isEmpty()) dequeue();
    }
};

#endif