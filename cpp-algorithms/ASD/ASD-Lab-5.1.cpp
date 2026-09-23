#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <cstring>
#define N 7

using namespace std;

struct University
{
    char name[N] = ""; 
    int numOfStudents = 0; 
    bool hasTurnstiles = false;
};

struct DynamicArray
{
    int capacity;
    int head;
    University* arr;

    DynamicArray()
    {
        capacity = 10;
        head = 0;
        arr = new University[capacity];
    }

    ~DynamicArray()  
    {
        if (arr != nullptr) 
        {
            delete[] arr;
        }
    }

    void push_back(University &elem) //2.1
    {
        if (head == capacity)
        {
            relocateMemory();
        }
        arr[head++] = elem; 
    }

    University pop_back()  
    {
        if (head == 0)
        {
            cout << "Dynamic array is empty.\n";
            return University();
        }
        head--;
        return arr[head];
    }


    University get(int elem)
    {
        if (head == 0) 
        {
            cout << "Dynamic array is empty.\n";
            return University();
        }
        else if (elem < 0 || elem >= head)
        {
            cout << "Invalid index.\n";
            return University();
        }
        return arr[elem];
    }

    int size()
    {
        return head;
    }

    void print()
    {
        if (head == 0)
        {
            cout << "Dynamic array is empty.\n";
            return;
        }
        for (int i = 0; i < head; i++)
        {
            cout << i + 1 << ".\n" << "Name: " << arr[i].name << endl;  
            cout << "Number of students: " << arr[i].numOfStudents << endl;
            cout << "Has turnstiles: ";
            if (arr[i].hasTurnstiles)
            {
                cout << "Yes" << endl; 
                continue;
            }
            cout << "No" << endl;
        }
    }

    void clear()
    {
        head = 0;
        capacity = 10;
        delete[] arr; 
        arr = new University[capacity];
    }

    void relocateMemory()
    {
        capacity *= 2; 
        University* newArr = new University[capacity];  
        for (int i = 0; i < head; i++) 
        {
            newArr[i] = arr[i]; 
        }
        
        delete[] arr;  
        arr = newArr; 
    }


    void push_front(University &elem) //2.2
    {
        if (head == capacity)
        {
            relocateMemory();
        }
        memmove(arr, arr + 1, head * sizeof(University));
        arr[0] = elem;
        head++;
         
    }

    University pop_front() //2.2
    {
        if (head == 0)
        {
            cout << "Dynamic array is empty.\n";
            return University();
        }
        University Data = arr[0];
        memmove(arr + 1, arr, head * (sizeof(University) - 1)); 
        head--;
        return Data;
    }
};

struct Node //3.1
{
    University data;
    Node* next;
    Node(University& data) : data(data), next(nullptr) {}     
};

struct LinkedList 
{
    Node* head;
    Node* tail; 
    int currentSize;
    LinkedList() : head(nullptr), tail(nullptr), currentSize(0) {}   
    
    void push_back(University &elem) 
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

    void push_front(University &elem)
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

    University pop_front() 
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
        if (!currentSize) cout << "List is already empty.\n";

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

    ~LinkedList()
    {
        clear();
    }
};

int main()
{
    srand(time(NULL));

    University KPI = { "KPI", 23242, true }, NaUKMA = { "NaUKMA", 9322 };   

    //===============================================================
    DynamicArray array;

    cout << "============= DynamicArray ==============\n";

    double globalTime = 0;
    cout << "Time of:\n";

    clock_t startTime = clock(); 
    for (int t = 0; t < 50000; t++)
    {
        array.push_back(KPI); 
    }
    clock_t endTime = clock();  
    double seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC; 
    globalTime += seconds;
    cout << "push_back() function: " << seconds << " seconds" << endl;  

    startTime = clock(); 
    for (int t = 0; t < 10000; t++)
    {
        array.push_front(NaUKMA); 
    }
    endTime = clock(); 
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC; 
    globalTime += seconds; 
    cout << "push_front() function: " << seconds << " seconds" << endl; 

    startTime = clock();  
    for (int t = 0; t < 20000; t++)
    {
        array.get(rand() % array.size());  
    }
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    globalTime += seconds; 
    cout << "get() function: " << seconds << " seconds" << endl; 

    startTime = clock(); 
    for (int t = 0; t < 5000; t++)
    {
        array.pop_back(); 
    }
    endTime = clock(); 
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC; 
    globalTime += seconds; 
    cout << "pop_back() function: " << seconds << " seconds" << endl; 

    startTime = clock(); 
    for (int t = 0; t < 5000; t++) 
    {
        array.pop_front(); 
    }
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    globalTime += seconds; 
    cout << "pop_front() function: " << seconds << " seconds" << endl; 

    cout << "The total time: " << globalTime << " seconds\n"; array.clear();
    // ===============================================================
    
    LinkedList list;

    cout << "============= LinkedList ==============\n";

    globalTime = 0; 
    cout << "Time of:\n";

    startTime = clock();
    for (int t = 0; t < 50000; t++)
    {
        list.push_back(KPI);   
    }
    endTime = clock(); 
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC; 
    globalTime += seconds; 
    cout << "push_back() function: " << seconds << " seconds" << endl; 

    startTime = clock(); 
    for (int t = 0; t < 10000; t++)
    {
        list.push_front(NaUKMA);  
    }
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC; 
    globalTime += seconds;
    cout << "push_front() function: " << seconds << " seconds" << endl;

    startTime = clock();
    for (int t = 0; t < 10000; t++)
    {
        list.get(rand() % list.size());  
    }
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC; 
    globalTime += seconds;
    cout << "get() function: " << seconds << " seconds" << endl;

    startTime = clock();
    for (int t = 0; t < 5000; t++)
    {
        list.pop_back(); 
    } 
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC; 
    globalTime += seconds;
    cout << "pop_back() function: " << seconds << " seconds" << endl;

    startTime = clock();
    for (int t = 0; t < 5000; t++)
    {
        list.pop_front(); 
    }
    endTime = clock();
    seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;
    globalTime += seconds;
    cout << "pop_front() function: " << seconds << " seconds" << endl;

    cout << "The total time: " << globalTime << " seconds\n";
   
    return 1;
}

