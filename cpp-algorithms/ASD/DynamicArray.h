#ifndef DYNAMICARRAY_H_INCLUDED
#define DYNAMICARRAY_H_INCLUDED

using namespace std;

template<typename T>
struct DynamicArray
{
    int capacity;
    int head;
    T* arr;

    DynamicArray();
    ~DynamicArray();

    void push_back(const T& elem);  
    T pop_back();
    T& get(int elem);
    int size();
    void clear();
    void relocateMemory();
};


#endif 