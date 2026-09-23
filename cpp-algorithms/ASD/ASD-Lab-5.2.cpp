#include <iostream>
#include <cstdlib>

using namespace std;

struct University
{
    char name[20] = ""; 
    int numOfStudents = 0; 
    bool hasTurnstiles = false; 
}; 

struct Node 
{
    University data;
    Node* next;
    Node(University data) : data(data), next(nullptr) {}
};
struct LinkedList 
{
    Node* head;
    Node* tail;
    int currentSize;
    LinkedList() : head(nullptr), tail(nullptr), currentSize(0) {}

    void push_back(University elem)
    {
        Node* newNode = new Node(elem);
        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        currentSize++;
    }

    void push_front(University elem)
    {
        Node* newNode = new Node(elem);
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

    University pop_back()
    {
        if (!currentSize)
        {
            cout << "List is empty.\n";
            return University();
        }
        University Data;
        if (currentSize == 1)
        {
            Data = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node* current = head;
            while (current->next != tail)
            {
                current = current->next;
            }
            Data = tail->data;
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        currentSize--;
        return Data;
    }

    University pop_front() //2.2
    {
        if (!currentSize)
        {
            cout << "List is empty.\n";
            return University();
        }
        University Data = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        currentSize--;
        if (currentSize == 0)
        {
            tail = nullptr;
        }
        return Data;
    }

    University get(int elem)
    {
        if (!currentSize)
        {
            cout << "List is empty.\n";
            return University();
        }
        else if (elem < 0 || elem >= currentSize)
        {
            cout << "Invalid index.\n";
            return University();
        }
        else if (elem == currentSize - 1)
        {
            return tail->data;
        }
        Node* current = head;

        for (int i = 0; i < elem; i++)
        {
            current = current->next;
        }

        return current->data;
    }

    int size()
    {
        return currentSize;
    }

    void print()
    {
        if (!currentSize)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node* current = head; int i = 1;
        while (current != nullptr)
        {
            cout << i << ".\n" << "Name: " << current->data.name << endl;
            cout << "Number of students: " << current->data.numOfStudents << endl;
            cout << "Has turnstiles: ";
            if (current->data.hasTurnstiles)
            {
                cout << "Yes" << endl;
            }
            else cout << "No" << endl;
            current = current->next;
            i++;
        }
    }

    void clear()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        currentSize = 0;
    }
};

Node* reverse(Node* head) 
{
    Node* next = nullptr, * past = nullptr, * current = head;

    while (current != nullptr)
    {
        next = current->next; 
        current->next = past;
        past = current;
        current = next;
    }
    return past;
}

int hasCycle(Node* head)
{
    if (!head || !head->next) return 0;
    
    Node* fast = head->next; 
    Node* slow = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        if (fast == slow) 
        {
            return 1;
        }
        slow = slow->next; 
        fast = fast->next->next;
    }
    return 0; 
}

int main()
{
    LinkedList list;

    list.push_back({ "KPI", 95743 }); 
    list.push_back({ "KNU", 15993, true }); 
    list.push_back({ "NAU", 43221, true });

    cout << "Original list\n";
    list.print();

    Node* newHead = reverse(list.head); 
    cout << "\nReversed list:\n";

    LinkedList reversedList;
    reversedList.head = newHead;

    reversedList.currentSize = list.size();
    reversedList.print();

    cout << hasCycle(list.head);
}


