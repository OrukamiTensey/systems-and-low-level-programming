#ifndef LINKEDLIST_H_INCLUDED 
#define LINKEDLIST_H_INCLUDED

template<typename T> 
struct HashNode 
{
    long long key;  
    T data;   
    HashNode* next;  
    HashNode(T& Data);
};

template<typename T> 
struct LinkedList
{
    HashNode<T>* head;  
    HashNode<T>* tail;   
    int currentSize; 
    LinkedList(); 

    void push_front(T& elem, long long key);
    int size(); void clear(); 
    ~LinkedList();
};

#endif // !LINKEDLIST_H_INCLUDED

