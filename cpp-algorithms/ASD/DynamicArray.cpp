#include "DynamicArray.h"
#include <iostream>
#include <cstdlib>

using namespace std;


template<typename T>
DynamicArray<T>::DynamicArray() : capacity(10), head(0), arr(new T[capacity]) {}   

template<typename T>
void DynamicArray<T>::push_back(const T& elem)   
{
    if (head == capacity)
    {
        relocateMemory();
    }
    arr[head++] = elem;
}

template<typename T>
T DynamicArray<T>::pop_back()
{
    if (head == 0)
    {
        cout << "Dynamic array is empty.\n";
        return T();  
    }
    head--;
    return arr[head];
}

template<typename T>
T& DynamicArray<T>::get(int elem)
{
    if (head == 0)
    {
        throw out_of_range("Array is empty"); 
    }
    else if (elem < 0 || elem >= head)
    {
        throw out_of_range("Index out of range"); 
    }
    return arr[elem];
}

template<typename T>
int DynamicArray<T>::size()
{
    return head;
}

template<typename T>
void DynamicArray<T>::clear()
{
    head = 0;
    capacity = 10;
    delete[] arr;
    arr = new T[capacity];
}

template<typename T>
void DynamicArray<T>::relocateMemory() 
{
    capacity *= 2;
    T* newArr = new T[capacity];
    for (int i = 0; i < head; i++)
    {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] arr;
}
