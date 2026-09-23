#include <iostream>
#include <string>

#define N 7
using namespace std;

struct EditEvent
{
    string text;
    unsigned int lineNum;
};

struct Stack
{
    EditEvent history[N];
    int head = -1;

    void addEvent(const EditEvent& event)
    {
        if (head == N - 1) cout << "History is full!\n";
        else history[++head] = event; 
    }
    void undo()
    {
        if (head >= 0) head--;
        else cout << "History is already empty!\n";
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
        cout << "History is cleared\n";
    }
    EditEvent top()
    {
        if (head >= 0)
        {
            return history[head];
        }
        cout << "History is empty\n";
        return EditEvent{ "", 0 };
    }
    
};

void print(Stack editHistory) 
{
    if (!editHistory.empty())
    {
        cout << "Print:\n";
        EditEvent elem;
        while (!editHistory.empty())
        {
            elem = editHistory.top();
            cout << "Line " << elem.lineNum << ": " << elem.text << "\n";
            editHistory.undo();
        }
        cout << "\n";
    }
    else cout << "History is empty\n";
}

void main()
{
    Stack editHistory;
    
    print(editHistory); 
     
    editHistory.addEvent({ "Add the line 1", 1 }); 
    editHistory.addEvent({ "Add the line 2", 2 });
    editHistory.addEvent({ "Edit the line 2", 2 });
    editHistory.addEvent({ "Add the line 3", 3 }); 

    print(editHistory);

    editHistory.addEvent({ "Edit the line 1", 1 });
    editHistory.addEvent({ "Add the line 4", 4 });
    editHistory.addEvent({ "Edit the line 3", 3 });
    editHistory.addEvent({ "Add the line 5", 5 });
    editHistory.addEvent({ "Add the line 6", 6 });
    editHistory.addEvent({ "Edit the line 4", 4 }); 

    print(editHistory); 

    editHistory.undo();
    editHistory.undo();

    print(editHistory);  

    editHistory.undo();
    editHistory.addEvent({ "Edit the line 4", 4 });

    print(editHistory);  

    for (int i = 0; i < 6; i++)
    {
        editHistory.undo();
    }
    print(editHistory); 
}



