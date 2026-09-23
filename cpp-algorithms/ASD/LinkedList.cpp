#include "LinkedList.h"
#include <iostream>
#include <cstdlib>

using namespace std; 

template<typename T>
HashNode<T>::HashNode(T& Data) : key(0), data(Data), next(nullptr) {}

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), currentSize(0) {} 

template<typename T>
void LinkedList<T>::push_front(T& elem, long long key) 
{
    HashNode<T>* newNode = new HashNode<T>(elem);         
    newNode->key = key;
    if (!head)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    currentSize++;
}

template<typename T>
int LinkedList<T>::size()
{
    return currentSize;
}

template<typename T>
void LinkedList<T>::clear()
{
    if (!currentSize) return;

    HashNode<T>* current = head;
    while (current != nullptr)
    {
        HashNode<T>* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    currentSize = 0;
}

template<typename T>
LinkedList<T>::~LinkedList() 
{
    clear(); 
}