#include <iostream>
#include <string>

#define N 8
using namespace std;

struct Worker
{
    string position;
    string experience;
    int salary;
};

struct Queue
{
    Worker PromQueue[N];
    int head = -1, tail = -1; 
    int diff = 0;

    void addWorker(const Worker& pro)
    {
        if (diff == N) 
        {
            cout << "Queue is full!\n";
            return;
        }
        else if (tail == N - 1) tail = 0;       
        else tail++;
        PromQueue[tail] = pro;

        if (head == -1) head++;
        diff++;
        
    }
    void pop()
    {
        if (diff == 0)
        {
            cout << "Queue is already empty!\n";
            return;
        }
        else if (head == N - 1) head = 0;
        else head++; 
        diff--;       
    }
    void increaseSalary(int newSalary)
    {
        if (diff > 0)
        {
            Worker& pro = PromQueue[head];
            pro.salary += newSalary;
        }
        else cout << "Queue is empty\n";
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
        head = -1; tail = -1; diff = 0;
        cout << "Queue is cleared\n";
    }
    Worker front()
    {
        if (diff > 0)
        {
            return PromQueue[head];
        }
        cout << "Queue is empty\n";
        return Worker{ "", "", 0 };
    }
};

void print(Queue queueCopy)
{
    if (!queueCopy.empty())
    {
        cout << "Print:\n"; 
        Worker elem; int i = 1;
        while (!queueCopy.empty())
        {
            elem = queueCopy.front();
            cout << "Worker " << i << "\nPosition: " << elem.position;
            cout << "\nExperience: " << elem.experience << "\nSalary: " << elem.salary << endl;
            queueCopy.pop(); 
            i++;
        }
        cout << "\n";
    }
    else cout << "Queue is empty\n";
}

int main()
{
    Queue queue;

    print(queue); 

    queue.addWorker({ "front-end","middle",1000 });
    queue.addWorker({ "back-end","junior",800 });
    queue.addWorker({ "back-end","senior",1500 }); 
    queue.addWorker({ "tester","junior",600 });
    queue.addWorker({ "team lead","senior",2500 });

    print(queue);

    queue.increaseSalary(200);

    print(queue); 

    queue.addWorker({ "fullstack","senior",2000 });
    queue.addWorker({ "front-end","junior",800 });
    queue.addWorker({ "tester","middle",1000 });
    queue.addWorker({ "back-end","middle",1200 }); 

    print(queue);  

    for (int i = 0; i < 10; i++)
    {
        if (!queue.empty())
        {
            queue.pop();
        }
        else
        {
            cout << "Queue is already empty!\n";
            break;
        }
    }

    print(queue); 
}


