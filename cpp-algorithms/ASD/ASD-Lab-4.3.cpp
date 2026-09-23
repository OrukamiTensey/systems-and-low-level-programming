#include <iostream>
#include <string>

#define N 255
using namespace std;

struct Stack
{
    char innerArray[N];
    int head = -1;

    void push(char bracket)
    {
        if (head == N - 1) cout << "Stack is full!\n";
        else innerArray[++head] = bracket;
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
    char top()
    {
        if (head >= 0)
        {
            return innerArray[head];
        }
        else cout << "Stack is empty\n";
        return 123;
    }
};

void print(Stack stackCopy)
{
    if (!stackCopy.empty())
    { 
        while (!stackCopy.empty())
        {
            cout << stackCopy.top();
        }
        cout << "\n";
    }
    else cout << "Stack is empty\n";
}

int TypeCheck(char elem)
{
    if (elem == '{' || elem == '}') return 1;
    if (elem == '[' || elem == ']') return 2;
    if (elem == '(' || elem == ')') return 3;
    else return -1;
}

void readSequence(char* arr, int size)  
{
    cout << "Enter your bracket sequence:\n";
    cin.getline(arr, size);     
}

int main()
{
    Stack sequence;
    char array[N]{}; 

    readSequence(array, N);
    for (int i = 0; i < N && array[i] != '\0'; i++)
    {
        if (array[i] == '{' || array[i] == '[' || array[i] == '(')
        {
            sequence.push(array[i]);
        }
        else if (!sequence.empty() && TypeCheck(array[i]) == TypeCheck(sequence.top()))
        {
            sequence.pop();
        }
        else
        {
            sequence.push(array[i]); 
            break;
        }
    }
    if (sequence.empty()) cout << "yes";
    else cout << "no";

    return 0;
}